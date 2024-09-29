#include "person.h"

Person * newPerson()
{
	Person *new = (Person*) malloc(sizeof(Person));

	int setData(int age) {
	    new->age = age;
	}

	new->setData = setData;
	return new;
}

int deletePerson(Person *person)
{
	free(person);
	return 0;
}
