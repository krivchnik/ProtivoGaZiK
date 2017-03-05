#include <IRTree/Frame.h>
#include <cassert>

using namespace IRTree;

std::shared_ptr<const CExpression> CAddressInFrame::ToExpression() const {
    std::shared_ptr<const CExpression> offsetExpression;
    if ( offset != 0 ) {
        offsetExpression = std::shared_ptr<const CExpression>(
            new CBinaryExpression(
                TOperatorType::OT_Plus,
                frameAddress->ToExpression(),
                std::shared_ptr<const CExpression>(
                    new CConstExpression( offset )
                )
            )
        );
    } else {
        offsetExpression = frameAddress->ToExpression();
    }
    return std::shared_ptr<const CExpression>(new CMemExpression(offsetExpression));
}

std::shared_ptr<const CExpression> CAddressOfField::ToExpression() const {
    std::shared_ptr<const CExpression> offsetExpression;
    if ( offset != 0 ) {
        offsetExpression = std::shared_ptr<const CExpression>(
            new CBinaryExpression(
                TOperatorType::OT_Plus,
                thisAddress->ToExpression(),
                std::shared_ptr<const CExpression>(
                    new CConstExpression( offset )
                )
            )
        );
    } else {
        offsetExpression = thisAddress->ToExpression();
    }
    return std::shared_ptr<CExpression>(new CMemExpression(offsetExpression));
}

std::shared_ptr<const CExpression> CAddressInRegister::ToExpression() const {
    return std::shared_ptr<const CExpression>(
        new CTempExpression( temp )
    );
}


const int CFrame::wordSize = 4;
const std::string CFrame::thisAddressName = "$this";
const std::string CFrame::returnAddressName = "$return";

const std::string CFrame::returnValueAddressName = "$rv";
const std::string CFrame::framePointerAddressName = "$fp";

CFrame::CFrame( const std::string& _className, const std::string& _methodName )
    : className( _className ), methodName( _methodName ), name( className + "$" + methodName ),
      maxOffsetFramePointer( 0 ), maxOffsetThis( 0 ) {
    addAddress( framePointerAddressName, new CAddressInRegister( CTemp( framePointerAddressName ) ) );
    addAddress( returnValueAddressName, new CAddressInRegister( CTemp( returnValueAddressName ) ) );
}

int CFrame::GetWordSize() const {
    return wordSize;
}

CLabel CFrame::GetName() const {
    return name;
}

const std::string& CFrame::GetClassName() const {
    return className;
}

const std::string& CFrame::GetMethodName() const {
    return methodName;
}

void CFrame::AddThisAddress() {
    AddArgumentAddress(thisAddressName);
}

void CFrame::AddReturnAddress() {
    AddArgumentAddress(returnAddressName);
}

void CFrame::AddArgumentAddress(const std::string &name) {
    AddLocalAddress(name);
}

void CFrame::AddLocalAddress(const std::string &name) {
    const CAddressInFrame* address = new CAddressInFrame(GetFramePointerAddress(), nextOffsetFromFramePointer());
    addAddress( name, address );
}

void CFrame::AddFieldAddress(const std::string &name) {
    const CAddressOfField* address = new CAddressOfField(GetThisAddress(), nextOffsetFromThis());
    addAddress( name, address );
}

const IAddress* CFrame::GetAddress( const std::string& varName ) const {
    auto addressIt = addresses.find( varName );
    const IAddress* res = nullptr;
    if ( addressIt != addresses.end() ) {
        res = addressIt->second.get();
    }
    return res;
}

const IAddress* CFrame::GetThisAddress() const {
    return GetAddress( thisAddressName );
}

const IAddress* CFrame::GetReturnAddress() const {
    return GetAddress( returnAddressName );
}

const IAddress* CFrame::GetFramePointerAddress() const {
    return GetAddress( framePointerAddressName );
}

const IAddress* CFrame::GetReturnValueAddress() const {
    return GetAddress( returnValueAddressName );
}

std::shared_ptr<const CExpression> CFrame::ExternalCall( const std::string& functionName, std::shared_ptr<const CExpressionList> args ) const {
    return std::shared_ptr<const CExpression>(
        new IRTree::CCallExpression(
            std::shared_ptr<const CExpression>(
                new CNameExpression( CLabel( functionName ) )
            ),
            args
        )
    );
}

int CFrame::nextOffsetFromFramePointer() {
    int tmp = maxOffsetFramePointer;
    maxOffsetFramePointer += wordSize;
    return tmp;
}

int CFrame::nextOffsetFromThis() {
    int tmp = maxOffsetThis;
    maxOffsetThis += wordSize;
    return tmp;
}

void CFrame::addAddress( const std::string& name, const IAddress* address ) {
    auto result = addresses.emplace( name, std::shared_ptr<const IAddress>( address ) );
    // overwriting may happen in case there is a field and a local/argument with the same name
    // assert( result.second );
}
