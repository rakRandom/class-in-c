#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *
 */
typedef struct {
    // Attributes
    char *name;
	int age;

    // Getters and Setters
    void (*setName)(char*); 
    char* (*getName)(); 
    
    void (*setAge)(int); 
    int (*getAge)(); 
	
    // Other Methods
    void (*sayHello)(); 
} Person;


/*
 * 
 */
Person * newPerson();


/*
 *
 */
int deletePerson(Person *person);


#endif  // PERSON_H
