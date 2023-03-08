#include <iostream>

/***
The Service declares the interface of the Service.
***/
class Service
{
public:
    virtual ~Service() {}
    virtual void operation() const = 0;
};


class ConcreteService: public Service
{
public:
    void operation() const override
    {
        std::cout << "Concrete service code." << std::endl;
    }
};

/***
The Proxy follows the Service interface.
It has a reference to a service object. After the proxy finishes
its procesesing, it passes the request to the service object.
***/
class Proxy: public Service
{
private:
    ConcreteService *_service{nullptr};

public:
    Proxy(ConcreteService *service)
    : _service(service)
    {}

    void operation() const override
    {
        std::cout << "Proxy code first, then ";
        _service->operation();
    } 
};

/***
The Client should work with both services and proxies via the same interface.
***/
void ClientCode(Service *service)
{
    service->operation();
}

int main()
{
    ConcreteService *service = new ConcreteService();
    ClientCode(service);

    Proxy *proxy = new Proxy(service);
    ClientCode(proxy);

    delete service;
    delete proxy;

    return 0;
}
