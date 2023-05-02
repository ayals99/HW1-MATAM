#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IsraeliQueue.h"

typedef struct Person_t {
    char* name;
    int age;
    int height;
} Person;

int comparePersons(void* person1, void* person2) {
    Person* p1 = (Person*) person1;
    Person* p2 = (Person*) person2;
    if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age) {
        return 1;
    } else {
        return 0;
    }
}

int areFriends1(void* person1, void* person2) {
    return ((Person*)person1)->height && ((Person*)person2)->height;
}

int areFriends2(void* person1, void* person2) {
    return ((Person*)person1)->age % 2 == 0 && ((Person*)person2)->age % 2 == 0;
}

int main() {
    FriendshipFunction friendshipFunctions[] = {areFriends1, areFriends2, NULL};
    ComparisonFunction comparisonFunction = comparePersons;
    IsraeliQueue queue = IsraeliQueueCreate(friendshipFunctions, comparisonFunction, 3, 2);

    Person* person1 = malloc(sizeof(*person1));
    person1->name = "John";
    person1->age = 30;
    person1->height = 175;

    Person* person2 = malloc(sizeof(*person2));
    person2->name = "Jane";
    person2->age = 25;
    person2->height = 165;

    Person* person3 = malloc(sizeof(*person3));
    person3->name = "Bob";
    person3->age = 40;
    person3->height = 180;

    IsraeliQueueEnqueue(queue, person1);
    IsraeliQueueEnqueue(queue, person2);
    IsraeliQueueEnqueue(queue, person3);

     IsraeliQueueImprovePositions(queue);

    IsraeliQueueDestroy(queue);
    return 0;
}
