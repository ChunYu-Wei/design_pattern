#include <iostream>
#include <vector>

template<typename T>
class Container;

template<typename T>
class Iterator
{
public:
    Iterator(Container<T> *container)
    : _container(container)
    {
        _idx = 0;
    }

    void next() { ++_idx; };
    bool isDone() { return (_idx == _container->size()); }
    T current() { return _container->get(_idx); };

private:
    Container<T> *_container;
    int _idx{};
};

template<typename T>
class Container
{
friend class Iterator<T>;

public:
    void add(const T t) { _vec.push_back(t); }
    int size() { return _vec.size(); }
    int get(int i){ return _vec[i]; }


    Iterator<T>* createIterator() { return new Iterator<T>(this); }

private:
    std::vector<T> _vec;
};


void ClientCode()
{
    Container<int> *cont = new Container<int>();
    for(int i = 0; i < 10; ++i)
        cont->add(i);

    Iterator<int>* it = cont->createIterator();
    for(;!it->isDone(); it->next())
    {
        std::cout << it->current() << std::endl;
    }
}

int main()
{
    ClientCode();
    return 0;
}
