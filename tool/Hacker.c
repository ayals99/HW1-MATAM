#include "Hacker.h"

struct hacker_t {
    char* m_hackerId;
    int m_desiredCoursesCount;
    int* m_desiredCoursesArray;
    Friends* m_friends;
    Foes* m_rivals;
};

void freeArrayOfStrings(char** array);

Hacker hackerCreate(char* hackerId, int desiredCourseCount, int* desiredCourses, Friends* friendsArray, Foes* foesArray)
{
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

int countStrings(char** array){
    if(array == NULL){
        return 0;
    }
    char* currentString = *(array);
    int counter = 0;
    while(currentString != NULL){
        currentString = *(array + counter);
        counter++;
    }
    return counter;
}

//frees a NULL terminated array of pointers to strings
void freeArrayOfStrings(char** array){
    if(array == NULL){
        return;
    }
    int numberOfStrings = countStrings(array);
    for(int i = 0; i < numberOfStrings; i++){
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
}

void hackerDestroy(Hacker toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    freeArrayOfStrings(toDestroy->m_friends);
    toDestroy->m_friends = NULL;
    freeArrayOfStrings(toDestroy->m_rivals);
    toDestroy->m_rivals = NULL;
    free(toDestroy->m_desiredCoursesArray);
    toDestroy->m_desiredCoursesArray = NULL;
    free(toDestroy->m_hackerId);
    toDestroy->m_hackerId = NULL;
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

//TODO: never used
//HackerError setCoursesCount(Hacker currHacker, int courseCount){
//    if(currHacker == NULL){
//        return HACKER_ERROR_BAD_PARA;
//    }
//    currHacker->m_desiredCoursesCount = courseCount;
//    return HACKER_ERROR_SUCCESS;
//}

// TODO: never used
//HackerError setCourseArray(Hacker currHacker, int* courseArray){
//    if(currHacker == NULL){
//        return HACKER_ERROR_BAD_PARA;
//    }
//    currHacker->m_desiredCoursesArray = courseArray;
//    return HACKER_ERROR_SUCCESS;
//}

//TODO: never used
//HackerError setFriendsArray(Hacker currHacker, Friends* friendsArray){
//    if(currHacker == NULL){
//        return HACKER_ERROR_BAD_PARA;
//    }
//    currHacker->m_friends = friendsArray;
//    return HACKER_ERROR_SUCCESS;
//}

//TODO: never used
//HackerError setFoesArray(Hacker currHacker, Foes* foesArray){
//    if(currHacker == NULL){
//        return HACKER_ERROR_BAD_PARA;
//    }
//    currHacker->m_rivals = foesArray;
//    return HACKER_ERROR_SUCCESS;
//}