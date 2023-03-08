#include <iostream>

/***
The Template Method defines the skeleton of an algorithm
***/
class AbstractClass
{
public:
    void templateMethod() const
    {
        baseOperation1();
        requiredOperation1();
        hook1();
        baseOperation2();
        requiredOperation2();
        hook2();
    }

    // These operations already have implementations
    void baseOperation1() const { std::cout << "Base operation 1" << std::endl; }
    void baseOperation2() const { std::cout << "Base operation 2" << std::endl; }
    // These operations have to be implemented in concrete classes
    virtual void requiredOperation1() const = 0;
    virtual void requiredOperation2() const = 0;
    // Hooks provide optional extension
    virtual void hook1() const {}
    virtual void hook2() const {}
};

class ConcreteClass1: public AbstractClass
{
public:
    void requiredOperation1() const override
    {
        std::cout << "ConcreteClass1: Required operation 1" << std::endl;
    }

    void requiredOperation2() const override
    {
        std::cout << "ConcreteClass1: Required operation 2" << std::endl;
    }
};

class ConcreteClass2: public AbstractClass
{
public:
    void requiredOperation1() const override
    {
        std::cout << "ConcreteClass2: Required operation 1" << std::endl;
    }

    void requiredOperation2() const override
    {
        std::cout << "ConcreteClass2: Required operation 2" << std::endl;
    }

    void hook1() const override
    {
        std::cout << "ConcreteClasse2: Hook 1" << std::endl;
    }
};

int main()
{
    ConcreteClass1 *c1 = new ConcreteClass1();
    c1->templateMethod();

    std::cout << "----------" << std::endl;

    ConcreteClass2 *c2 = new ConcreteClass2();
    c2->templateMethod();

    delete c1;
    delete c2;
}

