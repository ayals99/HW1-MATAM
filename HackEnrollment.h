#ifndef HACKENROLLMENT_H
#define HACKENROLLMENT_H

/** Included files */

#include "IsraeliQueue.h"
#include "Node.h"
#include "Person.h"
#include "Hacker.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Defines */

#define FRIENDSHIP_THRESHOLD 20
#define RIVALRY_THRESHOLD 0

/** Typedef */

typedef enum {ENROLLMENT_SYSTEM_SUCCESS, ENROLLMENT_SYSTEM_BAD_PARAM, ENROLLMENT_SYSTEM_ALLOC_FAILED} EnrollmentSystemError;
typedef struct enrollmentSystem_t EnrollmentSystem;


/** Friendship functions */

int byHackerFile(void*, void*);
int byNameDelta(void*, void*);
int byIdDelta(void*, void*);


/** Functions */

/**
 * createEnrollment: Creates an Enrollment System struct that includes the students and courses
 * in the files
 *
 * gets: students FILE*, courses FILE* and hackers FILE*
 *
 * @return EnrollmentSystem, or NULL in case of failure
 */
EnrollmentSystem createEnrollment(FILE*, FILE*, FILE*);



/**
 * readEnrollment: reads a file that describes the courses queues.
 *
 * gets: an Enrollment system and queue FILE*.
 *
 * @return Enrollment system with the courses queues as described in the file.
 * NULL in case of failure.
 */
EnrollmentSystem readEnrollment(EnrollmentSystem, FILE*);

/**
 * hackEnrollment: writes to Out new course queue where the hackers are inserted .
 * to two courses that they wished for, or one if they wished for one.
 * In case that one of the hackers didnt get what He/She wished for then the
 * output is an error message.
 *
 * gets: an Enrollment system and Out FILE*.
 */
void hackEnrollment(EnrollmentSystem, FILE*);

/**
 * enrollmentDestroy: Deallocates all memory allocated by createEnrollment
 * for the object pointed to by the parameter.
 *
 * gets: an Enrollment system.
 */
void enrollmentDestroy(EnrollmentSystem);


#endif
