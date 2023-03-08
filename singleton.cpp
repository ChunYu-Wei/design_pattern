#include<iostream>

class Singleton
{
private:
    // Make the default constructor hidden from the client code
    Singleton() {}
    static Singleton* _singleton;
    int _value{};

public:
    // Singletons should not be cloneable or assignable
    Singleton(Singleton &) = delete;
    void operator=(const Singleton &) = delete;
    void printValue() const { std::cout << _value << std::endl; }
    void setValue(const int value) { _value = value; }
    // The static method that controls the access to the singleton interface
    static Singleton* getInstance() 
    { 
        if(_singleton == nullptr)
            _singleton = new Singleton();

        return _singleton; 
    }
};

Singleton* Singleton::_singleton = nullptr;


int main()
{
    Singleton* s1 = Singleton::getInstance();
    s1->setValue(1);
    s1->printValue();
    Singleton* s2 = Singleton::getInstance();
    s2->setValue(2);
    s2->printValue();
    // The value of s1 becomes 2
    s1->printValue();

    return 0;
}
