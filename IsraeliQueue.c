#include <stdio.h>
#include <stdlib.h>

#ifndef ISRAELIQUEUE_H
#include "IsraeliQueue.h"
#include "Node.h"

typedef struct IsraeliQueue_t {
    FriendshipFunction* friendshipFunctions;
    ComparisonFunction comparisonFunction;
    Node* head; // Node contains: Person* person, Node* previous, Node* next.
    int friendshipThreshold;
    int rivalryThreshold;
} IsraeliQueue_t;

/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunctions, ComparisonFunction comparisonFunction,
                                int friendship_th, int rivalry_th){
    IsraeliQueue newQueue = (IsraeliQueue) malloc(sizeof(IsraeliQueue_t));
    if (!newQueue){
        return NULL;
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

    clonedFriendshipFiunctions = COPY_friendshipFunctions(); // Need to write
    clonedComparisonFunction = COPY_comparisonFunction();    // Need to write

    IsraeliQueue clonedQueue =  IsraeliQueueCreate(friendshipFunctions,
                                                   comparisonFunction,
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
    int amountOfFunctions = countFunction(q->friendshipFunctions);
    FriendshipFunction* newArray = realloc(q->friendshipFunctions, sizeof(FriendshipFunction) * (amountOfFunctions + 1));
    if (newArray == NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    
}
/*
 * We'll want to use realloc in order to add 1 function to the array
 * */

#endif