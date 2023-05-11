#ifndef PERSON_H
#define PERSON_H

#include <stdbool.h>

#include "../tool/Node.h"
#include "../tool/Hacker.h"

/** Type for defining the Person */
typedef struct Person_t* Person;

// typedef enum {PERSON_ERROR_SUCCESS} PersonError;

/**
 * personCreate: Creates a Person struct pointer with the following fields:
 * that should be initialized to the following values -
 * student ID = NULL
 * Total Credits = 0
 * GPA
 * Name
 * Surname
 * City
 * Department
 * Hacker
 *
 * return - a ptr to the new person Or NULL in case of failure;
 */
Person personCreate(char* studentID,
                     int totalCredits,
                     double GPA,
                     char* name,
                     char* surName,
                     char* city,
                     char* department);

/**
 * freePerson: frees the person sent to the function.
 * gets a person ptr
 */
void personDestroy(Person toDestroy);

/**
 * isPersonHacer: checks if a certain student is a hacker,
 *
 * return - returns true, or false.
 */
bool isPersonHacker(Person student);

/** Getter Functions */

//personGetID: returns a ptr to a str that holds the ID of the given person
char* personGetID(Person currPerson);

//personGetName: returns a ptr to a str that holds the first name of a given person
char* personGetName(Person currPerson);

//personGetSurName: returns a ptr to a str that holds the last name of a given person
char* personGetSurName(Person currPerson);

//personGetHacker: returns a ptr to a Hacker struct held by person.
Hacker personGetHacker(Person currPerson);


/** Setter Functions */

//personSetHacker: sets a ptr to a Hacker struct held by person.
void personSetHacker(Person currPerson, Hacker hackerToSet);

#endif
