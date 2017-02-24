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

IRTree::TOperatorType CIrtBuilderVisitor::operatorFromAstToIr( COperationExpression::OperationType type ) const {
    IRTree::TOperatorType typeResult;
    switch ( type ) {
        case COperationExpression::OperationType::ADDITION: typeResult = IRTree::TOperatorType::OT_Plus; break;
        case COperationExpression::OperationType::SUBTRACTION: typeResult = IRTree::TOperatorType::OT_Minus; break;
        case COperationExpression::OperationType::MULTIPLICATION: typeResult = IRTree::TOperatorType::OT_Times; break;
        //case COperationExpression::OperationType::DIVISION = IRTree::TOperatorType::OT_Div; break;
        case COperationExpression::OperationType::MOD: typeResult = IRTree::TOperatorType::OT_Mod; break;
        case COperationExpression::OperationType::AND: typeResult = IRTree::TOperatorType::OT_And; break;
        case COperationExpression::OperationType::OR: typeResult = IRTree::TOperatorType::OT_Or; break;
        default: {
            // such cases should never happen
            assert( false ) ;
        }
    }
    return typeResult;
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
    frameCurrent = std::shared_ptr<IRTree::CFrame>( new IRTree::CFrame( className, methodName ) );

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

    declaration->getListStatements()->Accept( this );
    std::shared_ptr<IRTree::ISubtreeWrapper> statementListWrapper( subtreeWrapper );

    if (declaration->getReturnExpression()) {
        declaration->getReturnExpression()->Accept( this );
        std::shared_ptr<const IRTree::CExpression> expressionReturn(subtreeWrapper->ToExpression());
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
    } else {
        if ( statementListWrapper ) {
            updateSubtreeWrapper( new IRTree::CStatementWrapper(
                    new IRTree::CSeqStatement(
                            std::shared_ptr<const IRTree::CLabelStatement>(
                                    new IRTree::CLabelStatement( IRTree::CLabel( methodFullName ) )
                            ),
                            statementListWrapper->ToStatement()
                    )
            ) );
        } else {
            // empty function
            updateSubtreeWrapper( new IRTree::CStatementWrapper(
                    new IRTree::CLabelStatement( IRTree::CLabel( methodFullName ) )
            ) );
        }
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

void CIrtBuilderVisitor::Visit(CAssignStatement *statement) {

    statement->GetVariable()->Accept( this );
    std::shared_ptr<IRTree::ISubtreeWrapper> wrapperLeftPart( subtreeWrapper );
    statement->GetExpression()->Accept( this );
    std::shared_ptr<IRTree::ISubtreeWrapper> wrapperRightPart( subtreeWrapper );

    updateSubtreeWrapper( new IRTree::CStatementWrapper(
            new IRTree::CMoveStatement(
                    wrapperLeftPart->ToExpression(),
                    wrapperRightPart->ToExpression()
            )
    ) );
}

void CIrtBuilderVisitor::Visit(CAssignItemStatement *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CPrintStatement *statement) {

    statement->GetExpression()->Accept( this );

    updateSubtreeWrapper( new IRTree::CExpressionWrapper(
            std::move( frameCurrent->ExternalCall(
                    "print",
                    std::shared_ptr<const IRTree::CExpressionList>(
                            new IRTree::CExpressionList( subtreeWrapper->ToExpression() )
                    )
            ) )
    ) );
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

void CIrtBuilderVisitor::Visit(COperationExpression *expression) {

    expression->GetLeftOperand()->Accept( this );
    std::shared_ptr<IRTree::ISubtreeWrapper> wrapperLeft( subtreeWrapper );
    // std::unique_ptr<const IRTree::CExpression> expressionLeft = std::move( subtreeWrapper->ToExpression() );

    expression->GetRightOperand()->Accept( this );
    std::shared_ptr<IRTree::ISubtreeWrapper> wrapperRight( subtreeWrapper );
    // std::unique_ptr<const IRTree::CExpression> expressionRight = std::move( subtreeWrapper->ToExpression() );

    if ( expression->GetOperationType() == COperationExpression::OperationType::LESS ) {
        updateSubtreeWrapper( new IRTree::CRelativeConditionalWrapper(
                IRTree::TLogicOperatorType::LOT_LT,
                wrapperLeft->ToExpression(),
                wrapperRight->ToExpression()
        ) );
    } else if ( expression->GetOperationType() == COperationExpression::OperationType::AND ) {
        updateSubtreeWrapper( new IRTree::CAndConditionalWrapper(
                wrapperLeft,
                wrapperRight
        ) );
    } else if ( expression->GetOperationType() == COperationExpression::OperationType::OR ) {
        updateSubtreeWrapper( new IRTree::COrConditionalWrapper(
                wrapperLeft,
                wrapperRight
        ) );
    } else {
        IRTree::TOperatorType operatorType = operatorFromAstToIr( expression->GetOperationType() );

        updateSubtreeWrapper( new IRTree::CExpressionWrapper(
                new IRTree::CBinaryExpression(
                        operatorType,
                        wrapperLeft->ToExpression(),
                        wrapperRight->ToExpression()
                )
        ) );
    }
}

void CIrtBuilderVisitor::Visit(CLengthExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CArrayConstructionExpression *) {
    //MOCKs
}

void CIrtBuilderVisitor::Visit(CConstructClassExpression *expression) {

    ClassInfo classInfo = symbolTable.GetClassInfo(expression->getClassID()->GetName());
    int fieldCount = classInfo.variableDeclaration.size();

    updateSubtreeWrapper( new IRTree::CExpressionWrapper(
            std::move( frameCurrent->ExternalCall(
                    "malloc",
                    std::shared_ptr<const IRTree::CExpressionList>(
                            new IRTree::CExpressionList(
                                    new IRTree::CBinaryExpression(
                                            IRTree::TOperatorType::OT_Times,
                                            new IRTree::CConstExpression( fieldCount ),
                                            new IRTree::CConstExpression( frameCurrent->WordSize() )
                                    )
                            )
                    )
            ) )
    ) );

    methodCallerClassName = expression->getClassID()->GetName();
}

void CIrtBuilderVisitor::Visit(CMethodCallExpression *expression) {
    expression->getObject()->Accept( this );
    std::string methodCaller = methodCallerClassName;

    const std::vector<std::shared_ptr<IExpression>>& arguments = expression->getArguments()->GetExpressions();

    IRTree::CExpressionList* expressionListIrt = new IRTree::CExpressionList();

    for ( auto it = arguments.begin(); it != arguments.end(); ++it ) {
        ( *it )->Accept( this );
        expressionListIrt->Add( subtreeWrapper->ToExpression() );
    }

    updateSubtreeWrapper( new IRTree::CExpressionWrapper(
            new IRTree::CCallExpression(
                    new IRTree::CNameExpression(
                            IRTree::CLabel( makeMethodFullName( methodCaller, expression->getMethodId()->GetName() ) )
                    ),
                    expressionListIrt
            )
    ) );

    std::vector<MethodInfo> methodsInfo = symbolTable.GetAvailableMethodsInfo(methodCaller);
    std::string returnType = "";
    for (auto it = methodsInfo.begin(); it != methodsInfo.end(); ++it) {
        if (it->name == expression->getMethodId()->GetName()) {
            returnType = it->returnedType;
            break;
        }
    }

    if (symbolTable.GetClassInfo(returnType).name != "") {
        methodCallerClassName = returnType;
    }
}

void CIrtBuilderVisitor::Visit(CThisExpression *) {
    //MOCK
}

void CIrtBuilderVisitor::Visit(CGetItemExpression *expression) {

    expression->GetObject()->Accept( this );
    std::shared_ptr<const IRTree::CExpression> containerExpression( subtreeWrapper->ToExpression() );

    expression->GetIndex()->Accept( this );
    std::shared_ptr<const IRTree::CExpression> indexExpression( subtreeWrapper->ToExpression() );

    updateSubtreeWrapper( new IRTree::CExpressionWrapper(
            new IRTree::CMemExpression(
                    new IRTree::CBinaryExpression(
                            IRTree::TOperatorType::OT_Plus,
                            containerExpression,
                            std::shared_ptr<const IRTree::CBinaryExpression>(
                                    new IRTree::CBinaryExpression(
                                            IRTree::TOperatorType::OT_Times,
                                            new IRTree::CBinaryExpression(
                                                    IRTree::TOperatorType::OT_Plus,
                                                    indexExpression,
                                                    std::shared_ptr<const IRTree::CConstExpression>(
                                                            new IRTree::CConstExpression( 1 )
                                                    )
                                            ),
                                            new IRTree::CConstExpression( frameCurrent->WordSize() )
                                    )
                            )
                    )
            )
    ) );
}
