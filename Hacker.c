#include "Hacker.h"

struct hacker_t {
    int m_desiredCoursesCount;
    int* m_desiredCoursesArray;
    Friends* m_friends;
    Foes* m_rivals;
};

Hacker hackerCreate(char* Id, int* desiredCourses, Friends* friendsArray, Foes* foesArray)
{

}


void hackerDestroy(Hacker toDestroy)
{

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
