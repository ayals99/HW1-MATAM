#include <stdlib.h>

#include "Node.h"
#include "Person.h"

/** Struct declaration */

struct Node_t{
    Person* person;
    Node* next;
    Node* previous;
};

/**Function Implementations */

Node nodeCreate()
{
    Node newNode = (Node)malloc(sizeof(newNode));
    if(!newNode)
    {
        return NULL;
    }
    return newNode;
}

void nodeDestroy(Node* toDestroy, FreePerson free_person)
{
    if(toDestroy == NULL)
    {
        return;
    }
    free_person(toDestroy->person);
    free(node);
}
