# Classes in C

> "Most good programmers do programming not because they expect to get paid or get adulation by the public, but because it is fun to program." -Linus Torvalds

This project is about constructing classes in C with my low experience with this type of thing.

In the proccess of learning how, I will pass through what a pointer is, what a struct is and, of course, what a class is.

Don't expect to be good as some of these big projects that a professional with years of experience make, also because it's on the earliest versions. Besides that, I'm trying my best to provide correct and rich informations about this subject.

There is lots of things to improve, polish and finish.


---
- [Introduction](#introduction)
	- [What is a pointer](#what-is-a-pointer)
		- [Pointer Arithmetic](#pointer-arithmetic)
	- [What is a structure](#what-is-a-structure)
	- [What is a function](#what-is-a-function)
- [Developing the Class system](#developing-the-class-system)
	- [Starting the development](#starting-the-development)
		- [Adding a way to make non-static methods](#adding-a-way-to-make-non-static-methods)
	- [Advanced system development](#advanced-system-development)
		- [Adding a destructor function](#adding-a-destructor-function)
		- [Improving the performance](#improving-the-performance)
		- [Creating an access modifier system](#creating-an-access-modifier-system)
---

# Introduction

>"A structure is just a fancy pointer, and a class is just a fancy structure."

Knowing this, we can first thought of what a class is composed of, and it's about this:
- Attributes
- Methods

Well, attributes are already built-in in the structures, so our problem is just the methods.

But, before we start our development, what is a pointer?

## What is a pointer

A pointer is a variable that stores some memory address. It can be found with the size of 8 bytes in a 64-bits processor, 4 bytes in a 32-bits processor and 2 bytes in a 16-bits processor.

All the pointers necessity is based on the access of memory with some address as reference.

We can imagine as a road, you can reference a house based on the start of the street, but this is bad when you have multiple deliveries, some complex ones, and a long street. So, you start to reference by something closer, and that is the pointer.

Also, pointers are what is used to create raw arrays, by using pointer arithmetic.

Pointers can have types, from primitive/primary types to structures. They don't change the content of the pointer, but how the compiler see the pointer and consequently how the arithmetic is made. 

But what is that `pointer artihmentic` that was mentioned so many times?
### Pointer Arithmetic

Pointer arithmetic is simple, is just take the address of the pointer and sum with a value to get another address value.

Imagine that this table is the memory:

| Address (hex) | Value (binary) |
| ------------- | -------------- |
| 0000          | 0000 0000      |
| 0001          | 0000 0000      |
| 0002          | 0000 0000      |
| 0003          | 0000 0000      |
| 0004          | 0000 0000      |
| 0005          | 0000 0000      |
| 0006          | 1111 1111      |
| 0007          | 1111 1000      |
| [...]         | [...]          |
| FFF8          | 0000 0000      |
| FFF9          | 0000 0000      |
| FFFA          | 0000 0000      |
| FFFB          | 0000 0101      |
| FFFC          | 0000 0000      |
| FFFD          | 0000 0000      |
| FFFE          | 0000 0000      |
| FFFF          | 0000 1010      |

At the address 0000x0 there is an int pointer at the stack that the value is FFF8x0, so it points to a int at the heap with value 5. If it is an array, to get the next element, it need to get the int at the address `FFF8x0 + 0004x0`, and that is easily done with `pointer[1]`.

And that is where the pointer type comes to play. The compiler only knows that you need to add 4 (bytes) because the size of an int is 4 bytes.

>Pointer arithmetic with structures is a bit more complex, the explanation is TBA.

## What is a structure

A structure is a way that C deals with the problems when the project begins to be too large and has problems with the amount of variables and the lack of pattern rules between then.

Here is an example of structure:
``` c
struct Person {
	char *name;
	int age;
}

struct Person person;
person.name = "rakRandom";
person.age = 16;
```

Structs can also be transformed into a type by using the `typedef` keyword, like this:
``` c
typedef struct Person {
	char *name;
	int age;
}

Person person;
person.name = "rakRandom";
person.age = 16;
```

Diving deeper into what a struct is, it is a way to store variables inside them, and that is all. But while this concept is simple, the fact that these variables can be pointers is interesting for us, that want to create a Class in C.

One of the types of pointers that can be created is the function pointer. But, before going further, what is, in fact, a function or method?

## What is a function

Basically, a function is a bunch of machine code that generally are stored at the executable file and then passed to the `.code` memory area. But what we use to call the function when we are programming is not exactly the function, it is a pointer to it.

We can define a function pointer in C using the following syntax rule:

`<return type> (*<variable name/function name>)(<parameter types>)`

> _Yes, it was all pointers, from the beginning to the end._

Here is an example:
``` c
#include <stdio.h>  // C Standart Input/Output library

// Original function
int my_add_function(int x, int y) {
    return x + y;
}

int main() {
    // Pointer that points to the same memory space as 'my_add_function'
    int (*add)(int,int) = my_add_function;
    
    printf("%d\n", add(1, 1)); // Output: 2
    
    return 0;
}
```

# Developing the Class system

## Starting the development

With all this in mind, we can start to develop our system, it should look something like this:

>`thing.h`
``` c
typedef struct {
    void (*showThing)();
} Thing;
```

Then, we define the struct pointer value as the same as the function `showThing` address:
>`main.c`
``` c
#include <stdio.h>
#include "thing.h"

void showThing() {
    printf("Something!\n");
}

int main() {
    Thing thing;

    thing.showThing = showThing;
}
```

But there is a problem, we don't know yet how to make a non-static method.

A non-static method depends on the object, it can reference the object and its attributes. So, how can you do this?

### Adding a way to make non-static methods

If we try to do this by passing the pointer as a parameter, this happens:
``` c
typedef struct {
    void (*showThing)(Thing*);  // Error: `Thing` is not declared
} Thing;
```

We can't say that a `Thing` pointer type variable is passed as parameter, because it wasn't created yet.

To fix this, we can use a `void` pointer to represent an `Any`-like type or a generic `<T>` thing.

But life doesn't go so smooth and, besides being ass ugly, it throws a `-Wincompatible-pointer-types` error if compiled with GCC, because it doesn't recognize `void *` as a generic or some shit like that.

>Note: In most online compilers, this approach will work.

To fix this two issues (being ugly and error prone), we need to go back to a basic function concept.

Why are the functions just _generally_ stored at the executable file and then passed to the `.code` memory area? Well, because it is possible to create functions at execution time, and then they will be store at the heap with a pointer to them being available.

Here is an example:
``` c
void outer() {
	void inner() {
		printf("Hello, I was created in execution time!\n");
	}

	inner();
}
```

Furthermore, we can mix this concept with scopes.

Scope is the area of the code where the application is currently on, if a variable is defined inside a scope, it will not be accessible at the outer scope, but the opposite is not true and, in fact, it's the opposite, a variable defined in an outer scope, when in the inner scope, it will be accessible, and we can use this to create relative references at execution time.

After applying these concepts, it should look like this:
``` c
void outer() {
	int age = 16;
	
	void inner() {
		printf("Hi, I'm %d years old!\n", age);
	}

	inner();
}

outer();  // Hi, I'm 16 years old!
```

## Advanced system development

Fixing these errors, we can finally work on the class system, with attributes and static and non-static methods.

First, we don't want to manually set all the methods every time we instantiate an object, so we need a `constructor`. And to do this, we need to:
- First: change the `outer` function return type to a pointer of the struct desired, like a `Thing` pointer.
- Second: create a variable that is a struct pointer called `new` with `malloc` or `calloc` and return it at the end of the function.
- Third: change the name `outer` to `new<class name>` (e.g.: `newThing`).
- Fourth: change the name `inner` to `<method name>` (e.g.: `showThing`).
- Fifth: set the `new` function pointer attribute(s) as the inner function(s).

The `outer` function will become the object constructor, and the inner function(s) will be the the method(s).

Here is an example with the `Thing` structure:
>`thing.h`
``` c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*showThing)();
} Thing;

Thing * newThing();
```

>`thing.c`
``` c
#include "thing.h"

Thing * newThing() {
    Thing *new = (Thing*) malloc(sizeof(Thing));

    void showThing() {
        printf("Something!\n");
    }
    
    new->showThing = showThing;

    return new;
}
```

>`main.c`
``` c 
#include "thing.h"

int main() {
    Thing *thing = newThing();
    thing->showThing();  // Output: Something!
    free(thing);  // Don't forget to free the pointers!
}
```

### Adding a `destructor` function

To improve even more, we can add a `destructor` to our class, like this:

>`thing.h`
``` c
[...]

void deleteThing(Thing *thing);
```

>`thing.c`
``` c
[...]

void deleteThing(Thing *thing) {
    free(thing);
}
```

>`main.c`
``` c
#include "thing.h"

int main() {
    Thing *thing = newThing();
    thing->showThing();  // Output: Something!
    deleteThing(thing);  // New way to delete the object!
}
```

In this example the `destructor` is very simple, but in bigger classes, with pointers or other classes as attributes, it's essential to have a `destructor`.

### Improving the performance

In our previous case, the constructor function created all the method code every time an object was created, and this can lead to a high memory usage.

To fix it, we can create a "private" function before the constructor, and then, inside the constructor, create a wrapper to this function, like this:

>`thing.h`
``` c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int someAttribute;
    void (*showThing)();
} Thing;

Thing * newThing();
```

>`thing.c`
``` c
#include "thing.h"

void _showThing(Thing * thing) {
	printf("Something %d!\n", thing->someAttribute);
}

Thing * newThing() {
    Thing *new = (Thing*) malloc(sizeof(Thing));

    void showThing() {
        _showThing(new);
    }
    
    new->showThing = showThing;

    return new;
}
```

This way, we can let the big code be created just once, and change the reference as the objects are created, with just one line.

### Creating an access modifier system

>_To be tested_

TBA

## License

This project is currently under a [MIT License](LICENSE)

<br />
