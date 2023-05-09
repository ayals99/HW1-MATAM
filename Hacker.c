#include "Hacker.h"

struct hacker_t {
    char* m_hackerId;
    int m_desiredCoursesCount;
    int* m_desiredCoursesArray;
    Friends* m_friends;
    Foes* m_rivals;
};

void freeArrayOfStrings(char** array);

Hacker hackerCreate(char* hackerId, int desiredCourseCount, int* desiredCourses, Friends* friendsArray, Foes* foesArray) {
    Hacker newHacker = (Hacker) malloc(sizeof(*newHacker));
    if (newHacker == NULL) {
        return NULL;
    }
    newHacker->m_hackerId = hackerId;
    newHacker->m_desiredCoursesCount = desiredCourseCount;
    newHacker ->m_desiredCoursesArray = desiredCourses;
    newHacker->m_friends = friendsArray;
    newHacker->m_rivals = foesArray;

    return newHacker;
}

//frees a NULL terminated array of pointers to strings
void freeArrayOfStrings(char** array){
    char* currentString = *(array);
    int i = 1;
    while(currentString != NULL){
        free( currentString);
        currentString = *(array + i);
        i++;
    }
    free(array);
}

void hackerDestroy(Hacker toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    freeArrayOfStrings((char**)toDestroy->m_friends);
    freeArrayOfStrings((char**)toDestroy->m_rivals);
    free(toDestroy->m_desiredCoursesArray);
    free(toDestroy->m_hackerId);
}

/** Getter Functions */

char* getHackerId(Hacker currHacker){
    if(currHacker == NULL){
        return NULL;
    }
    return currHacker->m_hackerId;
}

int getCoursesCount(Hacker currHacker){
    if(currHacker == NULL){
        return NULL_HACKER;
    }
    return currHacker->m_desiredCoursesCount;
}

int* getCourseArray(Hacker currHacker){
    if(currHacker == NULL){
        return NULL;
    }
    return currHacker->m_desiredCoursesArray;
}

Friends* getFriendsArray(Hacker currHacker){
    if(currHacker == NULL){
        return NULL;
    }
    return currHacker->m_friends;
}

Foes* getFoesArray(Hacker currHacker){
    if(currHacker == NULL){
        return NULL;
    }
    return currHacker->m_rivals;
}

/** Setter Functions */

HackerError setCoursesCount(Hacker currHacker, int courseCount){
    if(currHacker == NULL){
        return HACKER_ERROR_BAD_PARA;
    }
    currHacker->m_desiredCoursesCount = courseCount;
    return HACKER_ERROR_SUCCESS;
}

HackerError setCourseArray(Hacker currHacker, int* courseArray){
    if(currHacker == NULL){
        return HACKER_ERROR_BAD_PARA;
    }
    currHacker->m_desiredCoursesArray = courseArray;
    return HACKER_ERROR_SUCCESS;
}

HackerError setFriendsArray(Hacker currHacker, Friends* friendsArray){
    if(currHacker == NULL){
        return HACKER_ERROR_BAD_PARA;
    }
    currHacker->m_friends = friendsArray;
    return HACKER_ERROR_SUCCESS;
}

HackerError setFoesArray(Hacker currHacker, Foes* foesArray){
    if(currHacker == NULL){
        return HACKER_ERROR_BAD_PARA;
    }
    currHacker->m_rivals = foesArray;
    return HACKER_ERROR_SUCCESS;
}