#include<iostream>

/***
There are three types of product: chair, sofa, and table.
Each product have an interface class and three concrete class, 
which indicates the three variant of product: Art, Vic, adn Mod.
***/
class Chair
{
public:
    virtual ~Chair() {};
    virtual void method() const = 0;

};

class ArtChair: public Chair
{
public:
    virtual void method() const override { std::cout << "ArtChair" << std::endl; }        
};

class VicChair: public Chair
{
public:
    virtual void method() const override { std::cout << "VicChair" << std::endl; }        
};

class ModChair: public Chair
{
public:
    virtual void method() const override { std::cout << "ModChair" << std::endl; }        
};

class Sofa
{
public:
    virtual ~Sofa() {};
    virtual void method() const = 0;
};

class ArtSofa: public Sofa
{
public:
    virtual void method() const override { std::cout << "ArtSofa" << std::endl; }        
};

class VicSofa: public Sofa
{
public:
    virtual void method() const override { std::cout << "VicSofa" << std::endl; }        
};

class ModSofa: public Sofa
{
public:
    virtual void method() const override { std::cout << "ModSofa" << std::endl; }        
};

class Table
{
public:
    virtual ~Table() {};
    virtual void method() const = 0;
};

class ArtTable: public Table
{
public:
    virtual void method() const override { std::cout << "ArtTable" << std::endl; }        
};

class VicTable: public Table
{
public:
    virtual void method() const override { std::cout << "VicTable" << std::endl; }        
};

class ModTable: public Table
{
public:
    virtual void method() const override { std::cout << "ModTable" << std::endl; }        
};

/***
The abstract factory interface class declares a set of creation methods.
***/
class AbstractFactory
{
public:
    virtual Chair* createChair() const = 0;
    virtual Sofa* createSofa() const = 0;
    virtual Table* createTable() const = 0;
};

/***
The concrete factory class create a family of products belong to a single variant.
***/

class ArtFactory: public AbstractFactory
{
public:
    Chair* createChair() const override
    {
        return new ArtChair();
    }        

    Sofa* createSofa() const override
    {
        return new ArtSofa();
    }        

    Table* createTable() const override
    {
        return new ArtTable();
    }        
};

class VicFactory: public AbstractFactory
{
public:
    Chair* createChair() const override
    {
        return new VicChair();
    }        

    Sofa* createSofa() const override
    {
        return new VicSofa();
    }        

    Table* createTable() const override
    {
        return new VicTable();
    }        
};

class ModFactory: public AbstractFactory
{
public:
    Chair* createChair() const override
    {
        return new ModChair();
    }        

    Sofa* createSofa() const override
    {
        return new ModSofa();
    }        

    Table* createTable() const override
    {
        return new ModTable();
    }        
};

/***
The client create products in a single variant.
***/

void ClientCode(AbstractFactory* fac)
{
    Chair* chair = fac->createChair();
    chair->method();

    Sofa* sofa = fac->createSofa();
    sofa->method();

    Table* table = fac->createTable();
    table->method();
}

int main()
{
    ArtFactory* artFac = new ArtFactory();
    ClientCode(artFac);

    VicFactory* vicFac = new VicFactory();
    ClientCode(vicFac);

    ModFactory* modFac = new ModFactory();
    ClientCode(modFac);

    return 0;
}

