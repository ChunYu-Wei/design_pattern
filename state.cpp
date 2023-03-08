#include <iostream>

class Context;

/***
The base Satte class declares methods that  all Concrete state
should implememt and provides a backreference to the Context object.
***/
class State
{
protected:
    Context *_context{nullptr};

public:
    State(Context* context = nullptr)
    : _context(context)
    {
    }

    virtual ~State() {}

    void setContext(Context *context) { _context = context; }

    virtual void handle1() = 0;
    virtual void handle2() = 0;
};

/***
The Context defines the interface to clients.
It also maintains a reference to an instance of State, which represents
the current state.
***/
class Context
{
private:
    State *_state{nullptr};

public:
    Context(State *state = nullptr)
    {
        transition(state);
    }

    ~Context() { delete _state; }

    void transition(State *state)
    {
        std::cout << "State transit to " << typeid(*state).name() << std::endl;
        if(_state) delete _state;
        state->setContext(this);
        _state = state;
    }

    void request1() { _state->handle1(); }
    void request2() { _state->handle2(); } 
};

class ConcreteState1: public State
{
public:
    void handle1() override;

    void handle2() override
    {
        std::cout << "ConcreteState1 handles request2." << std::endl;
    }
};
    
class ConcreteState2: public State
{
public:
    void handle1() override
    {
        std::cout << "ConcreteState2 handles request1." << std::endl;
    }

    void handle2() override
    {
        std::cout << "ConcreteState2 handles request2." << std::endl;
        _context->transition(new ConcreteState1());
    }
};

void ConcreteState1::handle1()
{
    std::cout << "ConcreteState1 handles request1." << std::endl;
    _context->transition(new ConcreteState2());
}

int main()
{
    Context *context = new Context(new ConcreteState1());
    context->request1();
    context->request2();

    delete context;

}
