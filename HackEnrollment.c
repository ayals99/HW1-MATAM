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
#define CARRIAGE_RETURN '\r'
#define IDENTICAL_STRING 0
#define SIZE_OF_ID 9

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
int* parseIntArray(char* buffer, int numberOfElementsInLine);
char** parseStringArray(char* buffer);
char* readAndTrimLine(FILE* file, char* buffer, int bufferLength);
HackerArray makeHackerArray(FILE* hackers,int numberOfHackers);
void freeAndDestroyHackerArray(HackerArray hackerArray,
                               int count,
                               char* buffer,
                               int* desiredCourses,
                               Friends* friendsArray,
                               Foes* foesArray);
Hacker createHackerFromFile(FILE* hackers, char* buffer, int bufferSize);
char* copyBufferContents(char* buffer);
bool checkAndFreeIfNull(char* hackerId, int* desiredCourses, Friends* friendsArray, Foes* foesArray);
HackerArray createHackersArray(FILE* hackers, EnrollmentSystem sys);
Person* createStudentsArray(FILE* students, EnrollmentSystem sys);
courseStructPointerArray createCoursesArray(FILE* courses, EnrollmentSystem sys);
Person* configureStudentsWithHackers(EnrollmentSystem sys);
bool findAndAssignHackerToStudent(Person *studentsArray, int numberOfStudents, Hacker hacker);
EnrollmentSystemError makeCourseQueue(EnrollmentSystem sys, char* buffer);
EnrollmentSystemError enrollStudents(Person* allStudentsList,int numberOfStudents, Course currentCourse, char* studentsIdList);
EnrollmentSystemError insertStudentToCourseQueue(Course course,Person studentToInsert);





bool enrolledInTwoChoices(Person currentPerson,
                          Hacker currentHackerStruct,
                          Course* courseArray,
                          int numberOfHackers,
                          int totalNumberOfCourses);
void terminate(char* studentID, FILE* out);
bool requestedOnlyOneCourse (Hacker hacker);

/** Comparison functions */

int comparisonFunction(void* student1, void* student2)
{
    if (student1 == student2)
    {
        return 1;
    }
    return 0;
}

/** Friendship functions */

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
        Friends *tmp = getFriendsArray(personGetHacker(student1_AUX)); //This function is supposed to receive a Hacker but is given a person.
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student2_AUX)) == IDENTICAL_STRING)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(personGetHacker(student1_AUX));
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
        char **tmp = getFriendsArray(personGetHacker(student2_AUX));
        while (tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student1_AUX)) == 0)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(personGetHacker(student2_AUX));
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
    Person p1 = (Person) student1;
    Person p2 = (Person) student2;

    char* name1 = personGetName(p1);
    char* name2 = personGetName(p2);
    char* surname1 = personGetSurName(p1);
    char* surname2 = personGetSurName(p2);

    int nameDelta = 0;
    int surnameDelta = 0;

    for (int i = 0; name1[i] != '\0' || name2[i] != '\0'; i++)
    {
        if (name1[i] != '\0' && name2[i] != '\0')
        {
            nameDelta += abs(name1[i] - name2[i]);
        }
        else if (name1[i] != '\0')
        {
            nameDelta += abs(name1[i]);
        }
        else
        {
            nameDelta += abs(name2[i]);
        }
    }

    for (int i = 0; surname1[i] != '\0' || surname2[i] != '\0'; i++)
    {
        if (surname1[i] != '\0' && surname2[i] != '\0')
        {
            surnameDelta += abs(surname1[i] - surname2[i]);
        }
        else if (surname1[i] != '\0')
        {
            surnameDelta += abs(surname1[i]);
        }
        else
        {
            surnameDelta += abs(surname2[i]);
        }
    }
    return nameDelta + surnameDelta;
}

