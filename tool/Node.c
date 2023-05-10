#include <stdlib.h>
#include <assert.h>

#include "../tool/Node.h"

#define INITIALIZATION 0

/** Struct declaration */

struct Node_t{
    void* m_Item;
    int m_passCount;
    int m_blockCount;
    Node m_next;
    Node m_previous;
};

/** Function Implementations */

Node nodeCreate(void* m_item)
{
    Node newNode = malloc(sizeof(*newNode));
    if(!newNode)
    {
        return NULL;
    }
    newNode->m_Item = m_item;
    newNode->m_next = NULL;
    newNode->m_previous = NULL;
    newNode->m_passCount = INITIALIZATION;
    newNode->m_blockCount = INITIALIZATION;
    return newNode;
}

void nodeDestroy(Node toDestroy)
{
    if(toDestroy == NULL)
    {
        return;
    }
    free(toDestroy);
}

NodeError addNodeAfter(Node currNode, Node newNode)
{
    if(newNode == NULL || currNode == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    newNode->m_previous = currNode;
    newNode->m_next = currNode->m_next;
    if(currNode->m_next == NULL)
    {
        currNode->m_next = newNode;
        return NODE_ERROR_SUCCESS;
    }
    currNode->m_next->m_previous = newNode;
    currNode->m_next = newNode;
    return NODE_ERROR_SUCCESS;
}



NodeError addPassCount(Node node)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->m_passCount += 1;
    return NODE_ERROR_SUCCESS;
}

NodeError addBlockCount(Node node)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->m_blockCount += 1;
    return NODE_ERROR_SUCCESS;
}

Node cloneNode(Node nodeToClone)
{
    assert(nodeToClone != NULL);
    Node clonedNode = nodeCreate(nodeToClone->m_Item);
    if(clonedNode == NULL)
    {
        return NULL;
    }
    clonedNode->m_next = nodeToClone->m_next;
    clonedNode->m_previous = nodeToClone->m_previous;
    clonedNode->m_passCount = nodeToClone->m_passCount;
    clonedNode->m_blockCount = nodeToClone->m_blockCount;
    return clonedNode;
}

/** Getter Functions Implementation */

Node nodeGetNext(Node node)
{
    return (node == NULL) ? NULL : node->m_next;//Implement this style for the rest of the functions.
}

Node nodeGetPrevious(Node node)
{
    if (node == NULL)
    {
        return NULL;
    }
    return node->m_previous;
}

void* nodeGetItem(Node node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->m_Item;
}

int nodeGetPassCount(Node node)
{
    if(node == NULL){
        return NODE_ERROR_BAD_PARAM;
    }
    return node->m_passCount;
}

int nodeGetBlockCount(Node node)
{
    if(node == NULL){
        return NODE_ERROR_BAD_PARAM;
    }
    return node->m_blockCount;
}


/** Setter Functions Implementation */

NodeError nodeSetNext(Node node, Node nextToSet)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->m_next = nextToSet;
    return NODE_ERROR_SUCCESS;
}

NodeError nodeSetPrevious(Node node, Node preToSet)
{
    if(node == NULL)
    {
        return NODE_ERROR_BAD_PARAM;
    }
    node->m_previous = preToSet;
    return NODE_ERROR_SUCCESS;
}