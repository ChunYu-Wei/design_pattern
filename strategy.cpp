#include <iostream>
#include <string_view>

/***
The Startegy interface declares operations common to all supported versions
of some algorithm.
***/
class Strategy
{
public:
    virtual ~Strategy() {};
    virtual void doAlgorithm(std::string_view data) const = 0;
};

/***
The Context maintains a reference to one of the Strategy objects.
***/
class Context
{
private:
    Strategy* _strategy{nullptr};

public:
    explicit Context(Strategy *strategy)
    : _strategy(strategy)
    {}

    void setStrategy(Strategy *strategy)
    {
        if(_strategy) delete _strategy;
        _strategy = strategy;
    }

    void doSomeBusinessLogic() const
    {
        _strategy->doAlgorithm("dbcea");
    }
};

/***
Concrete Strategies implement the algorithm following the base Strategy interface.
***/

class ConcreteStrategy1: public Strategy
{
public:
    void doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(result.begin(), result.end());
        std::cout << result << std::endl;
    }
};

class ConcreteStrategy2: public Strategy
{
public:
    void doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(result.begin(), result.end(), std::greater<>());
        std::cout << result << std::endl;
    }
};

/***
The client code picks a concrete strategy and passes it to the context.
***/
int main()
{
    Context* context = new Context(new ConcreteStrategy1());
    context->doSomeBusinessLogic();
    context->setStrategy(new ConcreteStrategy2());
    context->doSomeBusinessLogic();

    delete context;
    return 0;
}
