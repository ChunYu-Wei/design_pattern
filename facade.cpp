#include <iostream>

class Subsystem1
{
public:
    std::string init() const { return "Subsystem1: Ready!\n"; }
    std::string operation() const { return "Subsystem1: Go!\n"; }
};

class Subsystem2
{
public:
    std::string init() const { return "Subsystem2: Ready!\n"; }
    std::string operation() const { return "Subsystem2: Go!\n"; }
};

/***
The Facade class provides a simple interface to the complex
logic of several subsystems.
***/
class Facade
{
protected:
    Subsystem1* _subsystem1{nullptr};
    Subsystem2* _subsystem2{nullptr};

public:
    Facade
    (
        Subsystem1 *subsystem1 = nullptr,
        Subsystem2 *subsystem2 = nullptr
    ) 
    {
        _subsystem1 = subsystem1 ? : new Subsystem1();
        _subsystem2 = subsystem2 ? : new Subsystem2();
    }

    ~Facade() 
    {
        delete _subsystem1;
        delete _subsystem2;
    }

    std::string operation()
    {
        std::string result;
        result += _subsystem1->init();
        result += _subsystem2->init();
        result += _subsystem1->operation();
        result += _subsystem2->operation();
        return result;
    }
};


void ClientCode(Facade *facade)
{
    std::cout << facade->operation();
}

int main()
{
    Facade* facade = new Facade();
    ClientCode(facade);
    return 0;
}
