#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

#include "IsraeliQueue.h"
#include "Node.h"
#include "Person.h"
#include "Hacker.h"
#include "HackEnrollment.h"


/** Defines */

#define FRIENDS 20
#define FOES (-20)
#define NEUTRAL 0
#define THE_VALUE_OF_CHAR_ZERO '0'
#define PUSHING_FORWARD 10
#define IDENTICAL 1

/** Struct declaration */
typedef Node** HackerArray;
typedef Course* courseStructPointerArray;

struct enrollmentSystem_t{
    courseStructPointerArray m_courses;
    int m_numberOfCourses;
    HackerArray m_hackerPointerArray;
    int m_numberOfHackers;
    Person* m_students;
    int m_numberOfStudents;
};

/** Function Signatures */
Node* createListOfStudents(FILE* students);
Node* readHackerFile(FILE* hackers, Node* studentList);
EnrollmentSystemError configureHackers(FILE* hackers, Node* studentList);
int countHackers(FILE* hackers);
HackerArray createHackerList(Node* studentList, int hackerCount);

//bool enrolledInTwoChoices(Person currentPerson, Hacker currentHackerStruct, Course* courseArray, int numberOfHackers,
//                          int totalNumberOfCourses);
void terminate(EnrollmentSystem system, char* studentID, FILE* out);
bool requestedOnlyOneCourse (Hacker hacker);
bool enrolledInCourse(Person currentPerson, Course currentCourse);
Course findCourseByNumber(int courseNumber, int totalNumberOfCourses, Course *courseArrayPointer);
void writeCourseQueueToFile(Course* CourseArray, int totalNumberOfCourses, FILE* out);
char* intToString(int number);
Hacker getHackerPointerFromList(HackerArray listOfHackers, int index);

/** Friendship functions */

int comparisonFunction(void* student1, void* student2){
        //TODO: write comparison function
}

int byHackerFile(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person student1_AUX = (Person) student1;
    Person student2_AUX = (Person) student2;
    bool isStudent1Hacker = isPersonHacker(student1_AUX);
    Hacker student1_Hacker = NULL;
    Hacker student2_Hacker = NULL;
    if (isStudent1Hacker){
        student1_Hacker = personGetHacker(student1_AUX);
    }
    bool isStudent2Hacker = isPersonHacker(student2_AUX);
    if (isStudent2Hacker){
        student2_Hacker = personGetHacker(student2_AUX);
    }
    if (isStudent1Hacker)
    {
        Friends *tmp = getFriendsArray(student1_AUX); //This function is supposed to receive a Hacker but is given a person.
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student2_AUX)) == 0)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(student1_AUX);
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student2_AUX)) == 0)
            {
                return FOES;
            }
            tmp++;
        }
    }
    if (isStudent2Hacker)
    {
        char **tmp = getFriendsArray(student2_AUX);
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student1_AUX)) == 0)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(student2_AUX);
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student1_AUX)) == 0)
            {
                return FOES;
            }
            tmp++;
        }
    }
    return NEUTRAL;
}

int byNameDelta(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person student1_AUX = (Person) student1;
    Person student2_AUX = (Person) student2;
    unsigned int studentsFullNameLength = strlen(personGetName(student1_AUX)) +
            strlen(personGetSurName(student1_AUX));
    char* student1name = malloc(sizeof(char) * (studentsFullNameLength + 1));
    if(student1name == NULL)
    {
        abort() ;
    }
    strcpy(student1name, personGetName(student1_AUX));
    strcat(student1name, personGetSurName(student1_AUX));
    studentsFullNameLength = strlen(personGetName(student2_AUX)) + strlen(
            personGetSurName(student2_AUX));
    char* student2name = malloc(sizeof(char) * (studentsFullNameLength + 1));
    if(student2name == NULL)
    {
        abort() ;
    }
    strcpy(student2name, personGetName(student2_AUX));
    strcat(student2name, personGetSurName(student2_AUX));
    unsigned int student1name_len = strlen(student1name);
    unsigned int student2name_len = strlen(student2name);
    int delta = 0;
    int i = 0;
    for (i = 0; i < student1name_len && i < student2name_len; ++i)
    {
        delta += abs(student1name[i] - student2name[i]);
    }
    while (i < student1name_len) {
        delta += abs(student1name[i] - '\0');
        i++;
    }

    while (i < student2name_len) {
        delta += abs(student2name[i] - '\0');
        i++;
    }
    free(student1name);
    free(student2name);
    return delta;
}

