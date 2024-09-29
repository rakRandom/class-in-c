#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int age;
	int (*setData)(int);
} Person;

int(*__setData(Person *self))(int)
{
	int new(int age) {
	    self->age = age;
	}
	
	return new;
}

Person * newPerson()
{
	Person *new = (Person*) malloc(sizeof(Person));
	new->setData = __setData(new);
	return new;
}

int deletePerson(Person *person)
{
	free(person);
	return 0;
}


int main()
{
	printf("Initializing the program...\n");
	
	Person *person = newPerson();
	person->setData(16);

	printf("I am %d years old!", person->age);

	deletePerson(person);

	return 0;
}
