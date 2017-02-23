#include <Visitors/IrtBuilderVisitor.h>
#include <CommonInclude.h>
#include <IRTree/Frame.h>

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

void CIrtBuilderVisitor::updateSubtreeWrapper( IRTree::ISubtreeWrapper* wrapperNew ) {
    subtreeWrapper = std::shared_ptr<IRTree::ISubtreeWrapper>( wrapperNew );
}

void CIrtBuilderVisitor::updateSubtreeWrapper( std::shared_ptr<IRTree::ISubtreeWrapper> wrapperNew ) {
    subtreeWrapper = std::move( wrapperNew );
}