int byIdDelta(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person student1_AUX = (Person) student1;
    Person student2_AUX = (Person) student2;
    char* student1ID = personGetID(student1_AUX);
    char* student2ID = personGetID(student2_AUX);
    int firstNumericalID = 0;
    for(int i = 0; i < strlen(student1ID); i++)
    {
        firstNumericalID = firstNumericalID * PUSHING_FORWARD + (student1ID[i] - THE_VALUE_OF_CHAR_ZERO);
    }
    int secondNumericalID = 0;
    for(int i = 0; i < strlen(student1ID); i++)
    {
        secondNumericalID = secondNumericalID * PUSHING_FORWARD + (student2ID[i] - THE_VALUE_OF_CHAR_ZERO);
    }
    return abs(firstNumericalID - secondNumericalID);
}

/** Functions Implementation */

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{
    
}

/**
 * hackEnrollment: writes to Out new course queue where the hackers are inserted .
 * to two courses that they wished for, or one if they wished for one.
 * In case that one of the hackers didnt get what He/She wished for then the
 * output is an error message.
 *
 * gets: an Enrollment system and Out FILE*.
 */
// loops through all hackers and tries to enqueue them into the queue.
void hackEnrollment(EnrollmentSystem system, FILE* out){
    int totalNumberOfCourses = system->m_numberOfCourses;
    int numberOfHackers = system->m_numberOfHackers;
    Course* courseArray = system->m_courses;
    HackerArray listOfHackers = system->m_hackerPointerArray;

    // loop through all hackers and enroll them in the courses they requested
    for (int hackerIndex = 0; hackerIndex < numberOfHackers; hackerIndex++){
        int enrollmentCounter = 0;
        Hacker currentHackerStruct = getHackerPointerFromList(listOfHackers, hackerIndex);
        Person currentPerson = nodeGetItem(listOfHackers[hackerIndex]);
        char* studentID = personGetID(currentPerson);
        int numberOfDesiredCourses = getCoursesCount(currentHackerStruct);
        int* desiredCoursesArray = getCourseArray(currentHackerStruct);

        // loop through this Hacker's courses and assign him in the course. at the end we'll check that he got at least
        // two courses overall (unless he asked for only one course and didn't get it):
        for(int i = 0; i < numberOfDesiredCourses; i++){
            int currentCourseNumber = desiredCoursesArray[i];
            Course currentCourse = findCourseByNumber(currentCourseNumber,  totalNumberOfCourses, courseArray);
            IsraeliQueue currentQueue = getCourseQueue(currentCourse);
            IsraeliQueueEnqueue(currentQueue, currentHackerStruct);
            bool gotTheCourse = enrolledInCourse(currentPerson, currentCourse);
            if(requestedOnlyOneCourse(currentHackerStruct) && !gotTheCourse){
                terminate(system, studentID, out);
                return;
            }
            if(gotTheCourse){
                enrollmentCounter++;
            }
        }
        // Check if hacker got two of his choices:
        if(enrollmentCounter < 2){
            terminate(system, studentID, out);
        }
    }
    writeCourseQueueToFile(courseArray, totalNumberOfCourses, out);
}

/**
 * enrollmentDestroy: Deallocates all memory allocated by createEnrollment
 * for the object pointed to by the parameter.
 *
 * gets: an Enrollment system.
 */
