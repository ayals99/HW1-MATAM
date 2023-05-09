#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include "IsraeliQueue.h"
#include "Node.h"

#define EMPTY_QUEUE 0

/** Struct declaration */

struct IsraeliQueue_t {
    FriendshipFunction* friendshipFunctions;
    ComparisonFunction comparisonFunction;
    Node* head;
    int friendshipThreshold;
    int rivalryThreshold;
};

/** Type for defining the Relationship */

typedef enum {FRIENDS, FOES, NEUTRAL} Relationship;

/** Function Signatures */

Node* getLastElement(IsraeliQueue queue);
int countFunction(FriendshipFunction* array);
FriendshipFunction* createFriendshipFunction(FriendshipFunction* friendshipFunctions);
Relationship getRelationship(IsraeliQueue queue, Node* existing, Node* toAdd);
Node* findFriend(IsraeliQueue queue, Node* current, Node* nodeToAdd);
Node* findFoe(IsraeliQueue queue, Node* current, Node* nodeToAdd);
Node* getClonedNode(IsraeliQueue clonedQueue, Node* lastOriginalNode);
void removeNode(IsraeliQueue queue, Node* toRemove);
int countQueues(IsraeliQueue* queueArray);
int countAllFunctions(IsraeliQueue* queueArray, int numberOfQueues);
int getAverageFriendshipThreshold(IsraeliQueue* queueArray, int numberOfQueues);
int getNewRivalryThreshold(IsraeliQueue* queueArray, int numberOfQueues);
void initializeFriendshipArray(FriendshipFunction* newFriendshipArray, IsraeliQueue* queueArray);
void mergeQueues(IsraeliQueue newQueue,IsraeliQueue* queueArray,int numberOfQueues);
FriendshipFunction* cloneFriendshipFunctions(FriendshipFunction* original);
void cloneAllNodes(IsraeliQueue original, IsraeliQueue clonedQueue);
void addFirstNode(IsraeliQueue queue, Node* node);
IsraeliQueueError addToEnd(IsraeliQueue queue, Node* toAdd);
IsraeliQueueError enqueueNode(IsraeliQueue queue,Node* nodeToAdd);
Node** makeNodeArray(IsraeliQueue queue, int queueSize);



/** Function Implementations */

int countFunction(FriendshipFunction* array)
{
    int counter = 0;
    while (*array != NULL)
    { // It's a given that the function array ends with NULL
        counter++;
        array++;
    }
    return counter;
}

FriendshipFunction* createFriendshipFunction(FriendshipFunction* friendshipFunctions)
{
    int numberOfFunctions = countFunction(friendshipFunctions);
    FriendshipFunction* friendshipArray = (FriendshipFunction*)malloc(sizeof(FriendshipFunction) * (numberOfFunctions + 1));
    if (friendshipArray == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < numberOfFunctions + 1; i++)
    {
        friendshipArray[i] = friendshipFunctions[i];
    }
    return friendshipArray;
}

/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunctions,
                                ComparisonFunction comparisonFunction,
                                int friendship_th,
                                int rivalry_th)
{
    if (friendshipFunctions == NULL || comparisonFunction == NULL)
    {
     return NULL;
    }
    IsraeliQueue newQueue = (IsraeliQueue)malloc(sizeof(*newQueue));
    if (newQueue == NULL)
    {
        return NULL;
    }
    FriendshipFunction* newFunctionsArray = createFriendshipFunction(friendshipFunctions);
    if (newFunctionsArray == NULL)
    {
        IsraeliQueueDestroy(newQueue);
        return NULL;
    }
    newQueue -> friendshipFunctions = newFunctionsArray;
    newQueue -> comparisonFunction = comparisonFunction;
    newQueue -> head = NULL;
    newQueue -> friendshipThreshold = friendship_th;
    newQueue -> rivalryThreshold = rivalry_th;
    return newQueue;
}

