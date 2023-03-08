#include <iostream>
#include <string>
#include <vector>

/***
  The product has coloning ability.
***/
class Product
{
protected:
    std::string _food;
    std::string _drink;

public:
    Product(const std::string &food, const std::string &drink)
    : _food(food), _drink(drink)
    {}
    virtual ~Product() {};
    virtual Product* clone() const = 0;
    virtual void print() const  = 0;
};

class HealthyProduct: public Product
{
public:
    HealthyProduct(const std::string &food, const std::string &drink)
    : Product(food, drink)
    {}
    Product* clone() const override { return new HealthyProduct(*this); } 
    void print() const override 
    { 
        std::cout << "Healthy product: ";
        std::cout << "food=" << _food;
        std::cout << ' ';
        std::cout << "drink=" << _drink;
        std::cout << std::endl;
    }
};

class TastyProduct: public Product
{
public:
    TastyProduct(const std::string &food, const std::string &drink)
    : Product(food, drink)
    {}
    Product* clone() const override { return new TastyProduct(*this); } 
    void print() const override 
    { 
        std::cout << "Tasty product: ";
        std::cout << "food=" << _food;
        std::cout << ' ';
        std::cout << "drink=" << _drink;
        std::cout << std::endl;
    }
};

/***
The product registry provides an easy way to access frequently-used prototypes.
Each time we watn to create a product, we can use the existing ones and clone those.
***/
class ProductRegistry
{
private:
    std::vector<Product*> _products;

public:
    ProductRegistry()
    {
        _products.resize(4);
        _products[0] = new HealthyProduct("Salad", "Water");
        _products[1] = new HealthyProduct("Chicken", "Juice");
        _products[2] = new TastyProduct("Hamberger", "Coke");
        _products[3] = new TastyProduct("Icecream", "Boba");
    }

    Product* produceProduct(int i)
    {
        return _products[i]->clone();
    }
};

void ClientCode()
{
    ProductRegistry* registry = new ProductRegistry();
    Product* product = nullptr;

    product = registry->produceProduct(0);
    product->print();
    delete product;


    product = registry->produceProduct(1);
    product->print();
    delete product;

    product = registry->produceProduct(2);
    product->print();
    delete product;

    product = registry->produceProduct(3);
    product->print();
    delete product;
}

int main()
{
    ClientCode();
    return 0;
}
