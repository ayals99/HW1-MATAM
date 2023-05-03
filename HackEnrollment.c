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
#define INVALID_FILE (-1)
#define INVALID_STR (-1)
#define ROW_DROP '\n'
#define SPACE_BAR ' '
#define LINES_PER_HACKER 4

/** Struct declaration */
typedef Hacker* HackerArray;
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
int getLongestLineLength(FILE* file);
EnrollmentSystemError initializeSystem(EnrollmentSystem sys);
courseStructPointerArray makeCoursesArray(FILE* courses, int numberOfCourses);
int getLinesOfFile(FILE* file);
Person* makeAllStudentsArray(FILE* students,int numberOfStudents);
int getNumberOfElementsInLine(char* string);



bool enrolledInTwoChoices(Person currentPerson,
                          Hacker currentHackerStruct,
                          Course* courseArray,
                          int numberOfHackers,
                          int totalNumberOfCourses);
void terminate(char* studentID, FILE* out);
bool requestedOnlyOneCourse (Hacker hacker);

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

int getLongestLineLength(FILE* file)
{
    if (file == NULL)
    {
        return INVALID_FILE;
    }
    int maxLength = 0;
    int currentLength = 0;
    int c;
    while((c = fgetc(file)) != EOF)
    {
        if(c == ROW_DROP)
        {
            if (currentLength > maxLength)
            {
                maxLength = currentLength;
            }
            currentLength = 0;
        }
        else
        {
              currentLength++;
        }
    }
    return maxLength;
}

int getLinesOfFile(FILE* file)
{
    if (file == NULL)
    {
        return INVALID_FILE;
    }
    int count = 0;
    int c;
    while((c = fgetc(file)) != EOF)
    {
        if(c == ROW_DROP)
        {
            count++;
        }
    }
    if(c != ROW_DROP && count > 0)
    {
        count++;
    }
    return count;
}

EnrollmentSystemError initializeSystem(EnrollmentSystem sys)
{
    if(sys == NULL)
    {
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }
    sys->m_courses = NULL;
    sys->m_hackerPointerArray = NULL;
    sys->m_students = NULL;
    sys->m_numberOfCourses = 0;
    sys->m_numberOfHackers = 0;
    return ENROLLMENT_SYSTEM_SUCCESS;
}

courseStructPointerArray makeCoursesArray(FILE* courses, int numberOfCourses)
{
    courseStructPointerArray coursesArray = (courseStructPointerArray) malloc(
            sizeof(Course) * numberOfCourses);
    if(coursesArray == NULL)
    {
        return NULL;
    }
    int longestLineLength = getLongestLineLength(courses);
    char* buffer = malloc(sizeof(char) * (longestLineLength + 1));
    if(buffer == NULL)
    {
        free(coursesArray);
        return NULL;
    }
    const char delimiter[] = {SPACE_BAR};
    for(int i = 0; fgets(buffer, longestLineLength, courses) != NULL; i++)
    {
        char* token = strtok(buffer, delimiter);
        assert(token != NULL);
        int courseNumber = atoi(token);
        token = strtok(NULL, delimiter);
        assert(token != NULL);
        int courseCapacity = atoi(token);

        Course currentCourse = courseCreate(courseNumber, courseCapacity);
        if(currentCourse == NULL)
        {
            free(coursesArray);
            free(buffer);
            return NULL;
        }
        coursesArray[i] = currentCourse;
    }
    free(buffer);
    return coursesArray;
}

Person* makeAllStudentsArray(FILE* students,int numberOfStudents)
{
    if(students == NULL || numberOfStudents == 0)
    {
        return NULL;
    }
    Person* allStudentsArray = malloc(sizeof(allStudentsArray) * (numberOfStudents + 1));
    if(allStudentsArray == NULL)
    {
        return NULL;
    }
    int longestLineLength = getLongestLineLength(students);
    char* buffer = malloc(sizeof(char) * longestLineLength);
    if(buffer == NULL)
    {
        free(allStudentsArray);
        return NULL;
    }
    const char delimiter[] = {SPACE_BAR};
    for(int i = 0; fgets(buffer, longestLineLength, students) != NULL; i++)
    {
        char* token = strtok(buffer, delimiter);
        assert(token != NULL);
        char* id = strdup(token);
        token = strtok(NULL, delimiter);
        assert(token != NULL);
        int totalCredits = atoi(token);
        token = strtok(NULL, delimiter);
        assert(token != NULL);
        int gpa = atoi(token);
        token = strtok(NULL, delimiter);
        assert(token != NULL);
        char* name = strdup(token);
        token = strtok(NULL, delimiter);
        assert(token != NULL);
        char* surname = strdup(token);
        token = strtok(NULL, delimiter);
        assert(token != NULL);
        char* city = strdup(token);
        token = strtok(NULL, delimiter);
        assert(token != NULL);
        char* department = strdup(token);

        Person newPerson = personCreate(id, totalCredits, gpa, name, surname, department, NULL);
        if(newPerson == NULL)
        {
            free(allStudentsArray);
            free(buffer);
            return NULL;
        }
        allStudentsArray[i] = newPerson;
    }
    free(buffer);
    return allStudentsArray;
}

