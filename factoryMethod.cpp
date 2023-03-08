#include<iostream>

/***
The product interface class contains a method 'deliver', 
which is implemented by the concrete product class.
***/
class Transport
{
public:
    virtual void deliver() const = 0;
    virtual ~Transport() {};

};

/***
A concrete product class implements the interface 'deliver'.
***/
class Truck: public Transport
{
public:
    void deliver () const override { std::cout << "Truck deliver." << std::endl; }
};

/***
A concrete product class implements the interface 'deliver'.
***/
class Ship: public Transport
{
public:
    void deliver () const override { std::cout << "Ship deliver." << std::endl; }
};

/***
The factory interface class contains a factory method 'create',
which is implemented by the concrete factory class.
***/
class Factory
{
public:
    virtual Transport* create() const = 0;
    virtual ~Factory() {};
};

/***
A concrete factory class implements tge interface 'create'.
***/
class TruckFactory: public Factory
{
public:
    Transport* create() const override 
    {
        return new Truck();
    }
};

/***
A concrete factory class implements tge interface 'create'.
***/
class ShipFactory: public Factory
{
public:
    Transport* create() const override 
    {
        return new Ship();
    }
};

/***
The client uses factory interface to create concrete products.
***/
void ClientCode(Factory* factory)
{
    Transport* t = factory->create();
    t->deliver();
}

int main()
{
    Factory * factory1 = new TruckFactory();
    ClientCode(factory1);

    Factory * factory2 = new ShipFactory();
    ClientCode(factory2);
    return 0;
}
