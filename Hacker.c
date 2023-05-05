#include "Hacker.h"

#define END_OF_LINE '\n'
#define END_OF_STRING '0'
#define ID_LENGTH 10
#define INT_LENGTH 10
#define SPACE ' '

struct hacker_t {
    char* m_hackerId;
    int m_desiredCoursesCount;
    int* m_desiredCoursesArray;
    Friends* m_friends;
    Foes* m_rivals;
};

int countDesiredCourses(char* secondLine){
    if(*secondLine == END_OF_LINE){
        return 0;
    }
    int spaceCounter = 0;
    while(*secondLine != END_OF_LINE){
        if(*secondLine == SPACE){
            spaceCounter++;
        }
        secondLine++;
    }
    return spaceCounter + 1;
}

Hacker hackerCreate(char* hackerId, int numberOfCourses, int* desiredCourses, Friends* friendsArray, Foes* foesArray){
    Hacker newHacker = malloc(sizeof(*newHacker));
    if(newHacker == NULL){
        return NULL;
    }
    newHacker->m_hackerId = hackerId;
    newHacker->m_desiredCoursesCount = numberOfCourses;
    newHacker->m_desiredCoursesArray = desiredCourses;
    newHacker->m_friends = friendsArray;
    newHacker->m_rivals = foesArray;
    return newHacker;
}

void hackerDestroy(Hacker toDestroy){

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