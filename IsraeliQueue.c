#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include "IsraeliQueue.h"
#include "Node.h"

/** Struct declaration */

struct IsraeliQueue_t {
    FriendshipFunction* friendshipFunctions;
    ComparisonFunction comparisonFunction;
    Node* head; // Node should contain: Person* person, Node* previous, Node* next.
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





// TODO: Add "addToEnd" function and to think of other extreme cases.

/** Function Implementations */

int countFunction(FriendshipFunction* array){
    int counter = 0;
    FriendshipFunction* pointer = array;
    while (pointer != NULL){ // It's a given that the function array ends with NULL
        counter++;
        pointer++;
    }
    return counter;
}

FriendshipFunction* createFriendshipFunction(FriendshipFunction* friendshipFunctions){
    int numberOfFunctions = countFunction(friendshipFunctions);
    FriendshipFunction* friendshipArray = (FriendshipFunction*)malloc(sizeof(FriendshipFunction) * (numberOfFunctions + 1));
    for (int i = 0; i < numberOfFunctions + 1; i++){
        friendshipArray[i] = friendshipFunctions[i];
    }
    return friendshipArray;
}

/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunctions, ComparisonFunction comparisonFunction,
                                int friendship_th, int rivalry_th){
    if(friendshipFunctions == NULL)
    {
        return NULL;
    }
    IsraeliQueue newQueue = (IsraeliQueue)malloc(sizeof(*newQueue));
    if (newQueue == NULL)
    {
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return NULL;
    }
    //Why create a new array when we can allocate the ptr. -AYAL: because of the clone function.
    // FriendshipFunction* newFunctionsArray = createFriendshipFunction(friendshipFunctions); // Uses malloc - needs free()
    // if(newFunctionsArray == NULL){
    //      return ISRAELIQUEUE_ALLOC_FAILED;
    // }
    // Will probably be in IsraeliQueueDestroy.
    //We should check the return value.
    newQueue -> friendshipFunctions = friendshipFunctions;
    newQueue -> comparisonFunction = comparisonFunction;
    newQueue -> head = NULL;
    newQueue -> friendshipThreshold = friendship_th;
    newQueue -> rivalryThreshold = rivalry_th;
    return newQueue;
}

Relationship getRelationship(IsraeliQueue queue, Node* existing, Node* toAdd){
    int numberOfFunctions = countFunction(queue->friendshipFunctions);
    int friendShipThreshold = queue->friendshipThreshold;
    double average = 0;
    if (numberOfFunctions == 0)
    {
        return NEUTRAL;
    }
    FriendshipFunction* array = queue->friendshipFunctions;
    for (int i = 0; i < numberOfFunctions; i++)
    {
        int friendshipFunctionResult = (array[i])(nodeGetItem(existing),
                                                  nodeGetItem(toAdd));
        if(friendshipFunctionResult > friendShipThreshold &&
                                (nodeGetPassCount(existing) < FRIEND_QUOTA))
        {
            return FRIENDS;
        }
        average += friendshipFunctionResult;
    }
    // We only get here if "existing" and "toAdd" are not friends according to all functions in the array.
    average /= numberOfFunctions;
    average = ((int)average < average) ? (double)((int)average + 1) : average;
    if (average < friendShipThreshold && nodeGetBlockCount(existing) < RIVAL_QUOTA)
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
    Relationship relationshipStatus = getRelationship(queue, current, nodeToAdd); // Ayal: How do you know that "nodeToAdd" isn't NULL?
    while(relationshipStatus != FRIENDS && current != NULL)
    {
        current = nodeGetNext(current);
        relationshipStatus = getRelationship(queue, current, nodeToAdd);
    }
    if(current == NULL)
    {
        return NULL;
    }
    return current;
}

