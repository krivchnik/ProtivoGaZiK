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

        ClassInfo classInfo = classes[frameCurrent->GetClassName()];

        //wrong decision
        MethodInfo methodInfo = classInfo.GetMethodInfo(frameCurrent->GetMethodName());
        VariableInfo varInfo = methodInfo.GetVariableOrParamInfo(expression->GetName());

        if ( varInfo.type == NONE_TYPE ) {
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
            type = classDefinition->GetFieldType( expression->GetName() );
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

        if ( type.Type() == TTypeIdentifier::ClassId ) {
            methodCallerClassName = type.ClassName();
        }
    }
}

void CIrtBuilderVisitor::updateSubtreeWrapper( IRTree::ISubtreeWrapper* wrapperNew ) {
    subtreeWrapper = std::shared_ptr<IRTree::ISubtreeWrapper>( wrapperNew );
}

void CIrtBuilderVisitor::updateSubtreeWrapper( std::shared_ptr<IRTree::ISubtreeWrapper> wrapperNew ) {
    subtreeWrapper = std::move( wrapperNew );
}
