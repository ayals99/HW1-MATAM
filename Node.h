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



/** Getter Functions */

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
 * nodeGetPerson: Getter for the Person.
 * gets the Person.
 *
 * return - a pointer to the person;
 */
Person* nodeGetPerson(Node* node);



/** Setter Functions */

/**
 * nodeSetPerson: Adds a Person ptr to the selected Node.
 * gets: a Node ptr and a Person ptr.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError nodeSetPerson(Node* node, Person* newPerson);

/**
 * nodeSetNext: sets the Next node to the given one in the function.
 * gets: a Node ptr and a Next ptr.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError nodeSetNext(Node* node, Node* nextToSet)

/**
 * nodeSetPrevious: sets the Previous node to the given one in the function.
 * gets: a Node ptr and a Previous ptr.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError nodeSetPrevious(Node* node, Node* preToSet)


#endif
