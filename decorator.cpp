#include <iostream>
#include <string>

/***
The base Component interface defines operations that can be
altered by decorators.
 ***/
class Component
{
public:
    virtual ~Component() {};
    virtual std::string operation() const = 0;
};

class ConcreteComponent: public Component
{
public:
    std::string operation() const override
    {
        return "ConcreteComponent";
    }        
};

/***
  The base Decorator class defines the wrapping interface for
  all concrete decorators.
***/
class Decorator: public Component
{
protected:
    Component* _component{nullptr};
public:
    Decorator(Component *component)
    : _component(component)
    {}

    std::string operation() const override
    {
        return _component->operation();
    }
};

class ConcreteDecoratorA: public Decorator
{
public:
    ConcreteDecoratorA(Component *component)
    : Decorator(component)
    {}

    std::string operation() const override
    {
        return "ConcreteDecoratorA(" + Decorator::operation() + ")";
    }    
};

class ConcreteDecoratorB: public Decorator
{
public:
    ConcreteDecoratorB(Component *component)
    : Decorator{component}
    {}

    std::string operation() const override
    {
        return "ConcreteDecoratorB(" + Decorator::operation() + ")";
    }    
};

/***
The client code works with all objects using the Component interface.
***/
void ClientCode(Component* component)
{
    std::cout << component->operation() << std::endl;
}

int main()
{
    Component* simple = new ConcreteComponent();
    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    ClientCode(decorator2);

    delete simple;
    delete decorator1;
    delete decorator2;
    return 0;
}