Relationship getRelationship(IsraeliQueue queue, Node* existing, Node* toAdd)
{
    int numberOfFunctions = countFunction(queue->friendshipFunctions);
    int friendShipThreshold = queue->friendshipThreshold;
    int rivalryThreshold = queue->rivalryThreshold;
    double average = 0;
    if (numberOfFunctions == 0)
    {
        return NEUTRAL;
    }
    FriendshipFunction* array = queue->friendshipFunctions;
    void* exitingItem = nodeGetItem(existing);
    void* toAddItem = nodeGetItem(toAdd);
    for (int i = 0; i < numberOfFunctions; i++)
    {
        int friendshipFunctionResult = (array[i])(exitingItem,toAddItem);
        if(friendshipFunctionResult > friendShipThreshold && (nodeGetPassCount(existing) < FRIEND_QUOTA))
        {
            return FRIENDS;
        }
        average += friendshipFunctionResult;
    }
    // We only get here if "existing" and "toAdd" are not friends according to all functions in the array.
    average /= numberOfFunctions;
    average = ((int)average < average) ? (double)((int)average + 1) : average;
    if (average < rivalryThreshold && nodeGetBlockCount(existing) < RIVAL_QUOTA)
    {
        return FOES;
    }
    else
    {
        return NEUTRAL;
    }
}

Node* findFriend(IsraeliQueue queue, Node* current, Node* nodeToAdd)
{
    if(current == NULL)
    {
        return NULL;
    }
    Relationship relationshipStatus = getRelationship(queue, current, nodeToAdd);
    while(relationshipStatus != FRIENDS && current != NULL)
    {
        current = nodeGetNext(current);
        if (current == NULL)
        {
            break;
        }
        relationshipStatus = getRelationship(queue, current, nodeToAdd);
    }
    return current;
}

Node* findFoe(IsraeliQueue queue, Node* current, Node* nodeToAdd)
{
    if(current == NULL)
    {
        return NULL;
    }
    Relationship relationshipStatus = getRelationship(queue, current, nodeToAdd);
    while(relationshipStatus != FOES && current != NULL)
    {
        current = nodeGetNext(current);
        if (current == NULL)
        {
            break;
        }
        relationshipStatus = getRelationship(queue, current, nodeToAdd);
    }
    return current;
}

IsraeliQueueError addToEnd(IsraeliQueue queue, Node* toAdd)
{
    assert(queue != NULL && toAdd != NULL);
    Node* lastNode = getLastElement(queue);
    if (lastNode == NULL)
    {
        addFirstNode(queue, toAdd);
        return ISRAELIQUEUE_SUCCESS;
    }
    if(addNodeAfter(lastNode, toAdd) != NODE_ERROR_SUCCESS)
    {
        return ISRAELI_QUEUE_ERROR;
    }
    return ISRAELIQUEUE_SUCCESS;
}


IsraeliQueueError enqueueNode(IsraeliQueue queue, Node* nodeToAdd)
{
    if (*(queue->friendshipFunctions) == NULL)
    {
        return addToEnd(queue, nodeToAdd);
    }
    Node* potentialFriend = findFriend(queue, queue->head, nodeToAdd);
    Node* potentialFoe = NULL;
    while (potentialFriend != NULL)
    {
        potentialFoe = findFoe(queue, nodeGetNext(potentialFriend), nodeToAdd);
        if (potentialFoe == NULL)
        {
            if (addNodeAfter(potentialFriend, nodeToAdd) == NODE_ERROR_SUCCESS)
            {
                addPassCount(potentialFriend);
                return ISRAELIQUEUE_SUCCESS;
            }
            return ISRAELIQUEUE_BAD_PARAM;
        }
        addBlockCount(potentialFoe);
        potentialFriend = findFriend(queue, nodeGetNext(potentialFoe),nodeToAdd);
    }
    return addToEnd(queue, nodeToAdd);
}
// The second version of this implementation is that the node that we want to
// insert is inserted after the rival the blocks him.

//  return addNodeAfter(potentialFoe, nodeToAdd);





/**@param IsraeliQueue: an IsraeliQueue in which to insert the item.
 * @param item: an item to enqueue
 *
 * Places the item in the foremost position accessible to it.*/
IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue queue, void* item)
{
    if(queue == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    Node* nodeToAdd = nodeCreate(item);
    if (nodeToAdd == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    return enqueueNode(queue, nodeToAdd);
}



/**@param IsraeliQueue: an IsraeliQueue to which the function is to be added
 * @param FriendshipFunction: a FriendshipFunction to be recognized by the IsraeliQueue
 * going forward.
 *
 * Makes the IsraeliQueue provided recognize the FriendshipFunction provided.*/
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue queue, FriendshipFunction friendships_function)
{
    if (queue == NULL || friendships_function == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int functionsCounter = countFunction(queue->friendshipFunctions);
    FriendshipFunction* newArray = realloc(queue->friendshipFunctions, (sizeof(FriendshipFunction) * (functionsCounter + 2)));
    // Note to self: multiplying by "functionsCounter + 2" because we didn't count the NULL at the end of the array
    if (newArray == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    *(newArray + functionsCounter) = friendships_function; // The value in this place was NULL
    //Assigning new function to the one before last space of array
    *(newArray + functionsCounter + 1) = NULL; // Accessing the last value in the array so Array will end with NULL
    queue->friendshipFunctions = newArray;
    return ISRAELIQUEUE_SUCCESS;
}

/**@param IsraeliQueue: an IsraeliQueue whose friendship threshold is to be modified
 * @param friendship_threshold: a new friendship threshold for the IsraeliQueue*/
IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int n_thresh)
{
    if(q == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->friendshipThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

/**@param IsraeliQueue: an IsraeliQueue whose rivalry threshold is to be modified
 * @param friendship_threshold: a new rivalry threshold for the IsraeliQueue*/
IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int n_thresh)
{
    if(q == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->rivalryThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

/**Returns the number of elements of the given queue. If the parameter is NULL, 0
 * is returned.*/
int IsraeliQueueSize(IsraeliQueue queue)
{
    if(queue == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int counter = 0;
    Node* current = queue->head;
    while (current != NULL)
    {
        counter++;
        current = nodeGetNext(current);
    }
    return counter;
}

/**Removes and returns the foremost element of the provided queue. If the parameter
 * is NULL or a pointer to an empty queue, NULL is returned.*/
void* IsraeliQueueDequeue(IsraeliQueue q)
{
    if (q == NULL || q->head == NULL){
        return NULL;
    }
    Node* toDestroy = q->head;
    void* item = nodeGetItem(toDestroy);
    q->head = nodeGetNext(q->head);
    if (q->head != NULL)
    {
        nodeSetPrevious(q->head, NULL);
    }
    nodeDestroy(toDestroy);
    return item;

}

/**@param item: an object comparable to the objects in the IsraeliQueue
 *
 * Returns whether the queue contains an element equal to item. If either
 * parameter is NULL, false is returned.*/
bool IsraeliQueueContains(IsraeliQueue queue, void* item){
    if(queue== NULL || queue->head == NULL)
    {
        return false;
    }
    Node* current = queue->head;
    ComparisonFunction compare = queue->comparisonFunction;
    while (current != NULL)
    {
        if (compare(nodeGetItem(current), item))
        {   // question @149 on piazza states that
            // compare will return 1 if identical and 0 if different
            return true;
        }
        current = nodeGetNext(current);
    }
    return false;
}

Node* getLastElement(IsraeliQueue queue){
    if(queue == NULL)
    {
        return NULL;
    }
    if(queue->head == NULL)
    {
        return queue->head;
    }
    Node* current;
    for(current = queue->head; nodeGetNext(current) != NULL; current = nodeGetNext(current));
    return current;
}

Node* getClonedNode(IsraeliQueue clonedQueue, Node* lastOriginalNode)
{
    if(clonedQueue == NULL || lastOriginalNode == NULL)
    {
        return NULL;
    }
    Node* clonedNode = clonedQueue->head;
    if(clonedNode == NULL)
    {
        return NULL;
    }
    while(clonedNode)
    {
        if(clonedQueue->comparisonFunction(nodeGetItem(clonedNode), nodeGetItem(lastOriginalNode)))
        {
            return clonedNode;
        }
        clonedNode = nodeGetNext(clonedNode);
    }
    return NULL;
}

void removeNode(IsraeliQueue queue, Node* toRemove)
{
    Node* next = nodeGetNext(toRemove);
    Node* previous = nodeGetPrevious(toRemove);
    if (next == NULL && previous!= NULL)
    {
        nodeSetNext(previous, NULL);
        return;
    }
    else if(next == NULL && previous == NULL)
    {
        queue->head = NULL;
        return;
    }
    else if(next != NULL && previous == NULL)
    {
        queue->head = next;
        return;
    }
    else
    {
        nodeSetPrevious(next, previous);
        nodeSetNext(previous, next);
        return;
    }

}

Node** makeNodeArray(IsraeliQueue queue, int queueSize)
{
    Node** queueNodeArray = malloc(sizeof(Node*) * queueSize);
    if (queueNodeArray == NULL)
    {
        return NULL;
    }
    Node* current = queue->head;
    Node** tmp = queueNodeArray;
    while (current != NULL)
    {
        *tmp = current;
        current = nodeGetNext(current);
        tmp++;
    }
    return queueNodeArray;
}


/**Advances each item in the queue to the foremost position accessible to it,
 * from the back of the queue frontwards.
*/
IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue queue)
{
    if(queue == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int queueSize = IsraeliQueueSize(queue);
    if (queueSize == EMPTY_QUEUE)
    {
        return ISRAELIQUEUE_SUCCESS;
    }
    Node** nodeArray = makeNodeArray(queue, queueSize);
    if (nodeArray == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    IsraeliQueueError status;
    for(int i = queueSize - 1; i >= 0; i--)
    {
        removeNode(queue, nodeArray[i]);
        status = enqueueNode(queue, nodeArray[i]);
        if (status != ISRAELIQUEUE_SUCCESS)
        {
            return status;
        }
    }
    free(nodeArray);
    return status;
}



int countQueues(IsraeliQueue* queueArray)
{
    int numberOfQueues = 0;
    IsraeliQueue* pointer = queueArray;
    while (pointer != NULL){
        pointer++;
        numberOfQueues++;
    }
    return numberOfQueues;
}

int countAllFunctions(IsraeliQueue* queueArray, int numberOfQueues)
{
    int numberOfFunctions = 0;
    for(int i = 0; i < numberOfQueues; i++)
    {
        numberOfFunctions += countFunction(queueArray[i]->friendshipFunctions);
    }
    return numberOfFunctions;
}

int getAverageFriendshipThreshold(IsraeliQueue* queueArray, int numberOfQueues)
{
    int averageFriendshipThreshold;
    int accumulateFriendshipThreshold = 0;
    for(int i = 0; i < numberOfQueues; i++)
    {
        accumulateFriendshipThreshold += queueArray[i]->friendshipThreshold;
    }
    averageFriendshipThreshold = accumulateFriendshipThreshold / numberOfQueues;
    return averageFriendshipThreshold;
}

int getNewRivalryThreshold(IsraeliQueue* queueArray, int numberOfQueues)
{
    double newRivalryThreshold = 1;
    for(int i = 0; i < numberOfQueues; i++)
    {
        newRivalryThreshold *= abs(queueArray[i]->rivalryThreshold);
    }
    newRivalryThreshold = ceil(pow(newRivalryThreshold, 1.0/(double)numberOfQueues));
    return (int)newRivalryThreshold;
}

void initializeFriendshipArray(FriendshipFunction* newFriendshipArray, IsraeliQueue* queueArray)
{
    assert(newFriendshipArray != NULL && queueArray != NULL);
    for(int i = 0; queueArray[i] != NULL; i++)
    {
        FriendshipFunction* toInsert = queueArray[i]->friendshipFunctions;
        for(int j = 0; toInsert[j] != NULL; j++)
        {
            *newFriendshipArray = toInsert[j];
            newFriendshipArray++;
        }
    }

}

void mergeQueues(IsraeliQueue newQueue,IsraeliQueue* queueArray,int numberOfQueues)
{
    assert(newQueue != NULL && queueArray != NULL && numberOfQueues > 0);
    bool isArrayEmpty = false;
    while(!isArrayEmpty)
    {
        isArrayEmpty = true;
        for(int i = 0; i < numberOfQueues; i++)
        {
            if(queueArray[i]->head != NULL )
            {
                isArrayEmpty = false;
                void* itemToEnqueue = IsraeliQueueDequeue(queueArray[i]);
                IsraeliQueueEnqueue(newQueue, itemToEnqueue);
            }
        }
    }
}



/**@param q_arr: a NULL-terminated array of IsraeliQueues
 * @param ComparisonFunction: a comparison function for the merged queue
 *
 * Merges all queues in q_arr into a single new queue, with parameters the parameters described
 * in the exercise. Each queue in q_arr enqueues its head in the merged queue, then lets the next
 * one enqueue an item, in the order defined by q_arr. In the event of any error during execution, return NULL.*/
 //Change compare_function
IsraeliQueue IsraeliQueueMerge(IsraeliQueue* queueArray, ComparisonFunction compare_function){
    if (queueArray == NULL || compare_function == NULL)
    { // According to question @210
        return NULL;
    }
    int numberOfQueues = countQueues(queueArray);
    int numberOfFunctions = countAllFunctions(queueArray, numberOfQueues);
    FriendshipFunction* newFriendshipArray = (FriendshipFunction*)malloc(sizeof(FriendshipFunction)*(numberOfFunctions + 1));
    if(newFriendshipArray == NULL)
    {
        return NULL;
    }
    initializeFriendshipArray(newFriendshipArray, queueArray);
    int averageFriendshipThreshold = getAverageFriendshipThreshold(queueArray, numberOfQueues);
    int newRivalryThreshold = getNewRivalryThreshold(queueArray, numberOfQueues);
    IsraeliQueue newQueue = IsraeliQueueCreate(newFriendshipArray,
                                               compare_function,
                                               averageFriendshipThreshold,
                                               newRivalryThreshold);
    if (newQueue == NULL)
    {
        return NULL;
    }
    if(numberOfQueues == 0)
    {
        return newQueue;
    }
    mergeQueues(newQueue, queueArray, numberOfQueues);
    return newQueue;
}

void addFirstNode(IsraeliQueue queue, Node* node)
{
    assert(queue != NULL && node != NULL);
    nodeSetNext(node, NULL);
    nodeSetPrevious(node, NULL);
    queue->head = node;
}

void cloneAllNodes(IsraeliQueue original, IsraeliQueue clonedQueue)
{
    assert(original != NULL && clonedQueue != NULL);
    Node* originalCurrentNode = original->head;
    bool firstNode = true;
    while(originalCurrentNode != NULL)
    {
        if (firstNode)
        {
            Node* clonedNode = cloneNode(originalCurrentNode);
            addFirstNode(clonedQueue, clonedNode);
            firstNode = false;
        }
        else
        {
            Node* clonedNode = cloneNode(originalCurrentNode);
            addToEnd(clonedQueue, clonedNode);
        }
        originalCurrentNode = nodeGetNext(originalCurrentNode);
    }
}

FriendshipFunction* cloneFriendshipFunctions(FriendshipFunction* original)
{
    int numberOfFunctions = countFunction(original);
    FriendshipFunction* newArray = (FriendshipFunction*) malloc(sizeof(FriendshipFunction) *  (numberOfFunctions + 1));
    if (newArray == NULL)
    {
        return NULL;
    }
    int i;
    for (i = 0; original[i] != NULL; i++)
    {
        newArray[i] = original[i];
    }
    newArray[i] = original[i];
    return newArray;
}

/**Returns a new queue with the same elements as the parameter. If the parameter is NULL,
 * NULL is returned.*/
IsraeliQueue IsraeliQueueClone(IsraeliQueue queue){
    if (queue == NULL){
        return NULL;
    }
    FriendshipFunction* clonedFriendshipFunctions = cloneFriendshipFunctions(queue->friendshipFunctions);
    if (clonedFriendshipFunctions == NULL)
    {
        return NULL;
    }
    ComparisonFunction clonedComparisonFunction = queue->comparisonFunction;
    IsraeliQueue clonedQueue =  IsraeliQueueCreate(clonedFriendshipFunctions,
                                                   clonedComparisonFunction,
                                                   queue->friendshipThreshold,
                                                   queue->rivalryThreshold);
    cloneAllNodes(queue, clonedQueue);
    return clonedQueue;
}

/**@param IsraeliQueue: an IsraeliQueue created by IsraeliQueueCreate
 *
 * Deallocates all memory allocated by IsraeliQueueCreate for the object pointed to by
 * the parameter.*/
void IsraeliQueueDestroy(IsraeliQueue queue)
{
    if (queue == NULL)
    {
        return;
    }
    Node* current = queue->head;
    while (current != NULL)
    {
        Node* next = nodeGetNext(current);
        nodeDestroy(current);
        current = next;
    }
    free(queue->friendshipFunctions);
    // According to question @273 we can't assume that "friendshipFunctions" was malloced,
    // therefore we used malloc to copy it and to clone it, then we always need to free() it.
    free(queue);
}