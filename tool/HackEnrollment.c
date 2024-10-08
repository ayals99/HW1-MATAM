#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>


#include "HackEnrollment.h"


/** Defines */

#define FRIENDS 20
#define FOES (-20)
#define NEUTRAL 0
#define IDENTICAL_BY_COMPARISON_FUNCTION 1
#define IDENTICAL_STRINGS 0
#define INVALID_FILE (-1)
#define INVALID_STR (-1)
#define ROW_DROP '\n'
#define SPACE_BAR ' '
#define LINES_PER_HACKER 4
#define CARRIAGE_RETURN '\r'
#define SIZE_OF_ID 9
#define NUMBER_OF_INPUTS_TO_SCAN_F 7
#define STRING_END '\0'
#define EMPTY_STRING 0
#define OFFSET 2
#define DECIMAL 10
#define SPACE_BAR_STRING " "

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
    bool m_isFlagOn;
};

/** Function Signatures */
int getLongestLineLength(FILE* file);
EnrollmentSystemError initializeSystem(EnrollmentSystem sys);
courseStructPointerArray makeCoursesArray(FILE* courses, int numberOfCourses);
int getLinesOfFile(FILE* file);
Person* makeAllStudentsArray(FILE* students,int numberOfStudents);
int getNumberOfElementsInLine(char* string);
int* parseIntArray(char* buffer, int numberOfElementsInLine);
char** parseStringArray(char* buffer, int numberOfElementsInLine);
char* readAndTrimLine(FILE* file, char* buffer, int bufferLength);
HackerArray makeHackerArray(FILE* hackers,int numberOfHackers);
void freeAndDestroyHackerArray(HackerArray hackerArray,
                               int countOfHackers);
Hacker createHackerFromFile(FILE* hackers, char* buffer, int bufferSize);
char* copyBufferContents(char* buffer);
bool checkAndFreeIfNull(char* hackerId, int* desiredCourses, Friends* friendsArray,
                        Foes* foesArray, int numberOfCourses, int numberOfFriends, int numberOfFoes);
HackerArray createHackersArray(FILE* hackers, EnrollmentSystem sys);
Person* createStudentsArray(FILE* students, EnrollmentSystem sys);
courseStructPointerArray createCoursesArray(FILE* courses,
                                            EnrollmentSystem sys);
Person* configureStudentsWithHackers(EnrollmentSystem sys);
bool findAndAssignHackerToStudent(Person *studentsArray,
                                  int numberOfStudents,
                                  Hacker hacker);
EnrollmentSystemError makeCourseQueue(EnrollmentSystem sys, char* buffer);
EnrollmentSystemError enrollStudents(Person* allStudentsList,
                                     int numberOfStudents,
                                     Course currentCourse,
                                     char* studentsIdList, bool isFlagOn);
EnrollmentSystemError insertStudentToCourseQueue(Course course,
                                                 Person studentToInsert);
EnrollmentSystemError addFriendshipFunctionsAndThresholds(IsraeliQueue queue, bool isFlagOn);
void DestroyCoursesArray(Course* array, int numberOfCourses);
Person getPersonByHacker(char* hackerID, Person* students, int numberOfStudents);
void terminate(char* studentID, FILE* out);
bool requestedOnlyOneCourse (Hacker hacker);
bool enrolledInCourse(Person currentPerson, Course currentCourse);
Course findCourseByNumber(int courseNumber, int totalNumberOfCourses, Course *courseArrayPointer);
void writeCourseQueueToFile(Course* CourseArray, int totalNumberOfCourses, FILE* out);
Hacker getHackerPointerFromList(HackerArray listOfHackers, int index, int numberOfHackers);
char* duplicateString(char* string);
int getLongestElementInLine(char* buffer);
EnrollmentSystemError allocateMemoryForFields(char** name, char** surName, char** city, char** department,
                                              int longestElementInLine);
