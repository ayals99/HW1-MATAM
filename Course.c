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