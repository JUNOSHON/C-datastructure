#include<stdio.h>
#include<stdlib.h>

typedef struct LinkedQueueNodeType {
    char data;
    struct LinkedQueueNodeType* plink;
}LinkedQueueNodeType;

typedef struct LinkedQueueType {

    int currentCount;
    LinkedQueueNodeType* pFront;
    LinkedQueueNodeType* pRear;
}LinkedQueue;

int isLinkedQueueEmpty(LinkedQueue* pQueue);

LinkedQueue* createLinkedQueue(int size){
    
    LinkedQueue *pReturn = NULL;

    pReturn = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    memset(pReturn, 0, sizeof(LinkedQueue));
    

    
    return pReturn;
}