void freeAllocatedMemoryForFields(char* name ,char* surName, char* city, char* department);
void handleErrorAllStudentsArray (char* buffer, Person* allStudentsArray, int index);
void handleErrorCourseArray (char* buffer, courseStructPointerArray coursesArray, int index);
void printQueue(IsraeliQueue queue);

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
    Person student1_AUX = (Person) student1;
    Person student2_AUX = (Person) student2;
    bool isStudentHacker = isPersonHacker(student1_AUX);
    if (isStudentHacker)
    {
        Friends *tmp = getFriendsArray(personGetHacker(student1_AUX));
        while (tmp != NULL && *tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student2_AUX)) == IDENTICAL_STRINGS)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(personGetHacker(student1_AUX));
        while (tmp != NULL && *tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student2_AUX)) == IDENTICAL_STRINGS)
            {
                return FOES;
            }
            tmp++;
        }
    }
    isStudentHacker = isPersonHacker(student2_AUX);
    if (isStudentHacker)
    {
        Friends* tmp = getFriendsArray(personGetHacker(student2_AUX));
        while (tmp != NULL && *tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student1_AUX)) == IDENTICAL_STRINGS)
            {
                return FRIENDS;
            }
            tmp++;
        }
        tmp = getFoesArray(personGetHacker(student2_AUX));
        while (tmp != NULL && *tmp != NULL)
        {
            if (strcmp(*tmp, personGetID(student1_AUX)) == IDENTICAL_STRINGS)
            {
                return FOES;
            }
            tmp++;
        }
    }
    return NEUTRAL;
}

void toLowerCase(char* originalString){
    while(*originalString != STRING_END){
        if (*originalString >= 'A' && *originalString <= 'Z'){
            *(originalString) = (char)(*originalString + 'a' - 'A');
        }
        originalString++;
    }
}

int byNameDeltaWithoutCase(void* student1, void* student2){
    Person p1 = (Person) student1;
    Person p2 = (Person) student2;
    char* name1 = personGetName(p1);
    toLowerCase(name1);
    char* name2 = personGetName(p2);
    toLowerCase(name2);
    char* surname1 = personGetSurName(p1);
    toLowerCase(surname1);
    char* surname2 = personGetSurName(p2);
    toLowerCase(surname2);

    int nameDelta = 0;
    int surnameDelta = 0;

    for (int i = 0; name1[i] != STRING_END || name2[i] != STRING_END; i++)
    {
        if (name1[i] != STRING_END && name2[i] != STRING_END) {
            nameDelta += abs(name1[i] - name2[i]);
        } else {
            for (int j = i; name1[j] != STRING_END; j++) {
                nameDelta += abs(name1[j]);
            }
            for (int j = i; name2[j] != STRING_END; j++) {
                nameDelta += abs(name2[j]);
            }
        }
    }
    for (int i = 0; surname1[i] != STRING_END || surname2[i] != STRING_END; i++)
    {
        if (surname1[i] != STRING_END && surname2[i] != STRING_END)
        {
            surnameDelta += abs(surname1[i] - surname2[i]);
        } else
        {
            for (int j = i; surname1[j] != STRING_END; j++)
            {
                surnameDelta += abs(surname1[j]);
            }
            for (int j = i; surname2[j] != STRING_END; j++)
            {
                surnameDelta += abs(surname2[j]);
            }
        }
    }
    return nameDelta + surnameDelta;
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

    for (int i = 0; name1[i] != STRING_END || name2[i] != STRING_END; i++) {
        if (name1[i] != STRING_END && name2[i] != STRING_END) {
            nameDelta += abs(name1[i] - name2[i]);
        } else {
            for (int j = i; name1[j] != STRING_END; j++) {
                nameDelta += abs(name1[j]);
            }
            for (int j = i; name2[j] != STRING_END; j++) {
                nameDelta += abs(name2[j]);
            }
            break;
        }
    }
    for (int i = 0; surname1[i] != STRING_END || surname2[i] != STRING_END; i++) {
        if (surname1[i] != STRING_END && surname2[i] != STRING_END) {
            surnameDelta += abs(surname1[i] - surname2[i]);
        } else {
            for (int j = i; surname1[j] != STRING_END; j++) {
                surnameDelta += abs(surname1[j]);
            }
            for (int j = i; surname2[j] != STRING_END; j++) {
                surnameDelta += abs(surname2[j]);
            }
            break;
        }
    }
    return nameDelta + surnameDelta;
}