int byIdDelta(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person p1 = (Person) student1;
    Person p2 = (Person) student2;

    int id1 = atoi(personGetID(p1));
    int id2 = atoi(personGetID(p2));

    return abs(id1 - id2);
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
        else if(c != CARRIAGE_RETURN)
        {
              currentLength++;
        }
    }
    fseek(file, 0, SEEK_SET);
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
    fseek(file, 0, SEEK_SET);
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
    ComparisonFunction newComparisonFunction = comparisonFunction;
    const char delimiter[] = {SPACE_BAR};

    for(int i = 0; readAndTrimLine(courses, buffer, longestLineLength + 1 ) != NULL;)
    {
        char* token = strtok(buffer, delimiter);
        //assert(token != NULL);
        int courseNumber = atoi(token);
        token = strtok(NULL, delimiter);
        //assert(token != NULL);
        int courseCapacity = atoi(token);

        Course currentCourse = courseCreate(courseNumber, courseCapacity, newComparisonFunction);
        if(currentCourse == NULL)
        {
            free(coursesArray);
            free(buffer);
            return NULL;
        }
        coursesArray[i] = currentCourse;
        i++;
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
    char* buffer = malloc(sizeof(char) * (longestLineLength + 1));
    if(buffer == NULL)
    {
        free(allStudentsArray);
        return NULL;
    }
    for(int i = 0; readAndTrimLine(students, buffer, longestLineLength + 1) != NULL;)
    {
        char studentID[SIZE_OF_ID];
        int totalCredits;
        double GPA;

        char* name;
        char* surName;
        char* city;
        char* department;

        int result = sscanf(buffer, "%s %d %lf %ms %ms %ms %ms", studentID, &totalCredits, &GPA, &name, &surName, &city, &department);
        if (result != 7) {
            //TODO: Error in parsing the line, you may want to handle it
            continue;
        }

        Person newPerson = personCreate(strdup(studentID), totalCredits, GPA, name, surName, city, department);
        if(newPerson == NULL)
        {
            for (int j = 0; j < i; j++) {
                personDestroy(allStudentsArray[j]);
            }
            free(allStudentsArray);
            free(buffer);
            return NULL;
        }
        allStudentsArray[i] = newPerson;
        i++;
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

int* parseIntArray(char* buffer, int numberOfElementsInLine)
{
    int* array = malloc(sizeof(int) * numberOfElementsInLine);
    if (array == NULL)
    {
        return NULL;
    }
    char *token = strtok(buffer, " ");
    for (int i = 0; i < numberOfElementsInLine && token != NULL; i++)
    {
        array[i] = atoi(token);
        token = strtok(NULL, " ");
    }
    return array;
}

char** parseStringArray(char* buffer)
{
    int numberOfElementsInLine = getNumberOfElementsInLine(buffer);
    char** array = malloc(sizeof(char*) * (numberOfElementsInLine + 1));
    if (array == NULL)
    {
        return NULL;
    }
    char *token = strtok(buffer, " ");
    for (int i = 0; i < numberOfElementsInLine && token != NULL; i++)
    {
        array[i] = strdup(token);
        token = strtok(NULL, " ");
    }
    array[numberOfElementsInLine] = NULL;
    return array;
}

char* readAndTrimLine(FILE* file, char* buffer, int bufferLength)
{
    do
    {
        if (fgets(buffer, bufferLength, file) == NULL)
        {
            return NULL;
        }
        char* newline = strchr(buffer, ROW_DROP);
        if (newline)
        {
            *newline = '\0';
        }
    } while(strlen(buffer) == 0);

    return buffer;
}

char* copyBufferContents(char* buffer)
{
    if (buffer == NULL)
    {
        return NULL;
    }
    size_t bufferSize = strlen(buffer) + 1;
    char* copiedBuffer = (char*)malloc(bufferSize * sizeof(char));
    if (copiedBuffer == NULL)
    {
        return NULL;
    }
    strncpy(copiedBuffer, buffer, bufferSize);
    return copiedBuffer;
}

void freeAndDestroyHackerArray(HackerArray hackerArray, int count, char* buffer, int* desiredCourses, Friends* friendsArray, Foes* foesArray) {
    free(foesArray);
    free(friendsArray);
    free(desiredCourses);

    for (int i = 0; i < count; i++) {
        hackerDestroy(hackerArray[i]);
    }

    free(hackerArray);
    free(buffer);
}

bool checkAndFreeIfNull(char* hackerId, int* desiredCourses, Friends* friendsArray, Foes* foesArray)
{
    bool nullCheck[4] = {hackerId == NULL, desiredCourses == NULL, friendsArray == NULL, foesArray == NULL};
    bool anyNull = false;
    for (int i = 0; i < 4; i++)
    {
        if (nullCheck[i])
        {
            anyNull = true;
            break;
        }
    }
    if (anyNull)
    {
        free(hackerId);
        free(desiredCourses);
        free(friendsArray);
        free(foesArray);
        return false;
    }
    return true;
}

Hacker createHackerFromFile(FILE* hackers, char* buffer, int bufferSize)
{
    char* hackerId = NULL;
    int* desiredCourses = NULL;
    Friends* friendsArray = NULL;
    Foes* foesArray= NULL;

    if (readAndTrimLine(hackers, buffer, bufferSize) != NULL)
    {
        hackerId = copyBufferContents(buffer);
        if(hackerId == NULL)
        {
            return NULL;
        }
    }
    int numberOfCourses;
    if (readAndTrimLine(hackers, buffer, bufferSize) != NULL)
    {
        numberOfCourses = getNumberOfElementsInLine(buffer);
        desiredCourses = parseIntArray(buffer, numberOfCourses);
    }
    if (readAndTrimLine(hackers, buffer, bufferSize) != NULL)
    {
        friendsArray = parseStringArray(buffer);
    }
    if (readAndTrimLine(hackers, buffer, bufferSize) != NULL)
    {
        foesArray = parseStringArray(buffer);
    }
    if (!checkAndFreeIfNull(hackerId, desiredCourses, friendsArray, foesArray))
    {
        return NULL;
    }
    return hackerCreate(hackerId, numberOfCourses, desiredCourses, friendsArray, foesArray);
}

HackerArray makeHackerArray(FILE* hackers,int numberOfHackers)
{
    if (hackers == NULL || numberOfHackers == 0)
    {
        return NULL;
    }
    HackerArray newHackerArray = malloc(sizeof(Hacker) * numberOfHackers);
    if (newHackerArray == NULL)
    {
        return NULL;
    }
    int longestLineLength = getLongestLineLength(hackers);
    char* buffer = malloc(sizeof(char) * (longestLineLength + 1));
    if (buffer == NULL)
    {
        free(newHackerArray);
        return NULL;
    }
    for (int i = 0; i < numberOfHackers; i++)
    {
        Hacker newHacker = createHackerFromFile(hackers, buffer, longestLineLength + 1);
        if (newHacker == NULL)
        {
            freeAndDestroyHackerArray(newHackerArray, i, buffer, NULL, NULL, NULL);
            return NULL;
        }
        newHackerArray[i] = newHacker;
    }
    free(buffer);
    return newHackerArray;
}

courseStructPointerArray createCoursesArray(FILE* courses, EnrollmentSystem sys)
{
    int numberOfCourses = getLinesOfFile(courses);
    if (numberOfCourses == EOF)
    {
        return NULL;
    }
    courseStructPointerArray coursesArray = makeCoursesArray(courses, numberOfCourses);
    if (coursesArray == NULL)
    {
        return NULL;
    }
    sys->m_courses = coursesArray;
    sys->m_numberOfCourses = numberOfCourses;
    return coursesArray;
}

Person* createStudentsArray(FILE* students, EnrollmentSystem sys)
{
    int numberOfStudents = getLinesOfFile(students);
    if (numberOfStudents == EOF)
    {
        return NULL;
    }
    Person *allStudentsArray = makeAllStudentsArray(students, numberOfStudents);
    if (allStudentsArray == NULL)
    {
        return NULL;
    }
    sys->m_students = allStudentsArray;
    sys->m_numberOfStudents = numberOfStudents;
    return allStudentsArray;
}

HackerArray createHackersArray(FILE* hackers, EnrollmentSystem sys)
{
    int numberOfHackers = getLinesOfFile(hackers) / LINES_PER_HACKER;
    if (numberOfHackers == EOF)
    {
        return NULL;
    }
    sys->m_numberOfHackers = numberOfHackers;
    HackerArray newHackerArray = makeHackerArray(hackers, numberOfHackers);
    if (newHackerArray == NULL)
    {
        return NULL;
    }
    sys->m_hackerPointerArray = newHackerArray;
    return newHackerArray;
}

bool findAndAssignHackerToStudent(Person *studentsArray, int numberOfStudents, Hacker hacker)
{
    char *currentHackerId = getHackerId(hacker);
    for (int i = 0; i < numberOfStudents; i++)
    {
        if (strcmp(currentHackerId, personGetID(studentsArray[i])) == IDENTICAL_STRING)
        {
            personSetHacker(studentsArray[i], hacker);
            return true;
        }
    }
    return false;
}


Person* configureStudentsWithHackers(EnrollmentSystem sys)
{
    if(sys == NULL)
    {
        return NULL;
    }
    int numberOfStudents = sys->m_numberOfStudents;
    int numberOfHackers = sys->m_numberOfHackers;
    Person* studentsArray = sys->m_students;
    HackerArray hackerArray = sys->m_hackerPointerArray;
    if (numberOfHackers == 0)
    {
        return studentsArray;
    }
    int successfulAssignments = 0;
    for (int i = 0; i < numberOfHackers; i++)
    {
        if (findAndAssignHackerToStudent(studentsArray, numberOfStudents, hackerArray[i]))
        {
            successfulAssignments++;
        }
    }
    if (successfulAssignments == numberOfHackers)
    {
        return studentsArray;
    }
    else
    {
        return NULL;
    }
}


/**
 * createEnrollment: Creates an Enrollment System struct that includes the
 * students and courses in the files
 *
 * gets: students FILE*, courses FILE* and hackers FILE*
 *
 * @return EnrollmentSystem, or NULL in case of failure
 */
EnrollmentSystem createEnrollment(FILE *students, FILE *courses, FILE *hackers)
{
    if (students == NULL || courses == NULL || hackers == NULL)
    {
        return NULL;
    }
    EnrollmentSystem sys = malloc(sizeof(*sys));
    if (sys == NULL)
    {
        return NULL;
    }
    if (initializeSystem(sys) != ENROLLMENT_SYSTEM_SUCCESS)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    if (createCoursesArray(courses, sys) == NULL)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    if (createStudentsArray(students, sys) == NULL)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    if (createHackersArray(hackers, sys) == NULL)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    if(configureStudentsWithHackers(sys) == NULL)
    {
        enrollmentDestroy(sys);
        return NULL;
    }
    return sys;
}

EnrollmentSystemError insertStudentToCourseQueue(Course course,Person studentToInsert)
{
    if (course == NULL || studentToInsert ==NULL)
    {
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }
    IsraeliQueue courseQueue = getCourseQueue(course);
    IsraeliQueueError enqueueStatus = IsraeliQueueEnqueue(courseQueue, studentToInsert);
    return enqueueStatus == ISRAELIQUEUE_SUCCESS ? ENROLLMENT_SYSTEM_SUCCESS : ENROLLMENT_SYSTEM_ERROR;
}

EnrollmentSystemError enrollStudents(Person* allStudentsList, int numberOfStudents, Course currentCourse, char* studentsIdList)
{
    if (currentCourse == NULL || studentsIdList == NULL)
    {
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }
    char* token = strtok(studentsIdList, " ");
    while(token != NULL)
    {
        for(int i = 0; i < numberOfStudents; i++)
        {
            if (strcmp(token, personGetID(allStudentsList[i])) == IDENTICAL_STRING)
            {
                EnrollmentSystemError insertionStatus = insertStudentToCourseQueue(currentCourse, allStudentsList[i]);
                if(insertionStatus != ENROLLMENT_SYSTEM_SUCCESS)
                {
                    return insertionStatus;
                }
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    return ENROLLMENT_SYSTEM_SUCCESS;
}

EnrollmentSystemError makeCourseQueue(EnrollmentSystem sys, char* buffer)
{
    if (sys == NULL || buffer == NULL)
    {
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }
    char* spacePosition = strchr(buffer, ' ');
    if (spacePosition == NULL)
    {
        return ENROLLMENT_SYSTEM_ERROR;
    }
    int courseNumber = atoi(buffer);
    char* studentsIdString = spacePosition + 1;
    int numberOfStudents = sys->m_numberOfStudents;
    Person* allStudentsList = sys->m_students;
    Course* currentCourse = sys->m_courses;
    int numberOfCourses = sys->m_numberOfCourses;
    for(int i = 0; i < numberOfCourses; i++)
    {
        if(courseNumber == getCourseNumber(currentCourse[i]))
        {
            return enrollStudents(allStudentsList, numberOfStudents, currentCourse[i], studentsIdString);
        }
    }
    return ENROLLMENT_SYSTEM_ERROR;
}

/**
 * readEnrollment: reads a file that describes the courses queues.
 *
 * gets: an Enrollment system and queue FILE*.
 *
 * @return Enrollment system with the courses queues as described in the file.
 * NULL in case of failure.
 */
EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues)
{
    if(sys == NULL || queues == NULL)
    {
        return NULL;
    }

    int longestLineInFile = getLongestLineLength(queues);
    char* buffer = malloc((sizeof(char) * (longestLineInFile + 1)));

    if (buffer == NULL)
    {
        return NULL;
    }

    buffer = readAndTrimLine(queues, buffer, longestLineInFile + 1 );

    while (buffer != NULL)
    {
        EnrollmentSystemError QueueStatus = makeCourseQueue(sys, buffer);
        if(QueueStatus != ENROLLMENT_SYSTEM_SUCCESS)
        {
            free(buffer);
            return NULL;
        }
        buffer = readAndTrimLine(queues, buffer, longestLineInFile + 1 );
    }

    free(buffer);
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
//    Node* pointerToHackerNode = listOfHackers[index];
//    Person originalHacker = nodeGetItem(pointerToHackerNode);
//    Person currentHacker = copyPerson(originalHacker);
//    return personGetHacker(currentHacker);
}

    // TODO: implement this function "intToString"
char* intToString(int courseNumber){

}

void writeCourseQueueToFile(Course* CourseArray, int totalNumberOfCourses, FILE* out){
    // loop through all courses:
//    for(int courseIndex = 0; courseIndex < totalNumberOfCourses; courseIndex++){
//        Course currentCourse = CourseArray[courseIndex];
//        IsraeliQueue queue = getCourseQueue(currentCourse);
//        //Node head = getCourseHead(currentCourse);
//        int courseNumber = getCourseNumber(currentCourse);
//        char* courseNumberStr = intToString(courseNumber);
//        fputs(courseNumberStr, out);
//        free (courseNumberStr);
//        fputs(" ", out);
//
//    }
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
//    IsraeliQueue list = getCourseQueue(currentCourse);
//    Person currentPersonInList = (Person) IsraeliQueueDequeue(list); //TODO: need a function that gets head of list from an IsraeliQueue
//    while(currentPerson != NULL){
//        char* currentID = personGetID(currentPerson);
//        if(comparisonFunction(currentPerson, currentPersonInList) == IDENTICAL){
//            return true;
//        }
//        currentPersonInList = (Person) IsraeliQueueDequeue(list);
//    }
//    return false;
}

Course findCourseByNumber(int courseNumber, int totalNumberOfCourses, Course *courseArrayPointer) {
//    for(int i = 0; i< totalNumberOfCourses; i++){
//        Course current = courseArrayPointer[i];
//        if(courseNumber == getCourseNumber(current)){
//            return current;
//        }
//    }
//    return NULL;
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
//    int totalNumberOfCourses = system->m_numberOfCourses;
//    int numberOfHackers = system->m_numberOfHackers;
//    Course* courseArray = system->m_courses;
//    HackerArray listOfHackers = system->m_hackerPointerArray;
//
//    // loop through all hackers and enroll them in the courses they requested
//    for (int hackerIndex = 0; hackerIndex < numberOfHackers; hackerIndex++){
//        int enrollmentCounter = 0;
//        Hacker currentHackerStruct = getHackerPointerFromList(listOfHackers, hackerIndex);
//        Person currentPerson = nodeGetItem(listOfHackers[hackerIndex]);
//        char* studentID = personGetID(currentPerson);
//        int numberOfDesiredCourses = getCoursesCount(currentHackerStruct);
//        int* desiredCoursesArray = getCourseArray(currentHackerStruct);
//
//        // loop through this Hacker's courses and assign him in the course. at the end we'll check that he got at least
//        // two courses overall (unless he asked for only one course and didn't get it):
//        for(int i = 0; i < numberOfDesiredCourses; i++){
//            int currentCourseNumber = desiredCoursesArray[i];
//            Course currentCourse = findCourseByNumber(currentCourseNumber,  totalNumberOfCourses, courseArray);
//            IsraeliQueue currentQueue = getCourseQueue(currentCourse);
//            IsraeliQueueEnqueue(currentQueue, currentHackerStruct);
//            bool gotTheCourse = enrolledInCourse(currentPerson, currentCourse);
//            if(requestedOnlyOneCourse(currentHackerStruct) && !gotTheCourse){
//                terminate(studentID, out);
//                return;
//            }
//            if(gotTheCourse){
//                enrollmentCounter++;
//            }
//            // TODO: write function that checks if has only one requested course
//            // TODO: write function that checks if the placement of the hacker is after "SIZE" in the queue
//            // TODO: write a function that terminates the void and writes "Cannot satisfy constraints for <Student ID>"
//        }
//        // Check if hacker got two of his choices:
//        if(enrollmentCounter < 2){
//            terminate(studentID, out);
//        }
//    }
//    writeCourseQueueToFile(courseArray, totalNumberOfCourses, out);
}

void enrollmentDestroy(EnrollmentSystem system)
{

}
