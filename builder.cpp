#include <iostream>
#include <string>

/***
The product contains a string _s to represent different configurations.
***/
class Product
{
public:
    std::string _s{};
    void print() const { std::cout << _s << std::endl; }
};

/***
The builder interface specifies methods for building the products.
The different variants can be implemented in the concrete builder class.
***/
class Builder
{
public:
    Product* _product{nullptr};
    virtual ~Builder() {}
    void reset() { _product = new Product(); }
    Product* getProduct(){ return _product; }
    virtual void buildA() = 0;
    virtual void buildB() = 0;
    virtual void buildC() = 0;
};

class LowerCaseBuilder: public Builder
{
public:
    void buildA() override { _product->_s.push_back('a'); }
    void buildB() override { _product->_s.push_back('b'); }
    void buildC() override { _product->_s.push_back('c'); }
};

class UpperCaseBuilder: public Builder
{
public:
    void buildA() override { _product->_s.push_back('A'); }
    void buildB() override { _product->_s.push_back('B'); }
    void buildC() override { _product->_s.push_back('C'); }
};

/***
Optional.
The director executes the building steps in a particular set of steps or sequence.
***/

class Director
{
public:
    Builder* _builder{nullptr};

    void setBuilder(Builder* builder) { _builder = builder; }
    Product* build(bool reverse)
    {
        _builder->reset();
        if(reverse)
        {
            _builder->buildA();
            _builder->buildB();
            _builder->buildC();
        }
        else
        {
            _builder->buildC();
            _builder->buildB();
            _builder->buildA();
        }

        return _builder->getProduct();
    }
};

void ClientCode()
{
    Director* director = new Director();
    LowerCaseBuilder* lcbuilder = new LowerCaseBuilder();
    UpperCaseBuilder* ucbuilder = new UpperCaseBuilder();

    Product* product{nullptr};
    bool reverse{};

    director->setBuilder(lcbuilder);

    reverse = true;
    product = director->build(reverse);
    product->print();
    delete product;

    reverse = false;
    product = director->build(reverse);
    product->print();
    delete product;

    director->setBuilder(ucbuilder);
    
    reverse = true;
    product = director->build(reverse);
    product->print();
    delete product;

    reverse = false;
    product = director->build(reverse);
    product->print();
    delete product;

    // without using director
    lcbuilder->reset();
    lcbuilder->buildA();
    lcbuilder->buildB();
    product = lcbuilder->getProduct();
    product->print();
    delete product;
}

int main()
{
    ClientCode();
    return 0;
}
