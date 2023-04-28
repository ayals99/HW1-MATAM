#ifndef PERSON_H
#define PERSON_H

#include "IsraeliQueue.h"
#include "Node.h"

/** Type for defining the Person */
typedef struct Person_t Person;

/**
 * personCreate: Creates a Person struct pointer with the following fields:
 * student ID
 * Total Credits
 * GPA
 * Name
 * Surname
 * City
 * Department
 *
 * return - a ptr to the new person Or NULL in case of failure;
 */
Person* personCreate();

/**
 * freePerson: frees the person sent to the function.
 * gets a person ptr
 */
void freePerson(Person* toDestroy);

/**
 * copyPerson: makes a new copy of a Person;
 * gets the Person wished to be copied
 *
 * return - NULL in case of allocation failure or
 * a ptr to the copy if successful
 */
Person* copyPerson(Person* toBeCopied);

/** Getter Functions */

//personGetID: returns a ptr to a str that holds the ID of the given person
int* personGetID(Person* currPerson);

//personGetTotalCredits: returns the Total Credits of given person
int personGetTotalCredits(Person* currPerson);

//personGetGPA: returns the GPA of a given person
int personGetGPA(Person* currPerson);

//personGetName: returns a ptr to a str that holds the first name of a given person
char* personGetName(Person* currPerson);

//personGetSurName: returns a ptr to a str that holds the last name of a given person
char* personGetSurName(Person* currPerson);

//personGetCity: returns a ptr to a str that holds the city of a given person
char* personGetCity(Person* currPerson);

//personGetDepartment: returns a ptr to a str that holds the department of a given person
char* personGetDepartment(Person* currPerson);

/** Setter Functions */

//personSetID: Sets the selected persons ID with the ID provided
//returns SUCCESS or FAILURE according to the enum FAILURE chart.
IsraeliQueueError personSetID(Person* currPerson, int* idString);

//personSetTotalCredits: Sets the selected persons Total credits with the Total
// credits provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
IsraeliQueueError personSetTotalCredits(Person* currPerson, int creditsToSet);

//personSetGPA: Sets the selected persons GPA with the GPA
//provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
IsraeliQueueError personSetGPA(Person* currPerson, int toSetGPA);

//personSetName: Sets the selected persons Name with the string
//provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
IsraeliQueueError personSetName(Person* currPerson, char* nameToSet);

//personSetSurName: Sets the selected persons Surname with the string
//provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
IsraeliQueueError personGetSurName(Person* currPerson, char* surNameToSet);

//personSetCity: Sets the selected persons City with the string
//provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
IsraeliQueueError personSetCity(Person* currPerson, char* cityToSet);

//personSetDepartment: Sets the selected persons Department with the string
//provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
IsraeliQueueError personSetDepartment(Person* currPerson, char* depToSet);

#endif
