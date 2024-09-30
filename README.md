# Classes in C

> "Most good programmers do programming not because they expect to get paid or get adulation by the public, but because it is fun to program." -Linus Torvalds

This project is about constructing classes in C with my low experience with this type of thing.

In the proccess of learning how, I will pass through what a pointer is, what a struct is and, of course, what a class is.

Don't expect to be good as some of these big projects that a professional with years of experience make, also because it's on the earliest versions. Besides that, I'm trying my best to provide correct and rich informations about this subject.

There is lots of things to improve, polish and finish.

## How is that possible?

A structure is just a fancy pointer, and a class is just a fancy strucuture.

Knowing this, we can first thought of what a class is composed of, and it's about this:
- Attributes
- Methods

Well, attributes are already built-in in the structures, so our problem is just the methods.

But, in fact, what is a method?

A non-static method is a function that is owned by an object of a class, and it's base is defined with the class.

Furthermore, a non-static method is just a block of code, that can be referenced with a pointer and, in fact, it already is used in this way.

When you call a function in any language, what makes the call is just the brackets at the end, but the first part is just another normal variable like any other, but it's type is `function pointer`.

We can define a function pointer in C using the following sintax rule:

`<return type> (*<variable name/function name>)(<parameter types>)`

Example (I'm not sure if this work): 
``` c
#include <stdio.h>  // C Standart Input/Output library

// Original function
int my_add_function(int x, int y)
{
    return x + y;
}

int main() 
{
    // Pointer that points to the same memory space as 'my_add_function'
    int (*add)(int,int) = my_add_function;

    printf("%d\n", add(1, 1)); // Output: 2

    return 0;
}

```

And, knowing this, we can create our structure like this:
``` c
// At `thing.h`

typedef struct {
    void (*showThing)();
} Thing;
```

Then, we add the function at execution time:
``` c
// At `main.c`

#include <stdio.h>
#include "thing.h"

void showThing()
{
    printf("Something!\n");
}

int main()
{
    Thing thing;
    thing.showThing = showThing;
}

```

But here we encouter a huge problem, in a non-static context, every function/method should have a reference to its object.

If we try to do this by passing the pointer as a parameter, this happens:
``` c 
typedef struct {
    void (*showThing)(Thing*);  // Error: `Thing` is not declared
} Thing;
```

We can't say that a `Thing` pointer type variable is passed as parameter, because it wasn't created yet.

To fix this, we can use a `void` pointer to represent an `Any`-like type or a generic `<T>` thing.

But life doesn't go so smooth and, besides being ass ugly, it throws a `-Wincompatible-pointer-types` error if compiled with GCC, because it doesn't recognize `void *` as a generic or some shit like that.

>Note: With most online compilers, this approach will work.

To fix this two issues, it being ugly and error prone, we can use the `scope` in our favor.

`scope` is the area of the code where the application is currently on, if a variable is defined inside a scope, it will not be accessible at the outer scope, but the oposity is not true and, in fact, it's the oposity, a variable defined in an outer scope, when in the inner scope, it will be accessible, and we can use this to create relative references at execution time.

An inner scope can be create with an outer function and an inner function, just like this:
``` c
#include <stdio.h>

void outer()
{
    void inner()
    {
        printf("Hello, scope!\n");
    }

    inner();
}

int main() {
    outer();  // Output: Hello, scope!

    return 0;
}

```

With this, we can finally work on the class.

- First: change the `outer` function return type to a pointer of the struct desired, like a `Thing` pointer

- Second: create a variable that is a struct pointer called `new` with `malloc` or `calloc` and return it at the end

- Third: change the name `outer` to `new<class name>` (e.g.: `newThing`)

- Fourth: change the name `inner` to `<method name>` (e.g.: `showThing`)

- Fifth: set the `new` function pointer attribute(s) as the inner function(s)

The `outer` function will become the object constructor, and the inner function(s) will be the the method(s).

Here is an example with the `Thing` structure:
``` c
// At `thing.h`
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*showThing)();
} Thing;

Thing * newThing();
```

``` c
// At `thing.c`
#include "thing.h"

Thing * newThing()
{
    Thing *new = (Thing*) malloc(sizeof(Thing));

    void showThing()
    {
        printf("Something!\n");
    }

    new->showThing = showThing;

    return new;
}

```

``` c
// At `main.c`
#include "thing.h"

int main()
{
    Thing *thing = newThing();

    thing->showThing();  // Output: Something!

    free(thing);  // Don't forget to free the pointers!
}
```

To improve even more, we can add a `destructor` to our "class":
``` c
// At `thing.h`
[...]

void deleteThing(Thing *thing);
```

``` c
// At `thing.c`
[...]

void deleteThing(Thing *thing)
{
    free(thing);
}
```

``` c
// At `main.c`
#include "thing.h"

int main()
{
    Thing *thing = newThing();

    thing->showThing();  // Output: Something!

    deleteThing(thing);  // New way to delete the object!
}
```

In this example the `destructor` is very simple, but in bigger classes, with pointers or other classes as attributes, it's essential to have a destructor.

## License

This project is currently under a [MIT License](LICENSE)
