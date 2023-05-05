#include "Course.h"
#include "IsraeliQueue.h"

struct course_t{
    int m_courseNumber;
    int m_courseCapacity;
    IsraeliQueue m_courseQueue;
};

Course courseCreate(FILE* course){
    // read file
    // create comparison function
    // create functions array
    Course newCourse = malloc(sizeof(*newCourse));
    IsraeliQueue newQueue = IsraeliQueueCreate();
    newCourse->m_courseQueue = newQueue;
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

/** Setter Functions */

CourseError setCourseQueue(Course currentCourse, IsraeliQueue queueToSet){
    currentCourse->m_courseQueue = queueToSet;
}