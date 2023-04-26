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
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    newQueue -> friendshipFunctions = friendshipFunctions;
    newQueue -> comparisonFunction = comparisonFunction;
    newQueue -> head = NULL;
    newQueue -> friendshipThreshold = friendship_th;
    newQueue -> rivalryThreshold = rivalry_th;
    return newQueue;
}

/**@param IsraeliQueue: an IsraeliQueue in which to insert the item.
 * @param item: an item to enqueue
 *
 * Places the item in the foremost position accessible to it.*/
IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void * item){

}


int countFunction(FriendshipFunction* array){
    int counter = 0;
    FriendshipFunction* pointer = array;
    while (pointer != NULL){ // It's a given that the function array ends with NULL
        pointer++;
    }
        return counter;
}

/**@param IsraeliQueue: an IsraeliQueue to which the function is to be added
 * @param FriendshipFunction: a FriendshipFunction to be recognized by the IsraeliQueue
 * going forward.
 *
 * Makes the IsraeliQueue provided recognize the FriendshipFunction provided.*/
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friendships_function){
    if (q == NULL || friendships_function == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }

    int functionsCounter = countFunction(q->friendshipFunctions);
    FriendshipFunction* newArray = realloc(q->friendshipFunctions,
                                           sizeof(FriendshipFunction) * (functionsCounter + 2));
    // Note to self: multiplying by "functionsCounter + 2" because we didn't count the NULL at the end of the array

    // Need to check that the data isn't lost when using realloc
    if (newArray == NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }

    // NEED to check that we don't access memory that's not allowed:
    *(newArray + functionsCounter) = friendships_function; // The value in this place was NULL
    //Assigning new function to the one before last space of array
    *(newArray + functionsCounter + 1) = NULL; // Array needs to end with NULL
    // Accessing the last value in the array
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
int IsraeliQueueSize(IsraeliQueue q){
    if(q == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int counter = 0;
    Node* current = q->head;
    while (current != NULL){
        counter++;
        current = q->next->head;
    }
    return counter;
}

/**Removes and returns the foremost element of the provided queue. If the parameter
 * is NULL or a pointer to an empty queue, NULL is returned.*/
void* IsraeliQueueDequeue(IsraeliQueue q){
    if (q == NULL || q->head == NULL){
        return NULL;
    }
    void* first = q->head->next;
    removeFirstNode(q); // This function NEEDS to be declared in "Node.h"
    return first;
}

/**@param item: an object comparable to the objects in the IsraeliQueue
 *
 * Returns whether the queue contains an element equal to item. If either
 * parameter is NULL, false is returned.*/
bool IsraeliQueueContains(IsraeliQueue q, void* item){
    if(q == NULL || q->head == NULL || item == NULL){
        return false;
    }
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

/**Advances each item in the queue to the foremost position accessible to it,
 * from the back of the queue frontwards.*/
IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue q){

}

/**@param q_arr: a NULL-terminated array of IsraeliQueues
 * @param ComparisonFunction: a comparison function for the merged queue
 *
 * Merges all queues in q_arr into a single new queue, with parameters the parameters described
 * in the exercise. Each queue in q_arr enqueues its head in the merged queue, then lets the next
 * one enqueue an item, in the order defined by q_arr. In the event of any error during execution, return NULL.*/
IsraeliQueue IsraeliQueueMerge(IsraeliQueue* q, ComparisonFunction compare_function){

}

void cloneAllNodes(IsraeliQueue original,IsraeliQueue cloned){
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
IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    if (q == NULL){
        abort(); // For debugging. TO BE REMOVED BEFORE COMPILING
        return ISRAELIQUEUE_BAD_PARAM;
    }

    clonedFriendshipFunctions = cloneFriendshipFunctions(q->);
    ComparisonFunction clonedComparisonFunction = (ComparisonFunction)malloc(sizeof(ComparisonFunction) * 1);
    clonedComparisonFunction = q->comparisonFunction;

    IsraeliQueue clonedQueue =  IsraeliQueueCreate(clonedFriendshipFunctions,
                                                   clonedComparisonFunction,
                                                   q->friendshipThreshold, q->rivalryThreshold);
    cloneAllNodes(q, clonedQueue); // Need to write
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
        free(current);
        current = NULL;
        current = next;
    }
    free(q->friendshipFunctions);
    q->friendshipFunctions = NULL;
    free(q->comparisonFunction);
    q->comparisonFunction = NULL;
    free(q);
    q = NULL; // assigning NULL in order to ensure that we don't use this pointer again
}
