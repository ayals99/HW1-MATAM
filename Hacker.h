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
typedef enum {HACKER_ERROR_ALLOC_FAILED, HACKER_ERROR_BAD_PARA, HACKER_ERROR_SUCCESS} HackerError;

/** Functions */

char* getHackerId(Hacker currHacker);

Hacker hackerCreate(char* hackerId, int numberOfCourses, int* desiredCourses, Friends* friendsArray, Foes* foesArray);

void hackerDestroy(Hacker toDestroy);

/** Getter Functions */

int getCoursesCount(Hacker currHacker);

int* getCourseArray(Hacker currHacker);

Friends* getFriendsArray(Hacker currHacker);

Foes* getFoesArray(Hacker currHacker);

/** Setter Functions */

HackerError setCoursesCount(Hacker currHacker, int courseCount);

HackerError setCourseArray(Hacker currHacker, int* courseArray);

HackerError setFriendsArray(Hacker currHacker, Friends* friendsArray);

HackerError setFoesArray(Hacker currHacker, Foes* foesArray);

#endif
