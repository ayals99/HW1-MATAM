#include <stdlib.h>

#include "Node.h"

#define INITIALIZATION 0;

/** Struct declaration */

struct Node_t{
    void* Item;
    int passCount;
    int blockCount;
    Node* next;
    Node* previous;
};

/** Function Implementations */

Node* nodeCreate(void* item)
{
    Node* newNode = malloc(sizeof(*newNode));
    if(!newNode)
    {
        return NULL;
    }
    newNode->Item = item;
    newNode->next = NULL;
    newNode->previous = NULL;
    newNode->passCount = INITIALIZATION;
    newNode->blockCount = INITIALIZATION;
    return newNode;
}

void nodeDestroy(Node* toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    free(toDestroy);
}


IsraeliQueueError addNodeAfter(Node* currNode, Node* newNode)
{
    if(newNode == NULL || currNode == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    newNode->previous = currNode;
    newNode->next = currNode->next;
    // if(currNode->next != NULL) // this is in case currNode is the last in the list and doesn't have a next
    // {
    //      currNode->next->previous = newNode;
    // }
    currNode->next->previous = newNode; // AYAL: What happens if "next" is NULL?
    currNode->next = newNode;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError addNodeBefore(Node* currNode, Node* newNode)
{
    if(newNode == NULL || currNode == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    newNode->next = currNode;
    newNode->previous = currNode->previous;
    // if(currNode->previous != NULL) // this is in case currNode is the first in the list and doesn't have a previous
    // {
    //      currNode->previous->next = newNode;
    // }
    currNode->previous->next = newNode; // AYAL: What happens if "previous" is NULL? I think this needs to be changed
    currNode->previous = newNode;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError addPassCount(Node* node)
{
    if(node == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    node->passCount += 1;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError addBlockCount(Node* node)
{
    if(node == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    node->blockCount += 1;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError resetCount(Node* node)
{
    if(node == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    node->blockCount = INITIALIZATION;
    node->passCount = INITIALIZATION;
    return ISRAELIQUEUE_SUCCESS;
}


/** Getter Functions Implementation */

Node* nodeGetNext(Node* node)
{
    return (node == NULL) ? NULL : node->next;//Implement this style for the rest of the functions.
}

Node* nodeGetPrevious(Node* node)
{
    if (node == NULL)
    {
        return NULL;
    }
    return node->previous;
}

void* nodeGetItem(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->Item;
}

int nodeGetPassCount(Node* node)
{
    return node->passCount;
}

int nodeGetBlockCount(Node* node)
{
    return node->blockCount;
}


/** Setter Functions Implementation */

IsraeliQueueError nodeSetItem(Node* node, void* itemToSet)
{
    if(node == NULL || itemToSet == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    node->Item = itemToSet;
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
    node->previous = preToSet;
    return ISRAELIQUEUE_SUCCESS;
}
