#include <Visitors/IrtBuilderVisitor.h>
#include <CommonInclude.h>
#include <IRTree/Frame.h>
#include <unordered_set>

void CIrtBuilderVisitor::StartVisit(INode *startNode) {
    startNode->Accept(this);
}

TMethodToIRTMap CIrtBuilderVisitor::GetMethodTrees() {
    return methodTrees;
}

void CIrtBuilderVisitor::Visit( CMainClass* mainClass ) {
    //ПОТЕНЦИАЛЬНО БАГ (ЕСТЬ ЛИ ИНФО О MAIN CLASS В ТАБЛИЦЕ СИМВОЛОВ)
    classCurrentName = mainClass->GetClassId()->GetName();

    mainClass->GetMainMethod()->Accept( this );
}

template <class InputIteratorArguments, class InputIteratorLocals, class InputIteratorFields>
void CIrtBuilderVisitor::buildNewFrame( const std::string& className, const std::string& methodName,
                                        InputIteratorArguments argumentsLeftIt, InputIteratorArguments argumentsRightIt,
                                        InputIteratorLocals localsLeftIt, InputIteratorLocals localsRightIt,
                                        InputIteratorFields fieldsLeftIt, InputIteratorFields fieldsRightIt ) {
    std::unique_ptr<IRTree::CFrame> frameNew = std::unique_ptr<IRTree::CFrame>( new IRTree::CFrame( className, methodName ) );

    frameCurrent = frameNew.get();

    frameCurrent->AddThis();
    for ( auto it = fieldsLeftIt; it != fieldsRightIt; ++it ) {
        frameCurrent->AddField( *it );
    }
    // arguments and locals should be added after fields
    // in order to overwrite them in the map of addresses in case of name collision
    for ( auto it = argumentsLeftIt; it != argumentsRightIt; ++it ) {
        frameCurrent->AddArgument( *it );
    }
    frameCurrent->AddReturn();
    for ( auto it = localsLeftIt; it != localsRightIt; ++it ) {
        frameCurrent->AddLocal( *it );
    }
}


void CIrtBuilderVisitor::buildNewFrame( CMethod* declaration ) {

    ClassInfo classInfo = symbolTable.GetClassInfo(classCurrentName);
    MethodInfo methodInfo = classInfo.GetMethodInfo(declaration->getId()->GetName());

    std::vector<VariableInfo> params(methodInfo.paramList);
    std::vector<std::string> paramsNames;
    paramsNames.reserve( params.size() );
    for ( auto it = params.begin(); it != params.end(); ++it ) {
        paramsNames.push_back( it->name );
    }

    std::vector<VariableInfo> locals(methodInfo.variablesList);
    std::vector<std::string> localsNames;
    localsNames.reserve( locals.size() );
    for ( auto it = locals.begin(); it != locals.end(); ++it ) {
        localsNames.push_back( it->name );
    }

    std::unordered_set<std::string> fieldsNames;
    ClassInfo currentClass = classInfo;
    do {
        std::vector<VariableInfo> fields = currentClass.variableDeclaration;
        for ( auto it = fields.begin(); it != fields.end(); ++it ) {
            fieldsNames.insert( it->name );
        }
        currentClass = symbolTable.GetClassInfo(currentClass.baseId);
    } while(currentClass.HasBase());

    buildNewFrame( classCurrentName, declaration->getId()->GetName(), paramsNames.begin(), paramsNames.end(),
                   localsNames.begin(), localsNames.end(), fieldsNames.begin(), fieldsNames.end() );
}

void CIrtBuilderVisitor::Visit( CNumExpression* expression ) {
//    ++expressionId;
//    std::string nodeName = getNodeNameWithLabel(std::to_string(expression->GetNumber()), expressionId, "Number");
    updateSubtreeWrapper(
            new IRTree::CExpressionWrapper(
                    new IRTree::CConstExpression( expression->GetNumber() )
            )
    );
}

void CIrtBuilderVisitor::Visit( CBoolExpression* expression ) {

    updateSubtreeWrapper( new IRTree::CExpressionWrapper(
            new IRTree::CConstExpression( expression->GetValue() ? 1 : 0 )
    ) );
}

