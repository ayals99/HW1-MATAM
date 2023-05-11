#ifndef HACKER_H
#define HACKER_H

/** Included files */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Typedef */

#define NULL_HACKER 0

typedef struct hacker_t* Hacker;
typedef char* Friends;
typedef char* Foes;

/** Functions */


Hacker hackerCreate(char* hackerId,int desiredCourseCount, int* desiredCourses, Friends* friendsArray, Foes* foesArray);

char* getHackerId(Hacker currHacker);

void hackerDestroy(Hacker toDestroy);

/** Getter Functions */

int getCoursesCount(Hacker currHacker);

int* getCourseArray(Hacker currHacker);

Friends* getFriendsArray(Hacker currHacker);

Foes* getFoesArray(Hacker currHacker);

/** Setter Functions */

#endif
