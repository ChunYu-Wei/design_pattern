# Design Pattern
Design patterns are typical solutions to commonly occurring problems in software design. They are like pre-made blueprints that you can customize to solve a recurring design problem in your code.

Reference: https://refactoring.guru/design-patterns



## Creational patterns
Creational patterns provide various object creation mechanisms, which increase flexibility and reuse of existing code.
### Factory Method
A creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.

### Abstract Factory 
A creational design pattern that lets you produce families of related objects without specifying their concrete classes.

### Builder
A creational design pattern that lets you construct complex objects step by step. 

### Prototype
A creational design pattern that lets you copy existing objects without making your code dependent on their classes.

### Singleton
A creational design pattern that lets you ensure that a class has only one instance while providing a global access point to this instance.

## Structural Design Patterns
Structural design patterns explain how to assemble objects and classes into larger structures, while keeping these structures flexible and efficient.

### Adapter
A structural design pattern that allows objects with incompatible interfaces to collaborate.

### Bridge 
A structural design pattern that lets you split a large class or a set of closely related classes into two separate hierarchies—abstraction.

### Composite 
A structural design pattern that lets you compose objects into tree structures.

### Decorator
A structural design pattern that lets you attach new behaviors to objects by placing these objects inside special wrapper objects that contain the behaviors.

### Facade 
A structural design pattern that provides a simplified interface to a library, a framework, or any other complex set of classes.

### Flyweight
A structural design pattern that lets you fit more objects into the available amount of RAM by sharing common parts of state between multiple objects instead of keeping all of the data in each object.

### Proxy
A structural design pattern that controls access to the original object, allowing you to perform something either before or after the request gets through to the original object.

## Behavioral design patterns
Behavioral design patterns are concerned with algorithms and the assignment of responsibilities between objects.
### Chain 
A behavioral design pattern that lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain.

### Command
A behavioral design pattern that lets you pass requests as a method arguments, delay or queue a request’s execution, and support undoable operations.

### Iterator
A behavioral design pattern that lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.).

### Mediator 
A behavioral design pattern that lets you reduce chaotic dependencies between objects. 

### Memento 
A behavioral design pattern that lets you save and restore the previous state of an object without revealing the details of its implementation.

### Observer
A behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

### State 
A behavioral design pattern that lets an object alter its behavior when its internal state changes. It appears as if the object changed its class.

### Strategy
A behavioral design pattern that lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable.

### Template Method 
A behavioral design pattern that defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure.

### Visitor
A behavioral design pattern that lets you separate algorithms from the objects on which they operate.
