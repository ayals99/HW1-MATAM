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

Node* nodeCreate()
{
    Node* newNode = malloc(sizeof(newNode));
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
    free(toDestroy);
}

IsraeliQueueError addNodeAfter(Node* currNode, Node* newNode)
{
    if(currNode == NULL || newNode == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    newNode->previous = currNode;
    newNode->next = currNode->next;
    currNode->next = newNode;
    currNode->next->previous = newNode;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError addNodeBefore(Node* currNode, Node* newNode)
{
    if(currNode == NULL || newNode == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    newNode->next = currNode;
    newNode->previous = currNode->previous;
    currNode->previous = newNode;
    currNode->previous->next = newNode;
    return ISRAELIQUEUE_SUCCESS;
}



/** Getter Functions Implementation */

Node* nodeGetNext(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->next;
}

Node* nodeGetPrevious(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->previous;
}

Person* nodeGetPerson(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->person;
}


/** Setter Functions Implementation */

IsraeliQueueError nodeSetPerson(Node* node, Person* newPerson)
{
    if(node == NULL || newPerson == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    node->person = newPerson;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError nodeSetNext(Node* node, Node* nextToSet)
{
    if(node == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    node->next = nextToSet;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError nodeSetPrevious(Node* node, Node* preToSet)
{
    if(node == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    node->next = preToSet;
    return ISRAELIQUEUE_SUCCESS;
}