int byIdDelta(void* student1, void* student2)
{
    assert(student1 != NULL && student2 != NULL);
    Person p1 = (Person) student1;
    Person p2 = (Person) student2;

    int id1 = (int)strtol(personGetID(p1), NULL, DECIMAL);
    int id2 = (int)strtol(personGetID(p2), NULL, DECIMAL);

    return abs(id1 - id2);
}

/** Functions Implementation */
Hacker getHackerPointerFromList(HackerArray listOfHackers, int index, int numberOfHackers){
    if(listOfHackers == NULL || index >= numberOfHackers){
        return NULL;
    }
    return listOfHackers[index];
}

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
    int c = fgetc(file);
    while( c != EOF)
    {
        if (c == ROW_DROP)
        {
            count++;
        }
        c = fgetc(file);
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
    sys->m_numberOfStudents = 0;
    return ENROLLMENT_SYSTEM_SUCCESS;
}

void handleErrorCourseArray (char* buffer, courseStructPointerArray coursesArray, int index)
{
    for (int j = 0; j < index; j++)
    {
        courseDestroy(coursesArray[j]);
        coursesArray[j] = NULL;
    }
    free(coursesArray);
    free(buffer);
}

courseStructPointerArray makeCoursesArray(FILE* courses, int numberOfCourses)
{
    courseStructPointerArray coursesArray = (courseStructPointerArray) malloc(sizeof(Course) * numberOfCourses);
    if(coursesArray == NULL)
    {
        return NULL;
    }
    int longestLineLength = getLongestLineLength(courses);
    char* buffer = malloc(sizeof(char) * (longestLineLength + OFFSET));
    if(buffer == NULL)
    {
        free(coursesArray);
        return NULL;
    }
    ComparisonFunction newComparisonFunction = comparisonFunction;
    const char delimiter[] = {SPACE_BAR};
    for(int i = 0; i < numberOfCourses; i++)
    {
        if (readAndTrimLine(courses, buffer, longestLineLength + OFFSET) == NULL)
        {
            handleErrorCourseArray(buffer, coursesArray, i);
            return NULL;
        }
        if (buffer[0] == '\n')
        {
            continue;
        }
        char* token = strtok(buffer, delimiter);
        int courseNumber = (int)strtol(token, NULL, DECIMAL);
        token = strtok(NULL, delimiter);
        int courseCapacity = (int)strtol(token, NULL, DECIMAL);
        Course currentCourse = courseCreate(courseNumber, courseCapacity, newComparisonFunction);
        if(currentCourse == NULL)
        {
            handleErrorCourseArray(buffer, coursesArray, i);
            return NULL;
        }
        coursesArray[i] = currentCourse;
    }
    free(buffer);
    return coursesArray;
}

char* duplicateString(char* string)
{
    if(string == NULL)
    {
        return NULL;
    }
    char* newString = malloc(sizeof(char) * (strlen(string) + 1));
    if(newString == NULL)
    {
        return NULL;
    }
    strcpy(newString, string);
    return newString;
}

int getLongestElementInLine(char* buffer)
{
    int maxCount = 0;
    if(buffer == NULL)
    {
        return -1;
    }
    while(*buffer != '\0')
    {
        int count = 0;
        while (*buffer != SPACE_BAR && *buffer != '\0')
        {
            count++;
            buffer++;
        }
        if (count > maxCount)
        {
            maxCount = count;
        }
        if (*buffer == SPACE_BAR)
        {
            buffer++;
        }
    }
    return maxCount;
}

