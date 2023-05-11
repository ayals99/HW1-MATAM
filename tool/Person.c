#include <stdlib.h>
#include <assert.h>

#include "../tool/Person.h"


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

/** Getter Functions Implementation */

char* personGetID(Person currPerson)
{
    if(currPerson == NULL)
    {
        return NULL;
    }
    return currPerson->m_ID;
}

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

void personSetHacker(Person currPerson, Hacker hackerToSet)
{
    assert(currPerson != NULL && hackerToSet != NULL);
    currPerson->m_Hacker = hackerToSet;
}