#ifndef COURSE_H
#define COURSE_H

#include <stdlib.h>
#include <stdio.h>

#include "IsraeliQueue.h"


/** Defines */
#define THRESHOLD_RESET 0
#define COURSE_NULL 0

typedef struct course_t* Course;
//typedef enum {COURSE_ERROR_BAD_PARAM, COURSE_ERROR_ALLOC_FAILED, COURSE_ERROR_SUCCESS} CourseError;

/** Functions */

/**
 * courseCreate: allocates a new struct and initialize accordingly.
 *
 * @param courses - FILE.
 * @return a pointer to a course strut, or NULL in case of failure.
 */

Course courseCreate(int courseNumber, int courseCapacity, ComparisonFunction comparisonFunction);

/**
 * courseDestroy:Destroy a course struct and free all the fields inside,.
 *
 * @param Course* - Course to destroy..
 */
void courseDestroy(Course toDestroy);

/** Getter Functions */

int getCourseNumber(Course course);

int getCourseSize(Course course);

IsraeliQueue getCourseQueue(Course course);

///** Setter Functions */
//
//CourseError setCourseQueue(Course currentCourse, IsraeliQueue queueToSet);
//
//CourseError setCourseNumber(Course currentCourse, int courseNumber);
//
//CourseError setCourseCapacity(Course currentCourse, int courseCapacity);


#endif
