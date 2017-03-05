#pragma once

#include <unordered_map>
#include <vector>

#include <IRTree/Nodes/Expression.h>
#include <IRTree/Temporary.h>
#include <IRTree/Label.h>

namespace IRTree {

class IAddress {
public:
    virtual ~IAddress() {}
    virtual std::shared_ptr<const CExpression> ToExpression() const = 0;
};

/**
Indicates a memory location at offset X from the frame pointer.
*/
class CAddressInFrame : public IAddress {
public:
    CAddressInFrame( const IAddress* _frameAddress, int _offset )
            : frameAddress( _frameAddress ), offset( _offset ) {}

    virtual std::shared_ptr<const CExpression> ToExpression() const override;
protected:
    const IAddress* frameAddress;
    int offset;
};

class CAddressOfField : public IAddress {
public:

    CAddressOfField (const IAddress* _thisAddress, int _offset)
        : thisAddress( _thisAddress ), offset( _offset ) {}
    std::shared_ptr<const CExpression> ToExpression() const override;

private:
    const IAddress* thisAddress;
    int offset;
};

/**
CAddressInRegister (T84) indicates that it will be held in "register" T84
*/
class CAddressInRegister : public IAddress {
public:
    CAddressInRegister( const CTemp& _temp ) : temp( _temp ) {}
    std::shared_ptr<const CExpression> ToExpression() const override;
private:
    CTemp temp;
};

class CFrame {
public:
    // CFrame( CLabel _name ) : name( _name ), maxOffsetFramePointer( 0 ) {}
    CFrame( const std::string& _className, const std::string& _methodName );

    int GetWordSize() const;

    CLabel GetName() const;
    const std::string& GetClassName() const;
    const std::string& GetMethodName() const;

    // reserves place on stack for method arguments and locals (determines offsets for them)
    void AddThisAddress();
    void AddReturnAddress();
    void AddArgumentAddress(const std::string &name);
    void AddLocalAddress(const std::string &name);
    void AddFieldAddress(const std::string &name);

    const IAddress* GetFramePointerAddress() const;
    const IAddress* GetReturnValueAddress() const;
    const IAddress* GetThisAddress() const;
    const IAddress* GetReturnAddress() const;
    const IAddress* GetAddress( const std::string& varName ) const;

    std::shared_ptr<const CExpression> ExternalCall( const std::string& functionName, std::shared_ptr<const CExpressionList> args ) const;
private:
    int nextOffsetFromFramePointer();
    int nextOffsetFromThis();
    void addAddress( const std::string& name, const IAddress* address );

    std::string className;
    std::string methodName;
    CLabel name;
    std::unordered_map<std::string, std::shared_ptr<const IAddress>> addresses;

    static const int wordSize;
    static const std::string thisAddressName;
    static const std::string returnAddressName; // return address
    static const std::string returnValueAddressName; // return value
    static const std::string framePointerAddressName;

    int maxOffsetFramePointer;
    int maxOffsetThis;
};


}