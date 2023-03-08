#include <iostream>

/***
The Target defines the domain-specific interface used by the client code.
***/
class Target
{
public:
    virtual ~Target() {};
    virtual std::string request() const { return "Target: The default target's behavior."; }
};

/***
The interface of Adaptee is incompatible with the existing client code.
***/
class Adaptee
{
public:
    std::string specificrequest() const { return ".eetpadA eht fo riovaheb laicepS"; }
};

/***
The Adapter makes the Adaptee's interface compatible with the Target's interface.
***/
class Adapter: public Target
{
private:
    Adaptee* _adaptee{nullptr};

public:
    Adapter(Adaptee* adaptee)
    : _adaptee(adaptee)
    {}

    std::string request() const override
    {
        std::string s = _adaptee->specificrequest();
        std::reverse(s.begin(), s.end());
        return s;
    }
};

/***
The client code follows the Target interface.
***/
void ClientCode(const Target *target)
{
    std::cout << target->request() << std::endl;
}

int main()
{
    Target* target = new Target();
    ClientCode(target);

    Adaptee *adaptee = new Adaptee();
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);

    return 0;
}