void enrollmentDestroy(EnrollmentSystem system){
    DestoryCoursesArray(system->m_courses, system->m_numberOfCourses);
    system->m_numberOfCourses = 0;
    Person current = *(system->m_students);
    Person next = NULL;
    Person* allStudentsArray =system->m_students;
    int numberOfStudents = system->m_numberOfStudents;
    for(int i = 0; i < numberOfStudents; i++){
        freePerson(allStudentsArray[i]);
    }
    free(system->m_students);
    freeAndDestroyHackerArray(system->m_hackerPointerArray, count, buffer, desiredCourses, friendsArray, foesArray);
    free(system);
}

Hacker getHackerPointerFromList(HackerArray listOfHackers, int index){
    Node* pointerToHackerNode = listOfHackers[index];
    Person originalHacker = nodeGetItem(pointerToHackerNode);
    Person currentHacker = copyPerson(originalHacker);
    return personGetHacker(currentHacker);
}

int countDigits(int number){
    int counter = 0;
    while(number > 0){
        counter++;
        number /= 10;
    }
    return counter;
}

// TODO: implement this function "intToString"
/**
 * intToString() takes an integer and turns it into a string
 * uses malloc, so needs to be freed later by user of function
 */
char* intToString(int number){
    int digitAmount = 0;
    int tempNumber = number;
    digitAmount = countDigits(number);
    char* string = malloc(sizeof(*string)*digitAmount);
    int index = 0;

    while (digitAmount > 0){
        int currentDigit =  tempNumber / (int)pow(10,digitAmount - 1);
        string[index] = (char)(currentDigit + '0');
        tempNumber /= 10;
        digitAmount--;
    }
    return string;
}

void writeCourseQueueToFile(Course* CourseArray, int totalNumberOfCourses, FILE* out){
    // loops through all courses:
    for(int courseIndex = 0; courseIndex < totalNumberOfCourses; courseIndex++){
        Course currentCourse = CourseArray[courseIndex];
        IsraeliQueue queue = getCourseQueue(currentCourse);
        Person head;
        int courseNumber = getCourseNumber(currentCourse);

        char* courseNumberStr = intToString(courseNumber);
        fputs(courseNumberStr, out);
        free (courseNumberStr);
        fputs(" ", out);
        int courseCapacity = getCourseSize(currentCourse);
        // prints to "out.txt" only the first students in line, until we reach courseCapacity
        for(int i = 0; i < courseCapacity; i++){
            head = IsraeliQueueDequeue(queue);
            fputs(personGetID(head), out);
            if(i != courseCapacity - 1){
                fputs(" ",out);
            }
        }
        fputs("\n", out);
    }
    fputs("\n",out); // TODO: check if FILE* out needs to end with a '\0'
}

bool requestedOnlyOneCourse (Hacker hacker){
    if (getCoursesCount(hacker) <= 1){
        return true;
    }
    else{
        return false;
    }
}

void terminate(EnrollmentSystem system, char* studentID, FILE* out){
    char string[] = "Cannot satisfy constraints for ";
    // write "Cannot satisfy constraints for <Student ID>" into file
    fputs(string, out);
    fputs(studentID, out);
    enrollmentDestroy(system);
}

bool enrolledInCourse(Person currentPerson, Course currentCourse){
    IsraeliQueue list = getCourseQueue(currentCourse);
    IsraeliQueue clonedList = IsraeliQueueClone(list);
    Person currentPersonInList = (Person) IsraeliQueueDequeue(clonedList);
    int courseSize = getCourseSize(currentCourse);
    // TODO: make sure that this loop needs to be until "courseSize - 1" and not "courseSize"
    for(int i = 0; i < (courseSize - 1) && currentPerson != NULL; i++){
        if(comparisonFunction(currentPerson, currentPersonInList) == IDENTICAL){
            return true;
        }
        currentPersonInList = (Person) IsraeliQueueDequeue(clonedList);
    }
    IsraeliQueueDestroy(clonedList);
    return false;
}

Course findCourseByNumber(int courseNumber, int totalNumberOfCourses, Course *courseArrayPointer) {
    for(int i = 0; i< totalNumberOfCourses; i++){
        Course current = courseArrayPointer[i];
        if(courseNumber == getCourseNumber(current)){
            return current;
        }
    }
    return NULL;
}