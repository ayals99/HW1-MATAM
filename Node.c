#include <stdlib.h>
#include <assert.h>

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


NodeError addNodeAfter(Node* currNode, Node* newNode)
{
    if(newNode == NULL || currNode == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    newNode->previous = currNode;
    newNode->next = currNode->next;
    if(currNode->next == NULL)
    {
        currNode->next = newNode;
        return NODE_ERROR_SUCCESS;
    }
    currNode->next->previous = newNode;
    currNode->next = newNode;
    return NODE_ERROR_SUCCESS;
}

NodeError addNodeBefore(Node* currNode, Node* newNode)
{
    if(newNode == NULL || currNode == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    newNode->next = currNode;
    newNode->previous = currNode->previous;
    currNode->previous->next = newNode;
    currNode->previous = newNode;
    return NODE_ERROR_SUCCESS;
}

NodeError addPassCount(Node* node)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->passCount += 1;
    return NODE_ERROR_SUCCESS;
}

NodeError addBlockCount(Node* node)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->blockCount += 1;
    return NODE_ERROR_SUCCESS;
}

NodeError resetCount(Node* node)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->blockCount = INITIALIZATION;
    node->passCount = INITIALIZATION;
    return NODE_ERROR_SUCCESS;
}

Node* cloneNode(Node* nodeToClone)
{
    assert(nodeToClone != NULL);
    Node* clonedNode = nodeCreate(nodeToClone->Item);
    if(clonedNode == NULL)
    {
        return NULL;
    }
    clonedNode->next = nodeToClone->next;
    clonedNode->previous = nodeToClone->previous;
    clonedNode->passCount = nodeToClone->passCount;
    clonedNode->blockCount = nodeToClone->blockCount;
    return clonedNode;
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

NodeError nodeSetItem(Node* node, void* itemToSet)
{
    if(node == NULL || itemToSet == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->Item = itemToSet;
    return NODE_ERROR_SUCCESS;
}

NodeError nodeSetNext(Node* node, Node* nextToSet)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->next = nextToSet;
    return NODE_ERROR_SUCCESS;
}

NodeError nodeSetPrevious(Node* node, Node* preToSet)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->previous = preToSet;
    return NODE_ERROR_SUCCESS;
}
