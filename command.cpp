#include <iostream>

class Receiver
{
public:
    void doSomething(const std::string task) { std::cout << task << std::endl; }
    void doSomethingElse(const std::string task) { std::cout << task << std::endl; }
};

/***
The Command interface declares a method for executing a command.
***/
class Command
{
public:
    virtual ~Command(){}
    virtual void execute() const = 0;
};


class SimpleCommand: public Command
{
public:
    void execute() const override
    {
        std::cout << "Simple command." << std::endl;
    }
};

class ComplexCommand: public Command
{
private:
    std::string _taskA{};
    std::string _taskB{};
    Receiver *_receiver{nullptr};

public:
    ComplexCommand(const std::string &taskA, const std::string &taskB, Receiver *receiver)
    : _taskA(taskA), _taskB(taskB), _receiver(receiver)
    {
    }

    void execute() const override
    {
        _receiver->doSomething(_taskA);
        _receiver->doSomethingElse(_taskB);
    }
};

/***
The Invoker is associated with one or several commands.
***/
class Invoker
{
private:
    Command *_start;
    Command *_finish;

public:
    void setCommandStart(Command* cmd){ _start = cmd; }
    void setCommandFinish(Command* cmd){ _finish = cmd; }

    void invoke()
    {
        if(_start) _start->execute();
        if(_finish) _finish->execute();
    }
};

int main()
{
    // The client code can parameterize an invoker with any commands
    Invoker *invoker = new Invoker();
    invoker->setCommandStart(new SimpleCommand());
    Receiver *receiver = new Receiver();
    invoker->setCommandFinish(new ComplexCommand("Send email", "Save report", receiver));
    invoker->invoke();
    delete invoker;
    delete receiver;

    return 0;
}
