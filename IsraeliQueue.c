#include <stdio.h>

#ifndef ISRAELIQUEUE.h
#include "IsraeliQueue.h"

/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunctions, ComparisonFunction comparisonFunction,
                                int friendship_th, int rivalry_th){
    IsraeliQueue* newQueue;
    newQueue->friendshipFunctions = friendshipFunctions;


    return newQueue;
}

#endif