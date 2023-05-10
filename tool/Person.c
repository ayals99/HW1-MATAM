#include <stdlib.h>
// #include <string.h>
#include <assert.h>

#include "../tool/Person.h"

/** DEFINES */

// #define MAX_GPA 100
// #define MIN_GPA 0
// #define MIN_TOTAl_CREDITS 0

// TODO: "ID_MAX_LENGTH" Never used:
// #define ID_MAX_LENGTH 10
/** Struct Declaration */

struct Person_t{
    char* m_ID;
    int m_TotalCredits;
    double m_GPA;
    char* m_Name;
    char* m_SurName;
    char* m_City;
    char* m_Department;
    Hacker m_Hacker;
};

/** functions declarations: */

/**
 * freePersonFields: Frees all the fields under a given struct.
 * gets a person ptr
 */
void freePersonFields(Person toDestroy);

/** Functions Implementations */

Person personCreate(char* studentID,
                    int totalCredits,
                    double GPA,
                    char* name,
                    char* surName,
                    char* city,
                    char* department)
{
    Person newPerson = (Person)malloc(sizeof(*newPerson));
    if(newPerson == NULL)
    {
        return NULL;
    }
    newPerson->m_ID = studentID;
    newPerson->m_GPA = GPA;
    newPerson->m_TotalCredits = totalCredits;
    newPerson->m_Name = name;
    newPerson->m_SurName = surName;
    newPerson->m_City = city;
    newPerson->m_Department = department;
    newPerson->m_Hacker = NULL;
    return newPerson;
}

void personDestroy(Person toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    freePersonFields(toDestroy);
    free(toDestroy);
}

void freePersonFields(Person toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    free(toDestroy->m_ID);
    toDestroy->m_ID = NULL;

    free(toDestroy->m_Name);
    toDestroy->m_Name = NULL;

    free(toDestroy->m_SurName);
    toDestroy->m_SurName = NULL;

    free(toDestroy->m_City);
    toDestroy->m_City = NULL;

    free(toDestroy->m_Department);
    toDestroy->m_Department = NULL;

    hackerDestroy(toDestroy->m_Hacker);
    toDestroy->m_Hacker = NULL;
}

// TODO: Never used
//Person copyPerson(Person toBeCopied)
//{
//    if(toBeCopied == NULL)
//    {
//        return NULL;
//    }
//    // What do you think, will this work? that way we have queues of pointers to structs and don't need to actually copy the structs themselves?
//    Person newPerson = toBeCopied; // Person is a pointer to a struct person_t
//    if(newPerson == NULL){
//        return NULL;
//    }

//            toBeCopied; // TODO: this function needs to get parameters
//    if(copyPersonFields(toBeCopied, newPerson) == PERSON_ERROR_SUCCESS) // Maybe we should use new success enums?
//    {
//        return newPerson;
//    }
//
//    return newPerson;
//}

// TODO: "copyPersonFields" Never used
//PersonError copyPersonFields(Person src , Person dest)
//{
//    if(src == NULL || dest == NULL)
//    {
//        return PERSON_ERROR_BAD_PARAM;
//    }
//    strcpy(dest->m_ID, src->m_ID);
//    dest->m_TotalCredits = src->m_TotalCredits;
//    dest->m_GPA = src->m_GPA;
//    int len = strlen(src->m_Name);
//    dest->m_Name = malloc(sizeof(char) * (len + 1));
//    if(dest->m_Name == NULL)
//    {
//        return PERSON_ERROR_ALLOC_FAILED;
//    }
//    strcpy(dest->m_Name, src->m_Name);
//    len = strlen(src->m_SurName);
//    dest->m_SurName = malloc(sizeof(char) * (len + 1));
//    if(dest->m_SurName == NULL)
//    {
//        return PERSON_ERROR_ALLOC_FAILED;
//    }
//    strcpy(dest->m_SurName, src->m_SurName);
//    len = strlen(src->m_City);
//    dest->m_City = malloc(sizeof(char) * (len + 1));
//    if(dest->m_City == NULL)
//    {
//        return PERSON_ERROR_ALLOC_FAILED;
//    }
//    strcpy(dest->m_City, src->m_City);
//    len = strlen(src->m_Department);
//    dest->m_City = malloc(sizeof(char) * (len + 1));
//    if(dest->m_City == NULL)
//    {
//        return PERSON_ERROR_ALLOC_FAILED;
//    }
//    strcpy(dest->m_Department, src->m_Department);
//    return PERSON_ERROR_SUCCESS;
//}

