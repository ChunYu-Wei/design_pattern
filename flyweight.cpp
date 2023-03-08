#include <iostream>
#include <string>
#include <unordered_map>

/***
Shares common parts of state between multiple objects,
in order to save RAM.
 ***/
class SharedState
{
public:
    std::string _brand{};
    std::string _model{};
    std::string _color{};

    SharedState(const std::string &brand, const std::string &model, const std::string &color)
    : _brand(brand), _model(model), _color(color)
    {}

    friend std::ostream &operator<<(std::ostream &os, const SharedState &ss)
    {
        return os << "[" << ss._brand << ", " << ss._model << ", " << ss._color << "]";
    }
};

class UniqueState
{
public:
    std::string _owner{};
    std::string _plates{};

    UniqueState(const std::string &owner, const std::string &plates)
    : _owner(owner), _plates(plates)
    {}

    friend std::ostream &operator<<(std::ostream &os, const UniqueState &us)
    {
        return os << '[' << us._owner << ", " << us._plates << ']';
    }

};

/***
The Flyweight stores a commom portion of the state.
It also accepts the rest of the unique state via its method parameters.
***/
class Flyweight
{
private:
    SharedState *_ss{nullptr};

public:
    Flyweight(const SharedState *ss) 
    :_ss(new SharedState(*ss))
    {}

    SharedState *getSharedState() const { return _ss; }
    void operation(const UniqueState &us) const
    {
        std::cout << "Flyweight: shared(" << *_ss << ") and unique(" << us << std::endl;
    }

};

/***
The Flyweight Factory creates and manages the Flyweight objects.
It ensures that flyweights are shared correctly by either returning
an existing instance or creates a new one.
***/
class FlyweightFactory
{
private:
    std::unordered_map<std::string, Flyweight> _flyweights;

    std::string getKey(const SharedState &ss)
    {
        return ss._brand + "_" + ss._model + "_" + ss._color;
    } 

public:
    FlyweightFactory(std::initializer_list<SharedState> sss)
    {
        for(const SharedState &ss: sss) 
        {
            _flyweights.insert(std::make_pair<std::string, Flyweight>(getKey(ss), Flyweight(&ss)));
        }
    }

    Flyweight getFlyweight(const SharedState &ss)
    {
        std::string key = getKey(ss);
        if(_flyweights.find(key) == _flyweights.end())
            _flyweights.insert(std::make_pair(key, Flyweight(&ss)));

        return _flyweights.at(key);
    }

    void listFlyweights() const
    {
        std::cout << "List Flyweights: " << std::endl;
        for(auto &it: _flyweights)
        {
            std::cout << *(it.second.getSharedState()) << std::endl;
        }
    }
};

void addCarToDatabase
(
    FlyweightFactory *ff,
    const std::string &plates,
    const std::string &owner,
    const std::string &brand,
    const std::string &model,
    const std::string &color 
)
{
    const Flyweight &flyweight = ff->getFlyweight({brand, model, color});
    flyweight.operation({owner, plates});
}

/***
The client code usually creates a bunch of pre-populated flyweights in the
initialization stage of the application.
***/
int main()
{
    FlyweightFactory *factory = new FlyweightFactory({{"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"}});
    factory->listFlyweights();

    addCarToDatabase
    (
        factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "M5",
        "red"
    );

    addCarToDatabase
    (
        factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "X1",
        "red"
    );

    factory->listFlyweights();
    delete factory;

    return 0;
}