EnrollmentSystemError allocateMemoryForFields(char** name, char** surName, char** city, char** department,
                                              int longestElementInLine)
{
    if (longestElementInLine < 1)
    {
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }

    *name = (char*) malloc((longestElementInLine + 1) * sizeof(char));
    *surName = (char*) malloc((longestElementInLine + 1) * sizeof(char));
    *city = (char*) malloc((longestElementInLine + 1) * sizeof(char));
    *department = (char*) malloc((longestElementInLine + 1) * sizeof(char));

    if (*name == NULL || *surName == NULL || *city == NULL || *department == NULL)
    {
        free(*name);
        free(*surName);
        free(*city);
        free(*department);
        return ENROLLMENT_SYSTEM_ALLOC_FAIL;
    }
    return ENROLLMENT_SYSTEM_SUCCESS;
}

void freeAllocatedMemoryForFields(char* name ,char* surName, char* city, char* department)
{
    free(name);
    free(surName);
    free(city);
    free(department);
}

void handleErrorAllStudentsArray (char* buffer, Person* allStudentsArray, int index)
{
    for (int j = 0; j < index; j++)
    {
        personDestroy(allStudentsArray[j]);
        allStudentsArray[j] = NULL;
    }
    free(allStudentsArray);
    free(buffer);
}

