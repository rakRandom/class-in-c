#ifndef PERSON_H
#define PERSON_H

#include <stdlib.h>


/*
 *
 */
typedef struct {
	int age;
	int (*setData)(int);
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
