#include <stdio.h>
//#include <assert.h>

/** Internal Includes */

#include "HackEnrollment.h"

/** Defines */

#define IDENTICAL_STRINGS 0
#define ON 0
#define OFF 1
#define ARGUMENTS_WITH_FLAG 7
#define ARGUMENTS_WITHOUT_FLAG 6
#define FIRST_FILE 2
#define SECOND_FILE 3
#define THIRD_FILE 4
#define FOURTH_FILE 5
#define FIFTH_FILE 6

/** Functions Signatures */
void closeFiles(FILE* , FILE* , FILE* , FILE* , FILE* );
int checkForFlag(int , char** );
int freeProgram(EnrollmentSystem ,FILE* ,FILE* , FILE* , FILE* , FILE*);

/** Helper functions */

void closeFiles(FILE* students, FILE* courses, FILE* hackers, FILE* queues, FILE* target){
    fclose(students);
    fclose(courses);
    fclose(hackers);
    fclose(queues);
    fclose(target);
}

int checkForFlag(int numberOfInputs, char** argv)
{
    for (int i = 1; i < numberOfInputs; i++)
    {
        if (strcmp(argv[i], "-i") == IDENTICAL_STRINGS)
        {
            return ON;
        }
    }
    return OFF;
}

int freeProgram(EnrollmentSystem system ,FILE* students,FILE* courses, FILE* hackers, FILE* queues, FILE* target)
{
    enrollmentDestroy(system);
    closeFiles(students, courses, hackers, queues, target);
    return 0;
}




int main(int argc, char** argv)
{
    int IsFlagOn = OFF;
    if(argc == ARGUMENTS_WITH_FLAG)
    {
        IsFlagOn = checkForFlag(argc, argv);
    }
    else if (argc != ARGUMENTS_WITHOUT_FLAG)
    {
        return 0;
    }

    FILE* students = fopen(argv[FIRST_FILE - IsFlagOn], "r");
    FILE* courses = fopen(argv[SECOND_FILE - IsFlagOn], "r");
    FILE* hackers = fopen(argv[THIRD_FILE - IsFlagOn], "r");
    FILE* queues = fopen(argv[FOURTH_FILE - IsFlagOn], "r");
    FILE* target = fopen(argv[FIFTH_FILE - IsFlagOn], "w+");

    if(!students || !courses || !hackers || !queues || !target)
    {
        closeFiles(students, courses, hackers, queues, target);
        return 0;
    }
    EnrollmentSystem system = createEnrollment(students, courses, hackers);
    if(system == NULL)
    {
        return freeProgram(system,students, courses, hackers, queues, target);
    }
    if (enrollmentSystemUpdateFlag(system, IsFlagOn) != ENROLLMENT_SYSTEM_SUCCESS)
    {
        return freeProgram(system,students, courses, hackers, queues, target);
    }
    if((system = readEnrollment(system, queues)) == NULL)
    {
        return freeProgram(system,students, courses, hackers, queues, target);
    }
    hackEnrollment(system, target);
    printEnrollmentSystem(system);
    return freeProgram(system,students, courses, hackers, queues, target);
}