#include "person.h"

Person * newPerson()
{
	Person *new = (Person*) malloc(sizeof(Person));


    // ========== Constructing the methods ==========
    // Getters and Setters
    void setName(char *name) {
        new->name = name;
    }

    char * getName() {
        char * buffer = malloc(1024);
        strcpy_s(buffer, 1024, new->name);
        return buffer;
    }
    
    void setAge(int age) {
        new->age = age;
    }
    
    int getAge() {
        return new->age;        
    }
	
    // Other Methods
    void sayHello() {
        printf("Hello! My name is %s and I'm %d years old!\n", new->name, new->age);
    }


    // ========== Setting the methods ==========
    // Getters and Setters
	new->setName = setName;
    new->getName = getName;
    
    new->setAge = setAge;
    new->getAge = getAge; 
	
    // Other Methods
    new->sayHello = sayHello;


	return new;
}

int deletePerson(Person *person)
{
    free(person->name);
	free(person);
	return 0;
}
