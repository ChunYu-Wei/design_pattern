#include <iostream>

class Component; 

/***
The Mediator interface declares a method used by components to notify
the mediator about various events.
***/
class Mediator
{
public:
    virtual ~Mediator() {}
    virtual void notify(const Component *sender, std::string event) const = 0;
};

class Component
{
protected: 
    Mediator *_mediator{nullptr};

public:
    Component(Mediator *mediator = nullptr)
    : _mediator(mediator)
    {}

    void setMediator(Mediator *mediator) { _mediator = mediator; }
};

/***
Concrete Components don't depend on other components.
***/
class ConcreteComponent1: public Component
{
public:
    void doA() const 
    { 
        std::cout << "Component1 doA" << std::endl; 
        _mediator->notify(this, "C");
    }
    void doB() const 
    { 
        std::cout << "Component1 doB" << std::endl; 
        _mediator->notify(this, "D");
    }
};

class ConcreteComponent2: public Component
{
public:
    void doC() const 
    { 
        std::cout << "Component2 doC" << std::endl; 
        _mediator->notify(this, "D");
    }
    void doD() const 
    { 
        std::cout << "Component2 doD" << std::endl; 
        _mediator->notify(this, "B");
    }
};

/***
Concrete Mediators implement cooperative behaviour by coordinating several components.
***/
class ConcreteMediator: public Mediator
{
private:

    ConcreteComponent1 *_component1{nullptr};
    ConcreteComponent2 *_component2{nullptr};

public:
    ConcreteMediator(ConcreteComponent1 *component1, ConcreteComponent2 *component2)
    : _component1(component1), _component2(component2)
    {}

    void notify(const Component *sender, std::string event) const override
    {
        if(event == "A")
            _component2->doC();
        if(event == "C")
            _component1->doB();

    }
};

int main()
{
    ConcreteComponent1 *c1 = new ConcreteComponent1();
    ConcreteComponent2 *c2 = new ConcreteComponent2();
    Mediator *mediator = new ConcreteMediator(c1, c2);
    c1->setMediator(mediator);
    c2->setMediator(mediator);
    c1->doA();
    std::cout << "------" << std::endl;
    c2->doC();

    delete c1;
    delete c2;
    delete mediator;

    return 0;
}
