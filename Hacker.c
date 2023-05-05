#include "Hacker.h"

struct hacker_t {
    char* m_hackerId;
    int m_desiredCoursesCount;
    int* m_desiredCoursesArray;
    Friends* m_friends;
    Foes* m_rivals;
};

Hacker hackerCreate(char* hackerId, int desiredCourseCount, int* desiredCourses, Friends* friendsArray, Foes* foesArray)
{
    Hacker newHacker = (Hacker)malloc(sizeof(*newHacker));
    if (newHacker == NULL) {
        return NULL;
    }
    newHacker->m_hackerId = hackerId;
    newHacker->m_desiredCoursesCount = desiredCourseCount;
    newHacker->m_desiredCoursesArray = desiredCourses;
    newHacker->m_friends = friendsArray;
    newHacker->m_rivals = foesArray;
    return newHacker;
}


void hackerDestroy(Hacker toDestroy)
{

}

char* getHackerId(Hacker currHacker)
{
    if(currHacker == NULL)
    {
        return NULL;
    }
    return currHacker->m_hackerId;
}

int getCoursesCount(Hacker currHacker)
{

}

int* getCourseArray(Hacker currHacker)
{

}

Friends* getFriendsArray(Hacker currHacker)
{

}

Foes* getFoesArray(Hacker currHacker)
{

}

/** Setter Functions */

HackerError setCoursesCount(Hacker currHacker, int courseCount)
{

}

HackerError setCourseArray(Hacker currHacker, int* courseArray)
{

}

HackerError setFriendsArray(Hacker currHacker, Friends* friendsArray)
{

}

HackerError setFoesArray(Hacker currHacker, Foes* foesArray)
{

}
