#include <iostream>

/***
The Implementation interface provides only primitive operations.
It doesn't have to match the Abstraction's interface.
***/
class Implementation
{
public:
    virtual ~Implementation() {}
    virtual std::string operation() const = 0;
};

class ConcreteImplementation1: public Implementation
{
public:
    virtual std::string operation() const override
    {
        return "Implementation 1";
    }
};

class ConcreteImplementation2: public Implementation
{
public:
    virtual std::string operation() const override
    {
        return "Implementation 2";
    }
};

/***
The Abstraction maintains reference to an object of the Implementation.
Abstraction defines higher-level operations based on the primitive operations in Implementation.
***/
class Abstraction
{
protected:
    Implementation* _implementation{nullptr};

public:
    Abstraction(Implementation* implementation)
    : _implementation{implementation}
    {}

    virtual std::string API() const
    {
        return "Base API: " + _implementation->operation();
    }
};

class ExtendedAbstraction: public Abstraction
{
public:
    ExtendedAbstraction(Implementation* implementation)
    : Abstraction(implementation)
    {}

    std::string API() const override
    {
        return "Extended API: " + _implementation->operation();
    }
};

void ClientCode(const Abstraction* abstraction)
{
    std::cout << abstraction->API() << std::endl;
}

int main()
{
    Implementation* implementation = new ConcreteImplementation1();
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(abstraction);
    delete implementation;
    delete abstraction;
    implementation = new ConcreteImplementation2();
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(abstraction);
    delete implementation;
    delete abstraction;
}
