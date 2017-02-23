#include <Visitors/IrtBuilderVisitor.h>
#include <CommonInclude.h>
#include <IRTree/Frame.h>


void CIrtBuilderVisitor::Visit( CMainClass* mainClass ) {

    buildNewFrame( mainClass );
    std::string methodFullName = makeMethodFullName( frameCurrent->GetClassName(), frameCurrent->GetMethodName() );

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