int getNumberOfElementsInLine(char* string)
{
    if (string == NULL)
    {
        return INVALID_STR;
    }
    int count = 0;
    while((*string != ROW_DROP ))
    {
        if(*string == SPACE_BAR)
        {
            count++;
        }
        string++;
    }
    return count + 1;
}

HackerArray makeHackerArray(FILE* hackers,int numberOfHackers)
{
    if(hackers == NULL || numberOfHackers == 0)
    {
        return NULL;
    }
    HackerArray newHackerArray = malloc(sizeof(Hacker) * numberOfHackers);
    if(newHackerArray == NULL)
    {
        return NULL;
    }
    int longestLineLength = getLongestLineLength(hackers);
    char* buffer = malloc(sizeof(char) * longestLineLength + 1);
    if(buffer == NULL)
    {
        free(newHackerArray);
        return NULL;
    }
    const char delimiter[] = {SPACE_BAR};
    for(int i = 0; i < numberOfHackers; i++)
    {
        fgets(buffer, longestLineLength, hackers);
        char* token = strtok(buffer, delimiter);
        char* hackerId = strdup(token);
        fgets(buffer, longestLineLength, hackers);
        int numberOfElementsInLine = getNumberOfElementsInLine(buffer);
        int* desiredCourses = malloc(sizeof(int) * numberOfElementsInLine);
        if(desiredCourses == NULL)
        {
            free(newHackerArray);
            free(buffer);
            return NULL;
        }
        int *tmp = desiredCourses;
        token = strtok(buffer, delimiter);
        while(token != NULL)
        {
            *tmp = atoi(token);
            token = strtok(NULL, delimiter);
            tmp++;
        }
        fgets(buffer, longestLineLength, hackers);
        numberOfElementsInLine = getNumberOfElementsInLine(buffer);
        Friends* friendsArray = malloc(sizeof(Friends) * (numberOfElementsInLine + 2));
        if(friendsArray == NULL)
        {
            free(desiredCourses);
            free(newHackerArray);
            free(buffer);
            return NULL;
        }
        Friends* tmpFriendsArray = friendsArray;
        token = strtok(buffer, delimiter);
        while(token != NULL)
        {
            *tmpFriendsArray = strdup(token);
            token = strtok(NULL, delimiter);
            tmpFriendsArray++;
        }
        *tmpFriendsArray = NULL;
        fgets(buffer, longestLineLength, hackers);
        numberOfElementsInLine = getNumberOfElementsInLine(buffer);
        Foes* foesArray = malloc(sizeof(Foes) * (numberOfElementsInLine + 2));
        if(foesArray == NULL)
        {
            free(friendsArray);
            free(desiredCourses);
            free(newHackerArray);
            free(buffer);
            return NULL;
        }
        Foes* tmpFoesArray = foesArray;
        token = strtok(buffer, delimiter);
        while(token != NULL)
        {
            *tmpFoesArray = strdup(token);
            token = strtok(NULL, delimiter);
            tmpFoesArray++;
        }
        *tmpFoesArray = NULL;
        Hacker newHacker = hackerCreate(hackerId, desiredCourses, friendsArray, foesArray);
        if(newHacker == NULL)
        {
            free(foesArray);
            free(friendsArray);
            free(desiredCourses);
            free(newHackerArray);
            free(buffer);
            return NULL;
        }
        newHackerArray[i] = newHacker;
    }
    return newHackerArray;
}


/**
 * createEnrollment: Creates an Enrollment System struct that includes the
 * students and courses in the files
 *
 * gets: students FILE*, courses FILE* and hackers FILE*
 *
 * @return EnrollmentSystem, or NULL in case of failure
 */
EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{
    if(students == NULL || courses == NULL || hackers == NULL)
    {
        return NULL;
    }
    EnrollmentSystem sys = malloc(sizeof(*sys));
    if(sys == NULL)
    {
        return NULL;
    }
    if(initializeSystem(sys) != ENROLLMENT_SYSTEM_SUCCESS)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    //Making and assimilating the courses array in the
    //system struct and the  number of courses
    int numberOfCourses = getLinesOfFile(courses);
    if(numberOfCourses == EOF)
    {
        return NULL;
    }
    courseStructPointerArray coursesArray = makeCoursesArray(courses, numberOfCourses);
    if(coursesArray == NULL)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    sys->m_courses = coursesArray;
    sys->m_numberOfCourses = numberOfCourses;
    //Making and assimilating the students array
    int numberOfStudents = getLinesOfFile(students);
    if(numberOfStudents == EOF)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    Person* allStudentsArray = makeAllStudentsArray(students, numberOfStudents);
    if(allStudentsArray == NULL)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    sys->m_students = allStudentsArray;
    sys->m_numberOfStudents= numberOfStudents;
    //Making and assimilating the hackers array
    // and updating the hackers in the students array.
    int numberOfHackers = getLinesOfFile(hackers) / LINES_PER_HACKER;
    if(numberOfHackers == EOF)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    sys->m_numberOfHackers = numberOfHackers;
    HackerArray newHackerArray = makeHackerArray(hackers, numberOfHackers);
    if(newHackerArray == NULL)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    sys->m_hackerPointerArray = newHackerArray;
    return sys;
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

Hacker getHackerPointerFromList(HackerArray listOfHackers, int index){
    Node* pointerToHackerNode = listOfHackers[index];
    Person originalHacker = nodeGetItem(pointerToHackerNode);
    Person currentHacker = copyPerson(originalHacker);
    return personGetHacker(currentHacker);
}

    // TODO: implement this function "intToString"
char* intToString(int courseNumber){

}

void writeCourseQueueToFile(Course* CourseArray, int totalNumberOfCourses, FILE* out){
    // loop through all courses:
    for(int courseIndex = 0; courseIndex < totalNumberOfCourses; courseIndex++){
        Course currentCourse = CourseArray[courseIndex];
        IsraeliQueue queue = getCourseQueue(currentCourse);
        //Node head = getCourseHead(currentCourse);
        int courseNumber = getCourseNumber(currentCourse);
        char* courseNumberStr = intToString(courseNumber);
        fputs(courseNumberStr, out);
        free (courseNumberStr);
        fputs(" ", out);

    }
}

bool requestedOnlyOneCourse (Hacker hacker){
    if (getCoursesCount(hacker) <= 1){
        return true;
    }
    else{
        return false;
    }
}

void terminate(char* studentID, FILE* out){
    char string[] = "Cannot satisfy constraints for ";
    // write "Cannot satisfy constraints for <Student ID>" into file
    fputs(string, out);
    fputs(studentID, out);

    // TODO: free all memory that was used
}

bool enrolledInCourse(Person currentPerson, Course currentCourse){
    IsraeliQueue list = getCourseQueue(currentCourse);
    Person currentPersonInList = (Person) IsraeliQueueDequeue(list); //TODO: need a function that gets head of list from an IsraeliQueue
    while(currentPerson != NULL){
        char* currentID = personGetID(currentPerson);
        if(comparisonFunction(currentPerson, currentPersonInList) == IDENTICAL){
            return true;
        }
        currentPersonInList = (Person) IsraeliQueueDequeue(list);
    }
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

bool enrolledInTwoChoices(Person currentPerson, Hacker currentHackerStruct, Course* courseArray, int numberOfHackers,
                          int totalNumberOfCourses){
    int enrollmentCounter = 0;
    int* desiredCoursesArray = getCourseArray(currentHackerStruct);
    int numberOfDesiredCourses = getCoursesCount(currentHackerStruct);
    for(int i = 0; i < numberOfDesiredCourses; i++){
        Course currentCourse = findCourseByNumber(desiredCoursesArray[i], totalNumberOfCourses , courseArray);
        if( enrolledInCourse(currentPerson, currentCourse) ){
            enrollmentCounter += 1;
        }
    }
    if(enrollmentCounter >= 2){
        return true;
    }
    else{
        return false;
    }
}

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
                terminate(studentID, out);
                return;
            }
            if(gotTheCourse){
                enrollmentCounter++;
            }
            // TODO: write function that checks if has only one requested course
            // TODO: write function that checks if the placement of the hacker is after "SIZE" in the queue
            // TODO: write a function that terminates the void and writes "Cannot satisfy constraints for <Student ID>"
        }
        // Check if hacker got two of his choices:
        if(enrollmentCounter < 2){
            terminate(studentID, out);
        }
    }
    writeCourseQueueToFile(courseArray, totalNumberOfCourses, out);
}