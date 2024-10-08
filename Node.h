#ifndef NODE_H
#define NODE_H


/** Type for defining the Node */
typedef struct Node_t* Node;
typedef enum {NODE_ERROR_BAD_PARAM = -1, NODE_ERROR_SUCCESS} NodeError;

/**
 * nodeCreate: Allocates a new node with an Item pointer and a pointer to the
 * previous node and the next node, including friends that passed and foes that
 * got blocked.
 *
 * gets - Item
 *
 * return - the Node if successful or NULL in case of any error.
 */
Node nodeCreate(void*);

/**
 * nodeDestroy: Deallocates an existing node.
 * Gets the node we wish to destroy.
 */
void nodeDestroy(Node);

/**
 * addNodeAfter: Puts a new node between the current and next Nodes.
 * gets the current Node and the Node to inject.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
NodeError addNodeAfter(Node, Node);

/**
 * addPassCount: add +1 to the passCount of the given node.
 * gets a node.
 *
 * @return - BAD_PARAM if the node is NULL or SUCCESS otherwise.
 */
NodeError addPassCount(Node);

/**
 * addBlockCount: add +1 to the blockCount of the given node.
 * gets a node.
 *
 * @return - BAD_PARAM if the node is NULL or SUCCESS otherwise.
 */
NodeError addBlockCount(Node);


/**
 * cloneNode: clones a node with the exact same parameters. but the cloned item
 * pointer points to the same item (they share the item basically)
 * gets a node.
 *
 * @return - NULL if the node is NULL or the clonedNode otherwise.
 */
Node cloneNode(Node);

/** Getter Functions */

/**
 * nodeGetNext: Getter for the next Node.
 * gets the Node.
 *
 * return - a pointer to the next Node, or NULL if the next is NULL;
 */
Node nodeGetNext(Node);

/**
 * nodeGetPrevious: Getter for the previous Node.
 * gets the Node.
 *
 * return - a pointer to the previous Node; (Any extreme cast that
 * the return value is anything but a ptr?)
 */
Node nodeGetPrevious(Node);

/**
 * nodeGetItem: Getter for the Item.
 * gets the node.
 *
 * return - a pointer to the Item;
 */
void* nodeGetItem(Node);

/**
 * nodeGetPassCount: Getter for the passCount.
 * gets the node.
 *
 * return - The passCount, NEEDS TO ESTABLISH AND ERROR MESSAGE
 */
int nodeGetPassCount(Node);

/**
 * nodeGetBlockCount: Getter for the blockCount.
 * gets the node.
 *
 * return - The blockCount, NEEDS TO ESTABLISH AND ERROR MESSAGE
 */
int nodeGetBlockCount(Node);


/** Setter Functions */


/**
 * nodeSetNext: sets the Next node to the given one in the function.
 * @param Node, a ptr to the current node.
 * @param Node a ptr to the node we with to set next.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
NodeError nodeSetNext(Node, Node);

/**
 * nodeSetPrevious: sets the Previous node to the given one in the function.
 * @param Node, a ptr to the current node.
 * @param Node a ptr to the node we with to set previous.
 *
 * return - BAD_PARAM if any of the parameters are NULL Or SUCCESS otherwise
 */
NodeError nodeSetPrevious(Node, Node);

#endif
