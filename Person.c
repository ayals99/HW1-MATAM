#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Node.h"
#include "Person.h"

/** DEFINES */

#define MAX_GPA 100
#define MIN_GPA 0
#define MIN_TOTAl_CREDITS 0

/** Struct Declaration */

struct Person_t{
    char ID[10];
    int TotalCredits;
    int GPA;
    char* Name;
    char* SurName;
    char* City;
    char* Department;
};

/** Function Implementation */

Person* personCreate()
{
    Person *newPerson = malloc(sizeof(*newPerson));
    if(newPerson == NULL)
    {
        return NULL;
    }
    return newPerson;
}

void freePerson(Person* toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    freePersonFields(toDestroy);
    free(toDestroy);
}

void freePersonFields(Person* toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    free(toDestroy->ID);
    free(toDestroy->Name);
    free(toDestroy->SurName);
    free(toDestroy->City);
    free(toDestroy->Department);
}

Person* copyPerson(Person* toBeCopied)
{
    if(toBeCopied == NULL)
    {
        return NULL;
    }
    Person* newPerson = personCreate();
    if(copyPersonFields(toBeCopied, newPerson) == ISRAELIQUEUE_SUCCESS) // Maybe we should use new success enums?
    {
        return newPerson;
    }
    return NULL;
}

IsraeliQueueError copyPersonFields(Person* src , Person* dest)
{
    if(src == NULL || dest == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    strcpy(dest->ID, src->ID);
    dest->TotalCredits = src->TotalCredits;
    dest->GPA = src->GPA;
    int len = strlen(src->Name);
    dest->Name = malloc(sizeof(char) * (len + 1));
    if(dest->Name == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    strcpy(dest->Name, src->Name);
    len = strlen(src->SurName);
    dest->SurName = malloc(sizeof(char) * (len + 1));
    if(dest->SurName == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    strcpy(dest->SurName, src->SurName);
    len = strlen(src->City);
    dest->City = malloc(sizeof(char) * (len + 1));
    if(dest->City == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    strcpy(dest->City, src->City);
    len = strlen(src->Department);
    dest->City = malloc(sizeof(char) * (len + 1));
    if(dest->City == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    strcpy(dest->Department, src->Department);
    return ISRAELIQUEUE_SUCCESS;
}

/** Getter Functions Implementation */

char* personGetID(Person* currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->ID;
}

int personGetTotalCredits(Person* currPerson)
{
    if(currPerson == NULL)
    {
        //Needs to check return values for this function.
        return -1;
    }
    return currPerson->TotalCredits;
}

int personGetGPA(Person* currPerson)
{
    if(currPerson == NULL)
    {
        //Needs to check return values for this function.
        return -1;
    }
    return currPerson->GPA;
}

char* personGetName(Person* currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->Name;
}

char* personGetSurName(Person* currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->Name;
}

char* personGetCity(Person* currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->City;
}

char* personGetDepartment(Person* currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->Department;
}

/** Setter Functions Implementation */

IsraeliQueueError personSetID(Person* currPerson, char* idString)
{
    assert(!currPerson && !idString);
    strcpy(currPerson->ID, idString);
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError personSetTotalCredits(Person* currPerson, int creditsToSet)
{
    assert(!currPerson && creditsToSet >= MIN_TOTAl_CREDITS);
    currPerson->TotalCredits = creditsToSet;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError personSetGPA(Person* currPerson, int toSetGPA)
{
    assert(!currPerson && (toSetGPA >= MIN_GPA && toSetGPA <= MAX_GPA));
    currPerson->GPA = toSetGPA;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError personSetName(Person* currPerson, char* nameToSet)
{
    assert(!currPerson && !nameToSet);
    strcpy(currPerson->Name, nameToSet);
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError personSetSurName(Person* currPerson, char* surNameToSet)
{
    assert(!currPerson && !surNameToSet);
    strcpy(currPerson->SurName, surNameToSet);
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError personSetCity(Person* currPerson, char* cityToSet)
{
    assert(!currPerson && !cityToSet);
    strcpy(currPerson->City, cityToSet);
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError personSetDepartment(Person* currPerson, char* depToSet)
{
    assert(!currPerson && !depToSet);
    strcpy(currPerson->Department, depToSet);
    return ISRAELIQUEUE_SUCCESS;
}





