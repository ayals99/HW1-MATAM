#ifndef NODE_H
#define NODE_H

#include "IsraeliQueue.h"
#include "Person.h"

/** Type for defining the Node */
typedef struct Node_t Node;


/**
 * nodeCreate: Allocates a new node with an Item pointer and a pointer to the
 * previous node and the next node, including friends that passed and foes that
 * got blocked.
 *
 * gets - Item
 *
 * return - the Node if successful or NULL in case of any error.
 */
Node* nodeCreate(void*);

/**
 * nodeDestroy: Deallocates an existing node.
 * Gets the node we wish to destroy.
 */
void nodeDestroy(Node*);

/**
 * addNodeAfter: Puts a new node between the current and next Nodes.
 * gets the current Node and the Node to inject.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError addNodeAfter(Node*, Node*);

/**
 * addNodeBefore: Puts a new node between the current and previous Nodes.
 * gets the current Node and the Node to inject.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError addNodeBefore(Node*, Node*);



/** Getter Functions */

/**
 * nodeGetNext: Getter for the next Node.
 * gets the Node.
 *
 * return - a pointer to the next Node, or NULL if the next is NULL;
 */
Node* nodeGetNext(Node*);

/**
 * nodeGetPrevious: Getter for the previous Node.
 * gets the Node.
 *
 * return - a pointer to the previous Node; (Any extreme cast that
 * the return value is anything but a ptr?)
 */
Node* nodeGetPrevious(Node*);

/**
 * nodeGetItem: Getter for the Item.
 * gets the node.
 *
 * return - a pointer to the Item;
 */
void* nodeGetItem(Node*);



/** Setter Functions */

/**
 * nodeSetItem: Adds an Item ptr to the selected Node.
 * gets: a Node ptr and an Item ptr.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError nodeSetItem(Node*, void*);

/**
 * nodeSetNext: sets the Next node to the given one in the function.
 * gets: a Node ptr and a Next ptr.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError nodeSetNext(Node*, Node*)

/**
 * nodeSetPrevious: sets the Previous node to the given one in the function.
 * gets: a Node ptr and a Previous ptr.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
IsraeliQueueError nodeSetPrevious(Node*, Node*)


#endif
