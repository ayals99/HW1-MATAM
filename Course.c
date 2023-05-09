#include "Course.h"

struct course_t{
    int m_courseNumber;
    int m_courseCapacity;
    IsraeliQueue m_courseQueue;
};

Course courseCreate(int courseNumber, int courseCapacity, ComparisonFunction comparisonFunction)
{
    Course newCourse = malloc(sizeof(*newCourse));
    if(newCourse == NULL)
    {
        return NULL;
    }
    FriendshipFunction* friendshipFunction = malloc(sizeof(FriendshipFunction));
    if(friendshipFunction == NULL)
    {
        courseDestroy(newCourse);
        return NULL;
    }
    *friendshipFunction = NULL;

    IsraeliQueue newQueue = IsraeliQueueCreate(friendshipFunction,
                                               comparisonFunction,
                                               THRESHOLD_RESET,
                                               THRESHOLD_RESET);
    free(friendshipFunction);
    newCourse->m_courseQueue = newQueue;
    newCourse->m_courseNumber = courseNumber;
    newCourse->m_courseCapacity = courseCapacity;

    return newCourse;
}

void courseDestroy(Course toDestroy){
    if(toDestroy == NULL){
        return;
    }
    IsraeliQueueDestroy(toDestroy->m_courseQueue);
    free(toDestroy);
}

/** Getter Functions */

int getCourseNumber(Course course){
    if (course == NULL){
        return COURSE_NULL;
    }
    return course->m_courseNumber;
}

int getCourseSize(Course course){
    if (course == NULL){
        return COURSE_NULL;
    }
    return course->m_courseCapacity;
}

IsraeliQueue getCourseQueue(Course course){
    if (course == NULL){
        return NULL;
    }
    return course->m_courseQueue;
}