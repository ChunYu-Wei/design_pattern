#include <iostream>
#include <vector>

class Component;

/***
The Visitor Interface declares a visiting method to Components.
***/
class Visitor
{
public:
    virtual ~Visitor() {}
    virtual void visitComponent(const Component *component) const = 0;
};

/***
The Component interface declares an 'accept' method taking
the Visitor interface as an argement.
***/
class Component
{
public:
    virtual ~Component() {}
    virtual void accept(Visitor* visitor) const = 0;
    virtual void method() const = 0;
};

/***
Each Concrete Component must implement the 'accept' method such that
it calls the visitor's method corresponding to the component's class.
***/
class ConcreteComponentA: public Component
{
public:
    void accept(Visitor* visitor) const override
    {
        visitor->visitComponent(this);
    }

    void method() const override
    {
        std::cout << "A" << std::endl;
    }
};

class ConcreteComponentB: public Component
{
public:
    void accept(Visitor* visitor) const override
    {
        visitor->visitComponent(this);
    }

    void method() const override
    {
        std::cout << "B" << std::endl;
    }
};


/***
Concrete Visitors implement several versions of the same algorithm,
which can work with all concrete componenet classes.
***/
class ConcreteVisitor1 : public Visitor
{
public:
    void visitComponent(const Component* component) const override
    {
        std::cout << "ConcreteVisitor1 + ";
        component->method();
    }
};

class ConcreteVisitor2 : public Visitor
{
public:
    void visitComponent(const Component* component) const override
    {
        std::cout << "ConcreteVisitor2 + ";
        component->method();
    }
};

void ClientCode(std::vector<Component*> &components, Visitor *visitor)
{
    for(Component *comp: components)
        comp->accept(visitor);

}

int main() 
{
    std::vector<Component*> components = {new ConcreteComponentA, new ConcreteComponentB};
    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component *comp : components)
        delete comp;

    delete visitor1;
    delete visitor2;

    return 0;
}
