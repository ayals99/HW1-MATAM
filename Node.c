#include <stdlib.h>

#include "Node.h"

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
    newNode->passCount = 0;
    newNode->blockCount = 0;
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
    if(newNode == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    if(currNode == NULL)
    {
        currNode = newNode;
        return ISRAELIQUEUE_SUCCESS;
    }
    newNode->previous = currNode;
    newNode->next = currNode->next;
    currNode->next->previous = newNode;
    currNode->next = newNode;
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
    currNode->previous->next = newNode;
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
    if(node == NULL)
    {
        //We need to establish an ERROR return message.
        return -1;
    }
    return node->passCount;
}

int nodeGetBlockCount(Node* node)
{
    if(node == NULL)
    {
        //We need to establish an ERROR return message.
        return -1;
    }
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
