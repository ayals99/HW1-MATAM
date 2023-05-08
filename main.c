#include <stdio.h>
#include <assert.h>

#define OFF 0
#define ON 1

#include "HackEnrollment.h" // Assuming the enrollment-related structures and functions are defined in this header file

void closeFiles(FILE* students, FILE* courses, FILE* hackers, FILE* queues, FILE* target){
    fclose(students);
    fclose(courses);
    fclose(hackers);
    fclose(queues);
    fclose(target);
}

int checkForFlag(int numberOfInputs, char** argv){
    int isFlagOn = OFF;
    for (int i = 1; i<numberOfInputs; i++){
        int j = 0;
        while( *(argv[i] + j) != '\0'){
            if( *(argv[i] + j) == '-' && *(argv[i] + j + 1) == 'i'){
                isFlagOn = ON;
            }
            j++;
        }
    }
    return isFlagOn;
}

int main(int argc, char** argv){
    if(argc > 7 || argc < 6){
        return 1;
    }
    int IsFlagOn = checkForFlag(argc - 1, argv);
    FILE* students = fopen(argv[2 - IsFlagOn], "r");
    FILE* courses = fopen(argv[3 - IsFlagOn], "r");
    FILE* hackers = fopen(argv[4 - IsFlagOn], "r");
    FILE* queues = fopen(argv[5 - IsFlagOn], "r");
    FILE* target = fopen(argv[6 - IsFlagOn], "w");

    EnrollmentSystem system = createEnrollment(students, courses, hackers);
    if(system == NULL){
        assert(system == NULL);
        closeFiles(students, courses, hackers, queues, target);
        return 1;
    }
    if (enrollmentSystemUpdateFlag(system, IsFlagOn) != ENROLLMENT_SYSTEM_SUCCESS){
        assert(system == NULL);
        closeFiles(students, courses, hackers, queues, target);
        return 1;
    }
    system = readEnrollment(system, courses);
    if(system == NULL){
        assert(system == NULL);
        closeFiles(students, courses, hackers, queues, target);
        return 1;
    }
    hackEnrollment(system, target);
    enrollmentDestroy(system);
    closeFiles(students, courses, hackers, queues, target);
    return 0;
}