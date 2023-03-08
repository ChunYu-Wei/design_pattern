#include <iostream>
#include <string>
#include <vector>

/***
The Handler interface declares a method for building the chain of handlers
***/
class Handler
{
public:
    virtual std::string handle(const std::string &request) const = 0;
    virtual Handler* setNext(Handler* handler) = 0;
};

class AbstractHandler: public Handler
{
private:
    Handler *_handler{nullptr};

public:
    virtual std::string handle(const std::string &request) const override
    {
        if(_handler)
            return _handler->handle(request);

        return "";
    }

    virtual Handler* setNext(Handler *handler) override
    {
        _handler = handler;
        // return the handler from here let us links handlers like this:
        // handler1->setNext(handler2)->setNext(handler3)
        return handler;
    }
};

/***
All Concrete Handlers either handle a request or pass it to the next handler 
***/

class MonkeyHandler: public AbstractHandler
{
public:
    std::string handle(const std::string &request) const override
    {
        if(request == "banana")
            return "Monkey: I'll eat the " + request + ".\n";
        else return AbstractHandler::handle(request); 
    }
}; 

class SquirrelHandler: public AbstractHandler
{
public:
    std::string handle(const std::string &request) const override
    {
        if(request == "nut")
            return "Squirrel: I'll eat the " + request + ".\n";
        else return AbstractHandler::handle(request); 
    }
}; 

class DogHandler: public AbstractHandler
{
public:
    std::string handle(const std::string &request) const override
    {
        if(request == "meatball")
            return "Dog: I'll eat the " + request + ".\n";
        else return AbstractHandler::handle(request); 
    }
}; 

/***
The client code not even awares that the handler is part of a chain 
***/
void ClientCode(Handler *handler)
{
    std::vector<std::string> food = {"nut", "banana", "coffee"};
    for(const std::string &f : food)
    {
        std::cout << "Client: Who wants a " << f << "?\n";
        std::cout << handler->handle(f) << std::endl;
    }
}

int main()
{
    MonkeyHandler *monkey = new MonkeyHandler();
    SquirrelHandler *squirrel = new SquirrelHandler();
    DogHandler *dog = new DogHandler();
    dog->setNext(squirrel)->setNext(monkey);

    ClientCode(dog);
    
    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}
