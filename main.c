#include <stdio.h>
#include <stdlib.h>
#include "HackEnrollment.h" // Assuming the enrollment-related structures and functions are defined in this header file

int main() {
    const char *students_filename = "C:\\Users\\user\\Documents\\GitHub\\ex1---Berko-and-Ayal\\ExampleTest\\students.txt";
    const char *courses_filename = "C:\\Users\\user\\Documents\\GitHub\\ex1---Berko-and-Ayal\\ExampleTest\\courses.txt";
    const char *hackers_filename = "C:\\Users\\user\\Documents\\GitHub\\ex1---Berko-and-Ayal\\ExampleTest\\hackers.txt";
    const char *queues_filename = "C:\\Users\\user\\Documents\\GitHub\\ex1---Berko-and-Ayal\\ExampleTest\\queues.txt";

    FILE *students_file = fopen(students_filename, "r");
    if (students_file == NULL)
    {
        printf("Error opening students file.\n");
        return 1;
    }

    FILE *courses_file = fopen(courses_filename, "r");
    if (courses_file == NULL)
    {
        printf("Error opening courses file.\n");
        fclose(students_file);
        return 1;
    }

    FILE *hackers_file = fopen(hackers_filename, "r");
    if (hackers_file == NULL)
    {
        printf("Error opening hackers file.\n");
        fclose(students_file);
        fclose(courses_file);
        return 1;
    }

    FILE *queues_file = fopen(queues_filename, "r");
    if (queues_file == NULL)
    {
        printf("Error opening queues file.\n");
        fclose(students_file);
        fclose(courses_file);
        fclose(hackers_file);
        return 1;
    }

    EnrollmentSystem enrollment_system = createEnrollment(students_file, courses_file, hackers_file);
    if (enrollment_system == NULL)
    {
        printf("Error creating enrollment system.\n");
        fclose(students_file);
        fclose(courses_file);
        fclose(hackers_file);
        fclose(queues_file);
        return 1;
    }


    EnrollmentSystem updated_system = readEnrollment(enrollment_system, queues_file);
    if (updated_system == NULL)
    {
        printf("Error reading enrollment data from queues file.\n");
        fclose(students_file);
        fclose(courses_file);
        fclose(hackers_file);
        fclose(queues_file);
        enrollmentDestroy(enrollment_system);
        return 1;
    }

    // You can perform operations on the updated_system here, e.g., enrolling students, adding courses, etc.

    // Clean up and close the files
    enrollmentDestroy(updated_system);
    fclose(students_file);
    fclose(courses_file);
    fclose(hackers_file);
    fclose(queues_file);

    return 0;
}
