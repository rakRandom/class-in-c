#include <stdio.h>
#include "person.h"


int main()
{
	printf("Initializing the program...\n");
	
	Person *person = newPerson();
	person->setData(16);

	printf("I am %d years old!", person->age);

	deletePerson(person);

	return 0;
}
