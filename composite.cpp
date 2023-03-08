#include <iostream>
#include <list>
#include <string>

/***
The base Component class declares common operations for 
both simple and complex objects of a composition.
***/
class Component
{
protected:
    Component* _parent{nullptr};        

public:
    virtual ~Component() {};
    void setParent(Component *parent){ _parent = parent; }
    Component* getParent() const { return _parent; }
    virtual void addComponent(Component *component) {}
    virtual void removeComponent(Component *component) {}
    virtual std::string operation() const = 0;
    virtual bool isComposite() const { return false; }
};

/***
A leaf can't have any children.
A composite has children.
Usually, it's the Leaf objects that do the actual work, whereas
Composite objects only delegate to their sub-components.
***/
class Leaf: public Component
{
public:
    bool isComposite() const override { return true; }
    std::string operation() const override { return "Leaf"; }
};

class Composite: public Component
{
protected:
    std::list<Component*> _children;
public:
    void addComponent(Component *component) override
    {
        _children.push_back(component);
        component->setParent(this);
    }

    void removeComponent(Component *component) override
    {
        _children.remove(component);
        component->setParent(nullptr);
    }

    bool isComposite() const override { return true; }

    std::string operation() const override
    {
        std::string result;
        for(const Component* c: _children)
        {
            if(c == _children.back())
                result += c->operation();
            else
                result += c->operation() + "+";
        }
        return "Branch(" + result + ')';
    }
};

void ClientCode(Component *component)
{
    std::cout << "RESULT: " << component->operation() << std::endl;
}

int main()
{
    Component *tree = new Composite();
    Component *branch1 = new Composite();

    Component *leaf_1 = new Leaf();
    Component *leaf_2 = new Leaf();
    Component *leaf_3 = new Leaf();
    branch1->addComponent(leaf_1);
    branch1->addComponent(leaf_2);
    Component *branch2 = new Composite();
    branch2->addComponent(leaf_3);
    tree->addComponent(branch1);
    tree->addComponent(branch2);
    ClientCode(tree);

    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;
    return 0;
}
