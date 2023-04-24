#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "IsraeliQueue.h"
#include "Node.h"


typedef struct IsraeliQueue_t {
    FriendshipFunction* friendshipFunctions;
    ComparisonFunction comparisonFunction;
    Node* head; // Node should contain: Person* person, Node* previous, Node* next.
    int friendshipThreshold;
    int rivalryThreshold;
} IsraeliQueue_t;

/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunctions, ComparisonFunction comparisonFunction,
                                int friendship_th, int rivalry_th){
    IsraeliQueue newQueue = (IsraeliQueue)malloc(sizeof(IsraeliQueue_t));
    if (newQueue == NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    newQueue -> friendshipFunctions = friendshipFunctions;
    newQueue -> comparisonFunction = comparisonFunction;
    newQueue -> head = NULL;
    newQueue -> friendshipThreshold = friendship_th;
    newQueue -> rivalryThreshold = rivalry_th;
    return newQueue;
}

/**Returns a new queue with the same elements as the parameter. If the parameter is NULL,
 * NULL is returned.*/
IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    clonedFriendshipFunctions = COPY_friendshipFunctions(); // Need to write
    clonedComparisonFunction = COPY_comparisonFunction();    // Need to write

    IsraeliQueue clonedQueue =  IsraeliQueueCreate(clonedFriendshipFunctions,
                                                   clonedComparisonFunction,
                                                   q->friendshipThreshold, q->rivalryThreshold);
    CLONE_ALL_NODES(q, clonedQueue); // Need to write
    return clonedQueue;
}

/**@param IsraeliQueue: an IsraeliQueue to which the function is to be added
 * @param FriendshipFunction: a FriendshipFunction to be recognized by the IsraeliQueue
 * going forward.
 *
 * Makes the IsraeliQueue provided recognize the FriendshipFunction provided.*/
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friendships_function){
    int functionsCounter = countFunction(q->friendshipFunctions);
    FriendshipFunction* newArray = realloc(q->friendshipFunctions,
                                           sizeof(FriendshipFunction) * (functionsCounter + 1));
    // Using realloc - Need to check that the data isn't lost
    if (newArray == NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    *(newArray + functionsCounter - 2) = friendships_function; // Accessing the one before last value in the array
    *(newArray + functionsCounter - 1) = NULL; // Accessing the last value in the array
    return ISRAELIQUEUE_SUCCESS;
}

/**Returns the number of elements of the given queue. If the parameter is NULL, 0
 * is returned.*/
int IsraeliQueueSize(IsraeliQueue q){
    int counter = 0;
    Node* current = q->head;
    while (current != NULL){
        counter++;
        current = q->next->head;
    }
    return counter;
}

/**@param item: an object comparable to the objects in the IsraeliQueue
 *
 * Returns whether the queue contains an element equal to item. If either
 * parameter is NULL, false is returned.*/
bool IsraeliQueueContains(IsraeliQueue q, void* item){
    Node* current = q->head;
    ComparisonFunction compare = q->comparisonFunction;
    while (current != NULL){
        if (compare(current, item)) {   // question @149 on piazza states that
                                        // compare will return 1 if identical and 0 if different
            return true;
        }
        current = q->next->head;
    }
    return false;
}

/**Removes and returns the foremost element of the provided queue. If the parameter
 * is NULL or a pointer to an empty queue, NULL is returned.*/
void* IsraeliQueueDequeue(IsraeliQueue q){
    if (q->head == NULL || q == NULL){
        return NULL;
    }
    void* first = q->head->next;
    removeFirstNode(q); // This function NEEDS to be declared in "Node.h"
    return first;
}

/**@param IsraeliQueue: an IsraeliQueue whose friendship threshold is to be modified
 * @param friendship_threshold: a new friendship threshold for the IsraeliQueue*/
IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int n_thresh){
    if(q == NULL){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->friendshipThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

/**@param IsraeliQueue: an IsraeliQueue whose rivalry threshold is to be modified
 * @param friendship_threshold: a new rivalry threshold for the IsraeliQueue*/
IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int n_thresh){
    if(q == NULL){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->rivalryThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

/**@param IsraeliQueue: an IsraeliQueue created by IsraeliQueueCreate
 *
 * Deallocates all memory allocated by IsraeliQueueCreate for the object pointed to by
 * the parameter.*/
void IsraeliQueueDestroy(IsraeliQueue q){ // This function NEEDS to be reviewed!
    Node* current = q->head;
    while (current != NULL){
        Node* next = q->head->next;
        free(current);
        current = next;
    }
    free(q->friendshipFunctions);
    free(q->comparisonFunction);
    free(q);
}
