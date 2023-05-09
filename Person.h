#ifndef PERSON_H
#define PERSON_H
#include <stdbool.h>

#include "Node.h"
#include "Hacker.h"

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
 * freePersonFields: Frees all the fields under a given struct.
 * gets a person ptr
 */
void freePersonFields(Person toDestroy);

// TODO: Never used
///**
// * copyPerson: makes a new copy of a Person;
// * gets the Person wished to be copied
// *
// * return - NULL in case of allocation failure or
// * a ptr to the copy if successful
// */
//Person copyPerson(Person toBeCopied);

// TODO: Never used
///**
// * copyPersonFields: copies the fields from src struct to dest.
// *
// * return - returns SUCCESS or FAILURE according to the enum FAILURE chart.
// */
//PersonError copyPersonFields(Person src, Person dest);

/**
 * isPersonHacer: checks if a certain student is a hacker,
 *
 * return - returns true, or false.
 */
bool isPersonHacker(Person student);

/** Getter Functions */

//personGetID: returns a ptr to a str that holds the ID of the given person
char* personGetID(Person currPerson);

// TODO: "personGetTotalCredits" Never used
////personGetTotalCredits: returns the Total Credits of given person
//int personGetTotalCredits(Person currPerson);

// TODO: "personGetGPA" Never used
////personGetGPA: returns the GPA of a given person
//int personGetGPA(Person currPerson);

//personGetName: returns a ptr to a str that holds the first name of a given person
char* personGetName(Person currPerson);

//personGetSurName: returns a ptr to a str that holds the last name of a given person
char* personGetSurName(Person currPerson);

// TODO: "personGetCity" Never used
////personGetCity: returns a ptr to a str that holds the city of a given person
//char* personGetCity(Person currPerson);

// TODO: "personGetDepartment" Never used
////personGetDepartment: returns a ptr to a str that holds the department of a given person
//char* personGetDepartment(Person currPerson);

//personGetHacker: returns a ptr to a Hacker struct held by person.
Hacker personGetHacker(Person currPerson);


/** Setter Functions */

// TODO: Never used

// TODO: "personSetID" Never used
////personSetID: Sets the selected persons ID with the ID provided
////returns SUCCESS or FAILURE according to the enum FAILURE chart.
//PersonError personSetID(Person currPerson, char* idString);

// TODO: "personSetTotalCredits" Never used
////personSetTotalCredits: Sets the selected persons Total credits with the Total
//// credits provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
//PersonError personSetTotalCredits(Person currPerson, int creditsToSet);

// TODO: "personSetGPA" Never used
////personSetGPA: Sets the selected persons GPA with the GPA
////provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
//PersonError personSetGPA(Person currPerson, int toSetGPA);

// TODO: "personSetName" Never used
////personSetName: Sets the selected persons Name with the string
////provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
//PersonError personSetName(Person currPerson, char* nameToSet);

// TODO: "personSetSurName" Never used
////personSetSurName: Sets the selected persons Surname with the string
////provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
//PersonError personSetSurName(Person currPerson, char* surNameToSet);

// TODO: "personSetCity" Never used
////personSetCity: Sets the selected persons City with the string
////provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
//PersonError personSetCity(Person currPerson, char* cityToSet);

// TODO: "personSetDepartment" Never used
////personSetDepartment: Sets the selected persons Department with the string
////provided, returns SUCCESS or FAILURE according to the enum FAILURE chart.
//PersonError personSetDepartment(Person currPerson, char* depToSet);

//personSetHacker: sets a ptr to a Hacker struct held by person.
void personSetHacker(Person currPerson, Hacker hackerToSet);

#endif