/** Getter Functions Implementation */

char* personGetID(Person currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->m_ID;
}

// TODO: "personGetTotalCredits" Never used
//int personGetTotalCredits(Person currPerson)
//{
//    if(currPerson == NULL)
//    {
//        //Needs to check return values for this function.
//        return -1;
//    }
//    return currPerson->m_TotalCredits;
//}

// TODO: "personGetGPA" Never used
//int personGetGPA(Person currPerson)
//{
//    if(currPerson == NULL)
//    {
//        //Needs to check return values for this function.
//        return -1;
//    }
//    return currPerson->m_GPA;
//}

char* personGetName(Person currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->m_Name;
}

char* personGetSurName(Person currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->m_SurName;
}

// TODO: "personGetCity" Never used
//char* personGetCity(Person currPerson)
//{
//    if(currPerson == NULL)
//    {
//        return NULL;
//    }
//    return currPerson->m_City;
//}

// TODO: "personGetDepartment" Never used
//char* personGetDepartment(Person currPerson)
//{
//    if(currPerson == NULL)
//    {
//        return NULL;
//    }
//    return currPerson->m_Department;
//}

bool isPersonHacker(Person student)
{
    assert(student != NULL);
    if(student->m_Hacker != NULL)
    {
        return true;
    }
    return false;
}

Hacker personGetHacker(Person currPerson)
{
    assert(currPerson != NULL);
    return currPerson->m_Hacker;
}



/** Setter Functions Implementation */

// TODO: "personSetID" Never used
//PersonError personSetID(Person currPerson, char* idString)
//{
//    assert(!currPerson && !idString);
//    strcpy(currPerson->m_ID, idString);
//    return PERSON_ERROR_SUCCESS;
//}

// TODO: "personSetTotalCredits" Never used
//PersonError personSetTotalCredits(Person currPerson, int creditsToSet)
//{
//    assert(!currPerson && creditsToSet >= MIN_TOTAl_CREDITS);
//    currPerson->m_TotalCredits = creditsToSet;
//    return PERSON_ERROR_SUCCESS;
//}

// TODO: "personSetGPA" Never used
//PersonError personSetGPA(Person currPerson, int toSetGPA)
//{
//    assert(!currPerson && (toSetGPA >= MIN_GPA && toSetGPA <= MAX_GPA));
//    currPerson->m_GPA = toSetGPA;
//    return PERSON_ERROR_SUCCESS;
//}

// TODO: "personSetName" Never used
//PersonError personSetName(Person currPerson, char* nameToSet)
//{
//    assert(!currPerson && !nameToSet);
//    strcpy(currPerson->m_Name, nameToSet);
//    return PERSON_ERROR_SUCCESS;
//}

// TODO: "personSetSurName" Never used
//PersonError personSetSurName(Person currPerson, char* surNameToSet)
//{
//    assert(!currPerson && !surNameToSet);
//    strcpy(currPerson->m_SurName, surNameToSet);
//    return PERSON_ERROR_SUCCESS;
//}

// TODO: "personSetCity" Never used
//PersonError personSetCity(Person currPerson, char* cityToSet)
//{
//    assert(!currPerson && !cityToSet);
//    strcpy(currPerson->m_City, cityToSet);
//    return PERSON_ERROR_SUCCESS;
//}

// TODO: "personSetDepartment" Never used
//PersonError personSetDepartment(Person currPerson, char* depToSet)
//{
//    assert(!currPerson && !depToSet);
//    strcpy(currPerson->m_Department, depToSet);
//    return PERSON_ERROR_SUCCESS;
//}

void personSetHacker(Person currPerson, Hacker hackerToSet)
{
    assert(currPerson != NULL && hackerToSet != NULL);
    currPerson->m_Hacker = hackerToSet;
}