Person* makeAllStudentsArray(FILE* students,int numberOfStudents)
{
    if(students == NULL || numberOfStudents < 0){
        return NULL;
    }
    Person* allStudentsArray = malloc(sizeof(allStudentsArray) * (numberOfStudents + OFFSET));
    if(allStudentsArray == NULL){
        return NULL;
    }
    int longestLineLength = getLongestLineLength(students);
    char* buffer = malloc(sizeof(char) * (longestLineLength + OFFSET));
    if(buffer == NULL){
        free(allStudentsArray);
        return NULL;
    }
    for(int i = 0; readAndTrimLine(students, buffer, longestLineLength + OFFSET) != NULL; i++){
        int longestElementInLine = getLongestElementInLine(buffer);
        if (!longestElementInLine)
        {
            handleErrorAllStudentsArray(buffer, allStudentsArray, i);
            return NULL;
        }
        char studentID[SIZE_OF_ID];
        int totalCredits;
        double GPA;
        char *name, *surName, *city, *department;
        if (allocateMemoryForFields(&name, &surName, &city, &department,longestElementInLine) !=
            ENROLLMENT_SYSTEM_SUCCESS){
            handleErrorAllStudentsArray(buffer, allStudentsArray, i);
            return NULL;
        }
        int result = sscanf(buffer, "%s %d %lf %s %s %s %s", studentID, &totalCredits, &GPA, name, surName,
                            city, department);
        if (result != NUMBER_OF_INPUTS_TO_SCAN_F){
            freeAllocatedMemoryForFields(name, surName, city, department);
            handleErrorAllStudentsArray(buffer, allStudentsArray, i);
            return NULL;
        }
        char* tempID = duplicateString(studentID);
        Person newPerson = personCreate(tempID, totalCredits, GPA, name, surName, city, department);
        if(newPerson == NULL){
            handleErrorAllStudentsArray(buffer, allStudentsArray, i);
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
    if (*string == ROW_DROP)
    {
        return count;
    }
    while((*string != ROW_DROP && strlen(string) != EMPTY_STRING))
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
    if (!numberOfElementsInLine)
    {
        return NULL;
    }
    int* array = malloc(sizeof(int) * numberOfElementsInLine);
    if (array == NULL)
    {
        return NULL;
    }
    char *token = strtok(buffer, SPACE_BAR_STRING);
    for (int i = 0; i < numberOfElementsInLine && token != NULL; i++)
    {
        array[i] = strtol(token, NULL, DECIMAL);
        token = strtok(NULL, SPACE_BAR_STRING);
    }
    return array;
}

char** parseStringArray(char* buffer, int numberOfElementsInLine)
{
    if (!numberOfElementsInLine)
    {
        return NULL;
    }
    char** array = malloc(sizeof(char*) * (numberOfElementsInLine + 1));
    if (array == NULL)
    {
        return NULL;
    }
    char *token = strtok(buffer, SPACE_BAR_STRING);
    for (int i = 0; i < numberOfElementsInLine && token != NULL; i++)
    {
        array[i] = duplicateString(token);
        token = strtok(NULL, SPACE_BAR_STRING);
    }
    array[numberOfElementsInLine] = NULL;
    return array;
}

char* readAndTrimLine(FILE* file, char* buffer, int bufferLength)
{
    if(buffer == NULL)
    {
        return NULL;
    }
    if (fgets(buffer, bufferLength, file) == NULL)
    {
        return NULL;
    }
    if (strlen(buffer) > 1)
    {
        char* newline = strchr(buffer, ROW_DROP);
        if (newline)
        {
            *newline = '\0';
        }
    }
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

void freeAndDestroyHackerArray(HackerArray hackerArray, int count) {
    if(hackerArray == NULL){
        return;
    }
    for (int i = 0; i < count; i++) {

        hackerDestroy(hackerArray[i]);
    }
    free(hackerArray);
}

bool checkAndFreeIfNull(char* hackerId, int* desiredCourses, Friends* friendsArray, Foes* foesArray,
                        int numberOfCourses, int numberOfFriends, int numberOfFoes)
{
    bool nullCheck[4] = {hackerId == NULL, desiredCourses == NULL && numberOfCourses > 0  ,
                         friendsArray == NULL && numberOfFriends > 0 , foesArray == NULL && numberOfFoes > 0};
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

    if (readAndTrimLine(hackers, buffer, bufferSize + OFFSET) != NULL)
    {
        hackerId = copyBufferContents(buffer);
        if(hackerId == NULL)
        {
            return NULL;
        }
    }
    int numberOfCourses = 0;
    if (readAndTrimLine(hackers, buffer, bufferSize + OFFSET) != NULL)
    {
        numberOfCourses = getNumberOfElementsInLine(buffer);
        desiredCourses = parseIntArray(buffer, numberOfCourses);
    }
    int numberOfFriends = 0;
    if (readAndTrimLine(hackers, buffer, bufferSize + OFFSET) != NULL)
    {
        numberOfFriends = getNumberOfElementsInLine(buffer);
        friendsArray = parseStringArray(buffer,numberOfFriends);
    }
    int numberOfFoes = 0;
    if (readAndTrimLine(hackers, buffer, bufferSize + OFFSET) != NULL)
    {
        numberOfFoes = getNumberOfElementsInLine(buffer);
        foesArray = parseStringArray(buffer, numberOfFoes);
    }
    if (!checkAndFreeIfNull(hackerId, desiredCourses, friendsArray, foesArray,
                            numberOfCourses, numberOfFriends, numberOfFoes))
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
    char* buffer = malloc(sizeof(char) * (longestLineLength + OFFSET));
    if (buffer == NULL)
    {
        free(newHackerArray);
        return NULL;
    }
    for (int i = 0; i < numberOfHackers; i++)
    {
        Hacker newHacker = createHackerFromFile(hackers, buffer, longestLineLength + OFFSET);
        if (newHacker == NULL)
        {
            freeAndDestroyHackerArray(newHackerArray, i);
            free(buffer);
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
        if (strcmp(currentHackerId, personGetID(studentsArray[i])) == IDENTICAL_STRINGS)
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

// From here on is "readEnrollment" functions:
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

EnrollmentSystemError addFriendshipFunctionsAndThresholds(IsraeliQueue queue, bool isFlagOn)
{
    if (queue == NULL)
    {
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }
    FriendshipFunction function = byHackerFile;
    if (IsraeliQueueAddFriendshipMeasure(queue, function) != ISRAELIQUEUE_SUCCESS)
    {
        return ENROLLMENT_SYSTEM_ERROR;
    }
    if (isFlagOn)
    {
        function = byNameDeltaWithoutCase;
    }
    else
    {
        function = byNameDelta;

    }
    if (IsraeliQueueAddFriendshipMeasure(queue, function) != ISRAELIQUEUE_SUCCESS)
    {
        return ENROLLMENT_SYSTEM_ERROR;
    }
    function = byIdDelta;
    if (IsraeliQueueAddFriendshipMeasure(queue, function) != ISRAELIQUEUE_SUCCESS)
    {
        return ENROLLMENT_SYSTEM_ERROR;
    }
    if (IsraeliQueueUpdateFriendshipThreshold(queue, FRIENDSHIP_THRESHOLD) !=ISRAELIQUEUE_SUCCESS)
    {
        return ENROLLMENT_SYSTEM_ERROR;
    }
    if (IsraeliQueueUpdateRivalryThreshold(queue, RIVALRY_THRESHOLD) !=ISRAELIQUEUE_SUCCESS)
    {
        return ENROLLMENT_SYSTEM_ERROR;
    }
    return ENROLLMENT_SYSTEM_SUCCESS;
}


EnrollmentSystemError enrollStudents(Person* allStudentsList, int numberOfStudents,
                                     Course currentCourse, char* studentsIdList, bool isFlagOn)
{
    if (currentCourse == NULL || studentsIdList == NULL)
    {
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }
    char* token = strtok(studentsIdList, SPACE_BAR_STRING);
    while(token != NULL)
    {
        for(int i = 0; i < numberOfStudents; i++)
        {
            if (strcmp(token, personGetID(allStudentsList[i])) == IDENTICAL_STRINGS)
            {
                EnrollmentSystemError insertionStatus = insertStudentToCourseQueue(currentCourse,
                                                                                   allStudentsList[i]);
                if(insertionStatus != ENROLLMENT_SYSTEM_SUCCESS)
                {
                    return insertionStatus;
                }
            }
        }
        token = strtok(NULL, SPACE_BAR_STRING);
    }
    return addFriendshipFunctionsAndThresholds(getCourseQueue(currentCourse), isFlagOn);
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
    int courseNumber = strtol(buffer, NULL, DECIMAL);
    char* studentsIdString = spacePosition + 1;
    int numberOfStudents = sys->m_numberOfStudents;
    Person* allStudentsList = sys->m_students;
    Course* currentCourse = sys->m_courses;
    int numberOfCourses = sys->m_numberOfCourses;
    for(int i = 0; i < numberOfCourses; i++)
    {
        if(courseNumber == getCourseNumber(currentCourse[i]))
        {
            return enrollStudents(allStudentsList, numberOfStudents, currentCourse[i],
                                  studentsIdString, sys->m_isFlagOn);
        }
    }
    return ENROLLMENT_SYSTEM_ERROR;
}

EnrollmentSystemError enrollmentSystemUpdateFlag(EnrollmentSystem system, bool isFlagOn){
    if(system == NULL){
        return ENROLLMENT_SYSTEM_BAD_PARAM;
    }
    system->m_isFlagOn = !isFlagOn;
    return ENROLLMENT_SYSTEM_SUCCESS;
}

/**
 * readEnrollment: reads a file that describes the courses queues.
 *
 * gets: an Enrollment system and queue FILE*.
 *
 * @return Enrollment system with the courses queues as described in the file.
 * NULL in case of failure.
 */
EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues){
    if(sys == NULL || queues == NULL){
        return NULL;
    }
    int longestLineInFile = getLongestLineLength(queues);
    char* buffer = malloc((sizeof(char) * (longestLineInFile + OFFSET)));
    if (buffer == NULL){
        return NULL;
    }

    buffer = readAndTrimLine(queues, buffer, longestLineInFile + OFFSET);

    while (buffer != NULL){
        EnrollmentSystemError QueueStatus = makeCourseQueue(sys, buffer);
        if(QueueStatus != ENROLLMENT_SYSTEM_SUCCESS)
        {
            free(buffer);
            return NULL;
        }
        buffer = readAndTrimLine(queues, buffer, longestLineInFile + OFFSET);
    }
    for(int i = 0; i < sys->m_numberOfCourses; i++)
    {
        IsraeliQueue currentQueue = getCourseQueue(*(sys->m_courses + i));
        int queueSize = IsraeliQueueSize(currentQueue);
        if (!queueSize)
        {
            if(addFriendshipFunctionsAndThresholds(currentQueue, sys->m_isFlagOn) != ENROLLMENT_SYSTEM_SUCCESS)
            {
                free(buffer);
                return NULL;
            }
        }
    }
    free(buffer);
    return sys;
}

// getPersonByHacker: Returns a ptr to a person_t struct thar holds the hacker.
// NOTE: Searches by ID.
Person getPersonByHacker(char* hackerID, Person* students, int numberOfStudents){
    if(students == NULL || hackerID == NULL){
        return NULL;
    }
    for(int i = 0; i < numberOfStudents;i++){
        Person currentPerson = students[i];
        if(strcmp(hackerID, personGetID(currentPerson)) == IDENTICAL_STRINGS){
            return currentPerson;
        }
    }
    return NULL;
}

bool enrolledInTwoChoices(Person currentPerson,Hacker currentHackerStruct,Course* courseArray,int totalNumberOfCourses)
{
    int enrollmentCounter = 0;
    int* desiredCoursesArray = getCourseArray(currentHackerStruct);
    int numberOfDesiredCourses = getCoursesCount(currentHackerStruct);
    for(int i = 0; i < numberOfDesiredCourses; i++){
        Course currentCourse = findCourseByNumber(desiredCoursesArray[i], totalNumberOfCourses , courseArray);
        if( enrolledInCourse(currentPerson, currentCourse) ){
            enrollmentCounter += 1;
        }
    }
    if(enrollmentCounter >= OFFSET){
        return true;
    }
    else{
        return false;
    }
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
    Course* courseArray = system->m_courses;
    int totalNumberOfCourses = system->m_numberOfCourses;
    HackerArray listOfHackers = system->m_hackerPointerArray;
    int numberOfHackers = system->m_numberOfHackers;
    // loop through all hackers and enroll them in the courses they requested
    for (int hackerIndex = 0; hackerIndex < numberOfHackers; hackerIndex++)
    {
        //Don't we have the hacker pointer from the array of hackers?
        //Hacker CurrentHacker = listOfHackers[i];
        Hacker currentHackerStruct = getHackerPointerFromList(listOfHackers, hackerIndex, numberOfHackers);
        Person currentPerson = getPersonByHacker(getHackerId(currentHackerStruct),
                                                 system->m_students, system->m_numberOfStudents);
        char* studentID = personGetID(currentPerson);
        int* desiredCoursesArray = getCourseArray(currentHackerStruct);
        int numberOfDesiredCourses = getCoursesCount(currentHackerStruct);
        // loop through this Hacker's desired courses and assign him in the course.
        // checks for two courses overall (unless he asked for only one course and didn't get it):
        for (int i = 0; i < numberOfDesiredCourses; i++) {
            int currentCourseNumber = desiredCoursesArray[i];
            Course currentCourse = findCourseByNumber(currentCourseNumber, totalNumberOfCourses, courseArray);
            IsraeliQueue currentQueue = getCourseQueue(currentCourse);
            if (ISRAELIQUEUE_SUCCESS != IsraeliQueueEnqueue(currentQueue, currentPerson)) {
                terminate(studentID, out);
                return;
            }
        }
    }
    // Check that all hackers got at least two courses overall (unless they asked for only one course and didn't get it)
    for (int hackerIndex = 0; hackerIndex < numberOfHackers; hackerIndex++){
        Person currentPerson = getPersonByHacker(getHackerId(listOfHackers[hackerIndex]),
                                                 system->m_students, system->m_numberOfStudents);
        Hacker currentHackerStruct = getHackerPointerFromList(listOfHackers, hackerIndex, numberOfHackers);
        if( getCoursesCount(currentHackerStruct) == 0){
            continue;
        }
        Course firstCourseOnList = findCourseByNumber(getCourseArray(currentHackerStruct)[0],
                                                      totalNumberOfCourses,courseArray);
        if((requestedOnlyOneCourse(currentHackerStruct) && !enrolledInCourse(currentPerson, firstCourseOnList) )
                    || (!enrolledInTwoChoices(currentPerson,currentHackerStruct,courseArray,totalNumberOfCourses)
                        && (getCoursesCount(currentHackerStruct) >= 2) ) ) {
            terminate(personGetID(currentPerson), out);
            return;
        }
    }
    writeCourseQueueToFile(courseArray, totalNumberOfCourses, out);
}

void DestroyCoursesArray(Course* array, int numberOfCourses){
    if(array == NULL){
        return;
    }
    for(int i = 0; i < numberOfCourses; i++){
        courseDestroy(array[i]);
    }
}

/**
 * enrollmentDestroy: Deallocates all memory allocated by createEnrollment
 * for the object pointed to by the parameter.
 *
 * gets: an Enrollment system.
 */
void enrollmentDestroy(EnrollmentSystem system){
    if(system == NULL){
        return;
    }
    DestroyCoursesArray(system->m_courses, system->m_numberOfCourses);
    int numberOfStudents = system->m_numberOfStudents;
    Person* allStudentsArray =system->m_students;
    for(int i = 0; i < numberOfStudents; i++){
        personDestroy(allStudentsArray[i]);
        allStudentsArray[i] = NULL;
    }
    free(system->m_hackerPointerArray);
    free(system->m_students);
    free(system);
}


// loops through all courses and writes thw whole queue to "out" file
void writeCourseQueueToFile(Course* CourseArray, int totalNumberOfCourses, FILE* out){
    for(int courseIndex = 0; courseIndex < totalNumberOfCourses; courseIndex++){
        Course currentCourse = CourseArray[courseIndex];
        IsraeliQueue queue = getCourseQueue(currentCourse);
        int courseNumber = getCourseNumber(currentCourse);
        int queueSize = IsraeliQueueSize(queue);
        if(queueSize == 0){
            continue;
        }
        fprintf(out, "%d", courseNumber);
        Person head = IsraeliQueueDequeue(queue);
        while (head != NULL){
            fprintf(out, SPACE_BAR_STRING);
            char* studentID = personGetID(head);
            fprintf(out, "%s", studentID);
            head = IsraeliQueueDequeue(queue);
        }
        fprintf(out, "\n");
    }
}

bool requestedOnlyOneCourse (Hacker hacker){
    if (getCoursesCount(hacker) == 1){
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
    fprintf(out, "\n");
}

bool enrolledInCourse(Person currentPerson, Course currentCourse){
    IsraeliQueue list = getCourseQueue(currentCourse);
    IsraeliQueue clonedList = IsraeliQueueClone(list);
    Person currentPersonInList = (Person) IsraeliQueueDequeue(clonedList);
    int courseSize = getCourseSize(currentCourse);
    for(int i = 0; i < courseSize && currentPersonInList != NULL; i++){
        if(comparisonFunction(currentPerson, currentPersonInList) == IDENTICAL_BY_COMPARISON_FUNCTION){
            IsraeliQueueDestroy(clonedList);
            return true;
        }
        currentPersonInList = (Person) IsraeliQueueDequeue(clonedList);
    }
    IsraeliQueueDestroy(clonedList);
    return false;
}

Course findCourseByNumber(int courseNumber, int totalNumberOfCourses, Course *courseArrayPointer) {
    if(courseArrayPointer == NULL){
        return NULL;
    }
    for(int i = 0; i< totalNumberOfCourses; i++){
        Course current = courseArrayPointer[i];
        if(courseNumber == getCourseNumber(current)){
            return current;
        }
    }
    return NULL;
}
