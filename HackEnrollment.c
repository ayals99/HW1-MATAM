#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

#include "IsraeliQueue.h"
#include "Node.h"
#include "Person.h"
#include "Hacker.h"
#include "HackEnrollment.h"


/** Defines */

#define FRIENDS 20
#define FOES (-20)
#define NEUTRAL 0
#define THE_VALUE_OF_CHAR_ZERO '0'
#define PUSHING_FORWARD 10

/** Struct declaration */
typedef Node** HackerArray;

struct enrollmentSystem_t{
    IsraeliQueue* queueArray;
    int* courses;
    HackerArray hackerPointerArray;
    int numberOfHackers;
    Person* students;
};

/** Function Signatures */
Node* createListOfStudents(FILE* students);
Node* readHackerFile(FILE* hackers, Node* studentList);
EnrollmentSystemError configureHackers(FILE* hackers, Node* studentList);
int countHackers(FILE* hackers);
HackerArray createHackerList(Node* studentList, int hackerCount);

/** Friendship functions */

int byHackerFile(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person *student1_AUX = (Person*) student1;
    Person *student2_AUX = (Person*) student2;
    bool isStudent1Hacker = isPersonHacker(student1_AUX);
    bool isStudent2Hacker = isPersonHacker(student2_AUX);
    if (isStudent1Hacker)
    {
        Friends *tmp = getFriendsArray(student1_AUX);
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student2_AUX)) == 0)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(student1_AUX);
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student2_AUX)) == 0)
            {
                return FOES;
            }
            tmp++;
        }
    }
    if (isStudent2Hacker)
    {
        char **tmp = getFriendsArray(student2_AUX);
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student1_AUX)) == 0)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(student2_AUX);
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student1_AUX)) == 0)
            {
                return FOES;
            }
            tmp++;
        }
    }
    return NEUTRAL;
}

int byNameDelta(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person *student1_AUX = (Person*) student1;
    Person *student2_AUX = (Person*) student2;
    unsigned int studentsFullNameLength = strlen(personGetName(student1_AUX)) +
            strlen(personGetSurName(student1_AUX));
    char* student1name = malloc(sizeof(char) * (studentsFullNameLength + 1));
    if(student1name == NULL)
    {
        abort() ;
    }
    strcpy(student1name, personGetName(student1_AUX));
    strcat(student1name, personGetSurName(student1_AUX));
    studentsFullNameLength = strlen(personGetName(student2_AUX)) + strlen(
            personGetSurName(student2_AUX));
    char* student2name = malloc(sizeof(char) * (studentsFullNameLength + 1));
    if(student2name == NULL)
    {
        abort() ;
    }
    strcpy(student2name, personGetName(student2_AUX));
    strcat(student2name, personGetSurName(student2_AUX));
    unsigned int student1name_len = strlen(student1name);
    unsigned int student2name_len = strlen(student2name);
    int delta = 0;
    int i = 0;
    for (i = 0; i < student1name_len && i < student2name_len; ++i)
    {
        delta += abs(student1name[i] - student2name[i]);
    }
    while (i < student1name_len) {
        delta += abs(student1name[i] - '\0');
        i++;
    }

    while (i < student2name_len) {
        delta += abs(student2name[i] - '\0');
        i++;
    }
    free(student1name);
    free(student2name);
    return delta;
}

int byIdDelta(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person *student1_AUX = (Person*) student1;
    Person *student2_AUX = (Person*) student2;
    char* student1ID = personGetID(student1_AUX);
    char* student2ID = personGetID(student2_AUX);
    int firstNumericalID = 0;
    for(int i = 0; i < strlen(student1ID); i++)
    {
        firstNumericalID = firstNumericalID * PUSHING_FORWARD + (student1ID[i] - THE_VALUE_OF_CHAR_ZERO);
    }
    int secondNumericalID = 0;
    for(int i = 0; i < strlen(student1ID); i++)
    {
        secondNumericalID = secondNumericalID * PUSHING_FORWARD + (student2ID[i] - THE_VALUE_OF_CHAR_ZERO);
    }
    return abs(firstNumericalID - secondNumericalID);
}

/** Functions Implementation */

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{
    
}


/**
 * hackEnrollment: writes to Out new course queue where the hackers are inserted .
 * to two courses that they wished for, or one if they wished for one.
 * In case that one of the hackers didnt get what He/She wished for then the
 * output is an error message.
 *
 * gets: an Enrollment system and Out FILE*.
 */
 // loops through all hackers and tries to enqueue them into the qeueue.
 //
void hackEnrollment(EnrollmentSystem, FILE*){

}