void CIrtBuilderVisitor::Visit( CIdExpression* expression ) {

    const IRTree::IAddress* address = frameCurrent->GetAddress( expression->GetName() );

    if ( address ) {
        // expression is a name of local var / argument / field

        std::vector<MethodInfo> methods = symbolTable.GetAvailableMethodsInfo(frameCurrent->GetClassName());
        MethodInfo methodInfo;
        for (auto it = methods.begin(); it != methods.end(); ++it) {
            if (it->name == frameCurrent->GetMethodName()) {
                methodInfo = *it;
                break;
            }
        };

        VariableInfo varInfo = methodInfo.GetVariableOrParamInfo(expression->GetName());
        std::string type = varInfo.type;
        if ( type == NONE_TYPE ) {
            // expression is a name of field
            updateSubtreeWrapper( new IRTree::CExpressionWrapper(
                    new IRTree::CMemExpression(
                            address->ToExpression(
                                    std::shared_ptr<IRTree::CExpression>(
                                            new IRTree::CMemExpression(
                                                    frameCurrent->GetThis()->ToExpression(
                                                            std::shared_ptr<IRTree::CExpression>(
                                                                    new IRTree::CTempExpression( frameCurrent->FramePointer() )
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
            ) );
            type = symbolTable.GetClassInfo(frameCurrent->GetClassName()).GetFieldInfo(expression->GetName()).type;
        } else {
            // expression is a name of local var / argument
            updateSubtreeWrapper( new IRTree::CExpressionWrapper(
                    new IRTree::CMemExpression(
                            address->ToExpression(
                                    std::shared_ptr<IRTree::CExpression>(
                                            new IRTree::CTempExpression( frameCurrent->FramePointer() )
                                    )
                            )
                    )
            ) );
        }

        if ( symbolTable.GetClassInfo(type).name == "" ) {
            methodCallerClassName = type;
        }
    }
}

void CIrtBuilderVisitor::Visit( CVarDecl* declaration ) {
    // such calls should never happen
    assert( false );
}

void CIrtBuilderVisitor::Visit( CMethod* declaration ) {

    buildNewFrame( declaration );
    std::string methodFullName = makeMethodFullName( frameCurrent->GetClassName(), frameCurrent->GetMethodName() );

    declaration->getListDeclarations()->Accept( this );
    std::shared_ptr<IRTree::ISubtreeWrapper> statementListWrapper( subtreeWrapper );

    declaration->getReturnExpression()->Accept( this );
    std::shared_ptr<const IRTree::CExpression> expressionReturn( subtreeWrapper->ToExpression() );

    if ( statementListWrapper ) {
        updateSubtreeWrapper(
                new IRTree::CStatementWrapper(
                        new IRTree::CSeqStatement(
                                new IRTree::CLabelStatement( IRTree::CLabel( methodFullName ) ),
                                new IRTree::CSeqStatement(
                                        statementListWrapper->ToStatement(),
                                        std::shared_ptr<const IRTree::CMoveStatement>(
                                                new IRTree::CMoveStatement(
                                                        std::shared_ptr<const IRTree::CTempExpression>(
                                                                new IRTree::CTempExpression( frameCurrent->ReturnValueTemp() )
                                                        ),
                                                        expressionReturn
                                                )
                                        )
                                )
                        )
                )
        );
    } else {
        updateSubtreeWrapper(
                new IRTree::CStatementWrapper(
                        new IRTree::CSeqStatement(
                                new IRTree::CLabelStatement( IRTree::CLabel( methodFullName ) ),
                                new IRTree::CMoveStatement(
                                        std::shared_ptr<const IRTree::CTempExpression>(
                                                new IRTree::CTempExpression( frameCurrent->ReturnValueTemp() )
                                        ),
                                        expressionReturn
                                )
                        )
                )
        );
    }

    methodTrees.emplace( methodFullName, std::move( subtreeWrapper->ToStatement() ) );
}

void CIrtBuilderVisitor::Visit( CClass* declaration ) {

    classCurrentName = declaration->getId()->GetName();
    declaration->getMethods()->Accept( this );
}

void CIrtBuilderVisitor::Visit( CProgram* program ) {

    program->GetMainClass()->Accept( this );
    program->GetMinorClasses()->Accept( this );
}

void CIrtBuilderVisitor::Visit( CListStatement* list ) {

    const std::vector<std::shared_ptr<IStatement> >& statements = list->GetStatements();
    std::shared_ptr<IRTree::ISubtreeWrapper> resultOnSuffix(nullptr);

    if ( !statements.empty() ) {
        //CHECK IT!!!

        // statements must be reversed before being used
        // we'll actually iterate over them in reversed order (the last statement will be the first)
        ( statements.front() )->Accept( this );
        resultOnSuffix = subtreeWrapper;
        for ( auto it = std::next( statements.begin() ); it != statements.end(); ++it ) {
            ( *it )->Accept( this );
            std::shared_ptr<IRTree::ISubtreeWrapper> resultCurrent( subtreeWrapper );
            resultOnSuffix = std::shared_ptr<IRTree::ISubtreeWrapper>( new IRTree::CStatementWrapper(
                    new IRTree::CSeqStatement(
                            resultCurrent->ToStatement(),
                            resultOnSuffix->ToStatement()
                    )
            ) );
        }
    }

    subtreeWrapper = resultOnSuffix;
}


void CIrtBuilderVisitor::updateSubtreeWrapper( IRTree::ISubtreeWrapper* wrapperNew ) {
    subtreeWrapper = std::shared_ptr<IRTree::ISubtreeWrapper>( wrapperNew );
}

void CIrtBuilderVisitor::updateSubtreeWrapper( std::shared_ptr<IRTree::ISubtreeWrapper> wrapperNew ) {
    subtreeWrapper = std::move( wrapperNew );
}

std::string CIrtBuilderVisitor::makeMethodFullName( const std::string& className, const std::string& methodName ) {
    return className + "::" + methodName;
}

void CIrtBuilderVisitor::Visit(CAssignStatement *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CAssignItemStatement *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CPrintStatement *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CIfElseStatement *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CWhileStatement *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CListExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CNotExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(COperationExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CLengthExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CArrayConstructionExpression *) {
    //MOCKs
}

void CIrtBuilderVisitor::Visit(CConstructClassExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CMethodCallExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CThisExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CGetItemExpression *) {
    //MOCK
}
