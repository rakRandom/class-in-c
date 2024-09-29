#include <stdio.h>
#include "person.h"


int main()
{
	printf("Initializing the program...\n");
	
	// Constructing the Person
	Person *person = newPerson();

	// Setting his attributes
	person->setName("rakRandom");
	person->setAge(16);

	// Calling his methods
	person->sayHello();

	// Always remember to delete the person
	deletePerson(person);

	return 0;
}
