#ifndef NODE_H
#define NODE_H

#include "IsraeliQueue.h"
#include "Person.h"

/** Type for defining the Node */
typedef struct Node_t Node;

typedef void (*FreePerson)(void*);

/**
 * nodeCreate: Allocates a new node with a Person struct and a pointer to the
 * previous node and the next one.
 *
 * return - the Node if successful or NULL in case of any error.
 */
Node* nodeCreate();

/**
 * nodeDestroy: Deallocates an existing node, including its Person.
 * Gets the node and the function: freePerson.
 */
void nodeDestroy(Node* toDestroy, FreePerson free_person);


/**
 * nodeGetNext: Getter for the next Node.
 * gets the Node.
 *
 * return - a pointer to the next Node, or NULL if the next is NULL;
 */
Node* nodeGetNext(Node* node);

/**
 * nodeGetPrevious: Getter for the previous Node.
 * gets the Node.
 *
 * return - a pointer to the previous Node; (Any extreme cast that
 * the return value is anything but a ptr?)
 */
Node* nodeGetPrevious(Node* node);

/**
 * addNodeAfter: Puts a new node between the current and next Nodes.
 * gets the current Node and the Node to inject.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError addNodeAfter(Node* currNode, Node* newNode);

/**
 * addNodeBefore: Puts a new node between the current and previous Nodes.
 * gets the current Node and the Node to inject.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError addNodeBefore(Node* currNode, Node* newNode);

/**
 * addPersonToNode: Adds a Person ptr to the selected Node.
 * gets: a Node ptr and a Person ptr.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError addPersonToNode(Node* node, Person* newPerson);

#endif