Node* findFoe(IsraeliQueue queue, Node* current, Node* nodeToAdd)
{
    Relationship relationshipStatus = getRelationship(queue, current, nodeToAdd);;
    while(relationshipStatus != FOES && current != NULL)
    {
        current = nodeGetNext(current);
        relationshipStatus = getRelationship(queue, current, nodeToAdd);
    }
    if(current == NULL)
    {
        return NULL;
    }
    return current;
}

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
    if(nodeToAdd == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    if(queue->friendshipFunctions == NULL)
    {
        //TODO: addToEnd(queue, nodeToAdd); Implement this better version for readability.
        return addNodeAfter(getLastElement(queue), nodeToAdd);
    }
    Node* potentialFriend = findFriend(queue, queue->head, nodeToAdd);
    Node* potentialFoe = NULL;
    while(potentialFriend != NULL)
    {
        potentialFoe = findFoe(queue, potentialFriend, nodeToAdd);
        if(potentialFoe == NULL)
        {
            if(addNodeAfter(potentialFriend, nodeToAdd) == ISRAELIQUEUE_SUCCESS)
            {
                addPassCount(potentialFriend);
                return ISRAELIQUEUE_SUCCESS;
            }
            return ISRAELIQUEUE_BAD_PARAM;
        }
        addBlockCount(potentialFoe);
        potentialFriend = findFriend(queue, nodeGetNext(potentialFoe), nodeToAdd);
    }
    //Adds to the end of the list in case of no friends or an enemy has blocked.

//    if(potentialFoe != NULL)
//    {
//        if(addNodeAfter(potentialFoe, nodeToAdd) == ISRAELIQUEUE_SUCCESS)
//        {
//            return ISRAELIQUEUE_SUCCESS;
//        }
//        return ISRAELIQUEUE_BAD_PARAM;
//    }
    return addNodeAfter(getLastElement(queue), nodeToAdd);
}



