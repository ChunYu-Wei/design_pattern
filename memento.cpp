#include <iostream>
#include <vector>

/***
The Memento interface provides a method to retrieve the memento's state.
***/
class Memento
{
public:
    virtual ~Memento() {}
    virtual std::string getName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};

/***
The Concrete Memento contains the infrastructure for storing the Originator's state.
***/
class ConcreteMemento: public Memento
{
private:
    std::string _state{};
    std::string _date{};

public:
    ConcreteMemento(std::string &state)
    : _state(state)
    {
        std::time_t now = std::time(0); 
        _date = std::ctime(&now);
    }

    virtual std::string getName() const override
    {
        return _date + "/ (" + _state.substr(0, 4) + "...)"; 
    }

    virtual std::string date() const override { return _date; }
    virtual std::string state() const override { return _state; }
};

/***
The Originator holds some important state.
It also defines a method for saving the state inside a Memento,
and a method for retoring the state from it.
***/
class Originator
{
private:
    std::string _state{};

    std::string generateRandomString(int length = 10) 
    {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        int stringLength = sizeof(alphanum) - 1;

        std::string random_string;
        for (int i = 0; i < length; i++) {
          random_string += alphanum[std::rand() % stringLength];
    }
    return random_string;
  }

public:
    Originator(std::string state): _state(state)
    {
        std::cout << "Originator: My initial state is: " << _state << std::endl;
    }

    void changeState()
    {
        _state = generateRandomString();
        std::cout << "Originator: Change state to: " << _state << std::endl;
    }

    void printState() const
    {
        std::cout << _state << std::endl;
    }

    Memento *save()
    {
        return new ConcreteMemento(_state);
    }

    void restore(Memento* memento)
    {
        _state = memento->state();
    }
};

/***
The Caretaker works with all mementos and the originator via the interface
***/
class Caretaker
{
private:
    std::vector<Memento*> _mementos;
    Originator* _originator{nullptr};

public:
    Caretaker(Originator* originator)
    : _originator(originator)
    {}

    ~Caretaker()
    {
        for(Memento* m: _mementos) delete m;
    }

    void backup()
    {
        _mementos.push_back(_originator->save());
    }

    void undo()
    {
        if(_mementos.empty()) return;

        _originator->restore(_mementos.back());
        delete _mementos.back();
        _mementos.pop_back();
    }
    
    void showHistory() const
    {
        std::cout << "------Caretaker Hsitory------" << std::endl;
        for(Memento* memento: _mementos)
        {
            std::cout << memento->getName() << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;
    }
};

int main()
{
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->backup();
    originator->changeState();
    caretaker->backup();
    originator->changeState();
    caretaker->backup();
    originator->changeState();
    caretaker->showHistory();
    caretaker->undo();
    originator->printState();
    caretaker->undo();
    originator->printState();
    caretaker->undo();
    originator->printState();

    delete originator;
    delete caretaker;
}
