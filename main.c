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
//
//  #define STUDENTS_FILES_1 "\Tests\Test 1 - 1 hacker\students.txt"
//  #define COURSES_FILES_1 "\Tests\Test 1 - 1 hacker\courses.txt"
//  #define HACKERS_FILES_1 "\Tests\Test 1 - 1 hacker\hackers.txt"
//  #define QUEUES_FILES_1 "\Tests\Test 1 - 1 hacker\queues.txt"
//  #define TARGET_FILES_1 "\Tests\Test 1 - 1 hacker\target.txt"
//
//  #define STUDENTS_FILES_2 "\Tests\Test2 - 1 hacker (no demands)\students.txt"
//  #define COURSES_FILES_2 "\Tests\Test2 - 1 hacker (no demands)\courses.txt"
//  #define HACKERS_FILES_2 "\Tests\Test2 - 1 hacker (no demands)\hackers.txt"
//  #define QUEUES_FILES_2 "\Tests\Test2 - 1 hacker (no demands)\queues.txt"
// #define TARGET_FILES_2 "\Tests\Test2 - 1 hacker (no demands)\target.txt"
//
//  #define STUDENTS_FILES_3 "\Tests\Test3 - 1 hacker (empty queue)\students.txt"
//  #define COURSES_FILES_3 "\Tests\Test3 - 1 hacker (empty queue)\courses.txt"
//  #define HACKERS_FILES_3 "\Tests\Test3 - 1 hacker (empty queue)\hackers.txt"
//  #define QUEUES_FILES_3 "\Tests\Test3 - 1 hacker (empty queue)\queues.txt"
//  #define TARGET_FILES_3 "\Tests\Test3 - 1 hacker (empty queue)\target.txt"
//
//  bool test1(){
//      FILE* students = fopen(STUDENTS_FILES_1, "r");
//      FILE* courses = fopen(COURSES_FILES_1, "r");
//      FILE* hackers = fopen(HACKERS_FILES_1, "r");
//      FILE* queues = fopen(QUEUES_FILES_1, "r");
//      FILE* target = fopen(TARGET_FILES_1, "w+");
//      EnrollmentSystem system = createEnrollment(students, courses, hackers);
//      if(system == NULL){
//           return false;
//      }
//      system = readEnrollment(system, courses);
//      hackEnrollment(system, target);
//      enrollmentDestroy(system);
//      fclose(target);
//      fopen(target, "r");
//
// }


int main(int argc, char** argv){
    if(argc > 7 || argc < 6){
        assert(argc > 7 || argc < 6);
    }
    char* studentPath = "C:\\Users\\ayals\\Downloads\\Tests (1)\\Tests\\Test1 - 1 hacker\\students.txt";
    char* hackersPath = "C:\\Users\\ayals\\Downloads\\Tests (1)\\Tests\\Test1 - 1 hacker\\hackers.txt";
    char* coursesPath = "C:\\Users\\ayals\\Downloads\\Tests (1)\\Tests\\Test1 - 1 hacker\\courses.txt";
    char* queuesPath = "C:\\Users\\ayals\\Downloads\\Tests (1)\\Tests\\Test1 - 1 hacker\\queues.txt";

    int IsFlagOn = checkForFlag(argc - 1, argv);
//    FILE* students = fopen(argv[2 - IsFlagOn], "r");
    FILE* students = fopen(studentPath, "r");
    FILE* courses = fopen(coursesPath, "r");
    FILE* hackers = fopen(hackersPath, "r");
    FILE* queues = fopen(queuesPath, "r");

//    FILE* courses = fopen(argv[3 - IsFlagOn], "r");
//    FILE* hackers = fopen(argv[4 - IsFlagOn], "r");
//    FILE* queues = fopen(argv[5 - IsFlagOn], "r");
//    FILE* target = fopen(argv[6 - IsFlagOn], "w+");

    FILE* target = fopen("C:\\Users\\ayals\\Downloads\\Tests (1)\\Tests\\Test1 - 1 hacker\\target.txt", "w+");
    EnrollmentSystem system = createEnrollment(students, courses, hackers);
    if(system == NULL){
        assert(system != NULL);
        closeFiles(students, courses, hackers, queues, target);
        return 4;
    }
    if (enrollmentSystemUpdateFlag(system, IsFlagOn) != ENROLLMENT_SYSTEM_SUCCESS){
        assert(system != NULL);
        closeFiles(students, courses, hackers, queues, target);
        return 2;
    }
    system = readEnrollment(system, queues);
    if(system == NULL){
        assert(system != NULL);
        closeFiles(students, courses, hackers, queues, target);
        return 3;
    }
    hackEnrollment(system, target);
    enrollmentDestroy(system);
    closeFiles(students, courses, hackers, queues, target);
    return 0;
}