/**@param IsraeliQueue: an IsraeliQueue to which the function is to be added
 * @param FriendshipFunction: a FriendshipFunction to be recognized by the IsraeliQueue
 * going forward.
 *
 * Makes the IsraeliQueue provided recognize the FriendshipFunction provided.*/
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue queue, FriendshipFunction friendships_function){
    if (queue == NULL || friendships_function == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int functionsCounter = countFunction(queue->friendshipFunctions);
    FriendshipFunction* newArray = (FriendshipFunction*) realloc(queue->friendshipFunctions,
                                                                 sizeof(FriendshipFunction) * (functionsCounter + 2));
    // Note to self: multiplying by "functionsCounter + 2" because we didn't count the NULL at the end of the array
    if (newArray == NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    *(newArray + functionsCounter) = friendships_function; // The value in this place was NULL
    //Assigning new function to the one before last space of array
    *(newArray + functionsCounter + 1) = NULL; // Accessing the last value in the array so Array will end with NULL
    return ISRAELIQUEUE_SUCCESS;
}

/**@param IsraeliQueue: an IsraeliQueue whose friendship threshold is to be modified
 * @param friendship_threshold: a new friendship threshold for the IsraeliQueue*/
IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int n_thresh){
    if(q == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->friendshipThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

/**@param IsraeliQueue: an IsraeliQueue whose rivalry threshold is to be modified
 * @param friendship_threshold: a new rivalry threshold for the IsraeliQueue*/
IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int n_thresh){
    if(q == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->rivalryThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

/**Returns the number of elements of the given queue. If the parameter is NULL, 0
 * is returned.*/
int IsraeliQueueSize(IsraeliQueue queue){
    if(queue == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int counter = 0;
    Node* current = queue->head;
    while (current != NULL){
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
/*
bool hasFriend(Node* friendPlace){
    if (friendPlace != NULL){
        return true;
    }
    else {
        return false;
    }
}

//Needs to check this function
bool canMoveForwards(Node* friendPlace, Node* foePlace){
    return (hasFriend(friendPlace) || foePlace != NULL);
}

void executeMove(Node* friendPlace, Node* foePlace, Node* end, Node* currentNodeToMove){
    if(hasFriend(friendPlace)) {
        addPassCount(friendPlace); // This friends let "item" pass
        // According to @253, we only add a pass if he actually let him pass
        // So we don't add a passCount if the pass was blocked
        addNodeAfter(friendPlace, currentNodeToMove);
    }
        // If "item" was blocked it need to go behind the last enemy that's in the segment in which it was blocked.
    else if(friendPlace == NULL && foePlace != NULL){
        addNodeAfter(foePlace, currentNodeToMove);
    }
    else{
        insertBefore(currentNodeToMove, end);
    }
}

bool MovedForwards(IsraeliQueue queue, Node* currentNodeToMove){
    bool canAdvance = false;
    Node* friendPlace = NULL, *foePlace = NULL, *current = queue->head;
    Node* placement = findBetterPlacement(current, friendPlace, foePlace, currentNodeToMove);
    if ( canMoveForwards(friendPlace, foePlace) ) {
        canAdvance = true;
        removeNodeFromQueue(currentNodeToMove); // removes "previous" and "next"
        executeMove(friendPlace, foePlace, current, currentNodeToMove);
    }
    return canAdvance;
}

/**Advances each item in the queue to the foremost position accessible to it,
 * from the back of the queue frontwards.
IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue queue){
    bool canImprove = true;
    while(canImprove){
        Node * currentHead = queue->head;
        Node * currentNodeToMove = findLastElement(queue);
        bool noOneCanMove = true;
        while (currentNodeToMove != currentHead) { // NEED to take care of first node!
            noOneCanMove = !MovedForwards(queue, currentNodeToMove);
            currentNodeToMove = nodeGetPrevious(currentNodeToMove);
        }
        noOneCanMove = !MovedForwards(queue, currentNodeToMove); //"currentNodeToMove" points to "currentHead"
        if(noOneCanMove){
            canImprove = false;
        }
    }
}
*/

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
        //TODO addToEnd(queue)
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


/**Advances each item in the queue to the foremost position accessible to it,
 * from the back of the queue frontwards.
*/
IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue queue)
{
    if(queue == NULL)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    IsraeliQueue clonedQueue = IsraeliQueueClone(queue);
    if(clonedQueue == NULL)
    {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    for(Node* lastOriginalNode = getLastElement(queue); lastOriginalNode != NULL; lastOriginalNode = getLastElement(queue))
    {
        removeNode(queue, lastOriginalNode);
        Node* clonedOriginalNode = getClonedNode(clonedQueue, lastOriginalNode);
        removeNode(clonedQueue, clonedOriginalNode);
        IsraeliQueueEnqueue(clonedQueue, clonedOriginalNode);
        //nodeDestroy(lastOriginalNode);
    }
    IsraeliQueue tmp = queue;
    queue = clonedQueue;
    IsraeliQueueDestroy(tmp);
    return ISRAELIQUEUE_SUCCESS;
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
    IsraeliQueue newQueue = IsraeliQueueCreate(newFriendshipArray,compare_function,
                                               averageFriendshipThreshold, newRivalryThreshold);
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

void cloneAllNodes(IsraeliQueue original, IsraeliQueue cloned){
    if (original == NULL){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    Node* current = original->head;
    while(current != NULL){
        copyNodeToStart(current, cloned); // NEEDS to be implemented in "Node.c"
        current = current->next;
    }
}

FriendshipFunction* cloneFriendshipFunctions(FriendshipFunction* original){
    int numberOfFunctions = countFunction(original);
    FriendshipFunction* newArray = (FriendshipFunction*) malloc(sizeof(FriendshipFunction) *  (numberOfFunctions + 1));
    for (int i = 0; i < (numberOfFunctions + 1); i++){
        newArray[i] = original[i]
    }
    return newArray;
}

/**Returns a new queue with the same elements as the parameter. If the parameter is NULL,
 * NULL is returned.*/
IsraeliQueue IsraeliQueueClone(IsraeliQueue queue){
    if (queue == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }

    FriendshipFunction* clonedFriendshipFunctions = cloneFriendshipFunctions(queue->friendshipFunctions);
    ComparisonFunction* clonedComparisonFunction = (ComparisonFunction*)malloc(sizeof(ComparisonFunction) * 1);
    clonedComparisonFunction = q->comparisonFunction;

    IsraeliQueue clonedQueue =  IsraeliQueueCreate(clonedFriendshipFunctions,
                                                   *clonedComparisonFunction,
                                                   q->friendshipThreshold, q->rivalryThreshold);
    cloneAllNodes(q, clonedQueue);
    return clonedQueue;
}

/**@param IsraeliQueue: an IsraeliQueue created by IsraeliQueueCreate
 *
 * Deallocates all memory allocated by IsraeliQueueCreate for the object pointed to by
 * the parameter.*/
void IsraeliQueueDestroy(IsraeliQueue q){ // This function NEEDS to be reviewed!
    if (q == NULL){
        return; // To check that we're not given a NULL pointer, since we can't free() a NULL pointer.
    }
    Node* current = q->head;
    while (current != NULL){ // So we don't try and apply free on a NULL pointer
        Node* next = q->head->next;
        free(current); // NEED to check in "node.h" that we don't use any other dynamic memory allocations
        current = NULL;
        current = next;
    }
    free(q->friendshipFunctions);
    // (According to question @273 we can't assume that "friendshipFunctions" was malloced,
    // therefore we used malloc to copy it and to clone it and then we always need to free() it.
    q->friendshipFunctions = NULL;
    free(q->comparisonFunction);
    // We free() "comparisonFunction" because if we want to clone it we have to malloc and therefore we always malloc it
    q->comparisonFunction = NULL;
    free(q);
    q = NULL; // assigning NULL in order to ensure that we don't use this pointer again
}