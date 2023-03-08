#include <iostream>
#include <list>
#include <vector>

/***
The Subject contains some important state and notifies observers when
the state changes.
***/

class IObserver
{
public:
    virtual ~IObserver() {}
    virtual  void update(const std::string &message) = 0;
};

class ISubject
{
public:
    virtual ~ISubject() {};
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notify() = 0;
};

class Subject: public ISubject
{
private:
    std::list<IObserver*> _observers;
    std::string _message{};

public:
    void attach(IObserver *observer) override
    {
        observer->update(_message);
        _observers.push_back(observer);
    }

    void detach(IObserver *observer) override
    {
        _observers.remove(observer);
    }

    void notify() override
    {
        for(IObserver* observer: _observers)
        {
            observer->update(_message);
        }
    }

    void updateMessage(const std::string &message)
    {
        _message = message;
        notify();
    }
};

class Observer: IObserver
{
private:
    Subject* _subject{nullptr};
    std::string _message{};
    static int _number;
    int _id{};

public:
    Observer(Subject* subject)
    : _subject(subject)
    {
        _id = Observer::_number;
        ++Observer::_number;
        _subject->attach(this);
    }

    void update(const std::string &message) override
    {
        _message = message;
    }

    void removeFromSubject()
    {
        _subject->detach(this);
    }

    void print()
    {
        std::cout << "Ob(" << _id << "): " << _message << std::endl;
    }
};

int Observer::_number = 0;

int main()
{
    Subject* subject = new Subject();
    std::vector<Observer*> obList;
    for(int i = 0; i < 5; ++i)
        obList.push_back(new Observer(subject));
    
    subject->updateMessage("Hi");
    std::cout << "----Observers' Messages----" << std::endl;
    for(Observer* ob: obList)
        ob->print();

    obList[3]->removeFromSubject();
    obList[4]->removeFromSubject();
    std::cout << "----Observers' Messages----" << std::endl;
    subject->updateMessage("How are you?");
    for(Observer* ob: obList)
        ob->print();

    return 0;
}
