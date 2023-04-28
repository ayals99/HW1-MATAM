#include <stdlib.h>

#include "Node.h"

/** Struct declaration */

struct Node_t{
    void* Item = NULL;
    int passCount = 0;
    int blockCount = 0;
    Node* next = NULL;
    Node* previous = NULL;
};

/**Function Implementations */

Node* nodeCreate(void* item)
{
    Node* newNode = malloc(sizeof(newNode));
    if(!newNode)
    {
        return NULL;
    }
    newNode->Item = item;
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
    node->blockCountCount += 1;
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
    node->next = preToSet;
    return ISRAELIQUEUE_SUCCESS;
}
