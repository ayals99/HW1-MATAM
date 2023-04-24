#include <stdio.h>
#include <stdlib.h>

#ifndef ISRAELIQUEUE.h
#include "IsraeliQueue.h"

typedef struct IsraeliQueue_t {
    FriendshipFunction* friendshipFunctions;
    ComparisonFunction comparisonFunction;
    void* head;
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

#endif