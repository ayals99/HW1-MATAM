#include "Course.h"
#include "IsraeliQueue.h"

struct course_t{
    int m_courseNumber;
    int m_courseCapacity;
    IsraeliQueue m_courseQueue;
};

Course courseCreate(int courseNumber, int courseCapacity)
{
    // read file
    // create comparison function
    // create functions array
    Course newCourse = malloc(sizeof(*newCourse));
    IsraeliQueue newQueue = NULL;
    newCourse->m_courseQueue = newQueue;
    newCourse->m_courseCapacity = 0;
    newCourse->m_courseNumber= 0;
}