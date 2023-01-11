#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LinkedQueueNodeType
{
    char data;
    struct LinkedQueueNodeType *pLink;
} LinkedQueueNode;

typedef struct LinkedQueueType
{

    int currentCount;
    struct LinkedQueueNodeType *pFront;
    struct LinkedQueueNodeType *pRear;
} LinkedQueue;

LinkedQueue *createLinkedQueue()
{

    LinkedQueue *pReturn = NULL;

    pReturn = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    memset(pReturn, 0, sizeof(LinkedQueue));

    return pReturn;
}

int isLinkedQueueEmpty(LinkedQueue *pQueue)
{
    int ret = 0;

    if (pQueue != NULL)
    {
        if (pQueue->currentCount == 0)
        {
            ret = 1;
        }
    }
    return ret;
}

int enqueueLQ(LinkedQueue *pQueue, char data)
{
    int ret = 0;
    LinkedQueueNode *pNode = NULL;

    pNode = (LinkedQueueNode *)malloc(sizeof(LinkedQueueNode));
    pNode->data = data;
    pNode->pLink = NULL;

    if (isLinkedQueueEmpty(pQueue) == 0)
    {
        pQueue->pRear->pLink = pNode;
        pQueue->pRear = pNode;
    }
    else
    {
        pQueue->pFront = pNode;
        pQueue->pRear = pNode;
    }
    pQueue->currentCount++;
    ret = 1;

    return ret;
}
LinkedQueueNode *peekLQ(LinkedQueue *pQueue)
{
    LinkedQueueNode *pReturn = NULL;
    if (pQueue != NULL)
    {
        if (isLinkedQueueEmpty(pQueue) == 0)
        {
            pReturn = pQueue->pFront;
        }
    }
    return pReturn;
}
LinkedQueueNode *dequeueLQ(LinkedQueue *pQueue)
{
    LinkedQueueNode *pReturn = NULL;
    if (isLinkedQueueEmpty(pQueue) == 0)
    {
        pReturn = pQueue->pFront;
        pQueue->pFront = pQueue->pFront->pLink;
        pReturn->pLink = NULL;

        pQueue->currentCount--;
    }
    if (isLinkedQueueEmpty(pQueue) == 1)
    {
        pQueue->pRear = NULL;
    }
    return pReturn;
}

void deleteLinkedQueue(LinkedQueue *pQueue)
{
    LinkedQueueNode *pNode = NULL;
    LinkedQueueNode *pDelNode = NULL;

    if (pQueue != NULL)
    {
        pNode = pQueue->pFront;
        while (pNode != NULL)
        {
            pDelNode = pNode;
            pNode = pNode->pLink;
            free(pDelNode);
        }
        free(pDelNode);
    }
    free(pQueue);
}

void displayLinkedqueue(LinkedQueue *pQueue)
{
    LinkedQueueNode *pNode = NULL;
    int i = 0;
    if (pQueue != NULL)
    {
        printf("현재 노드 개수 : %d\n", pQueue->currentCount);
        pNode = pQueue->pFront;
        while (pNode != NULL)
        {
            printf("[%d] - [%c]\n", i, pNode->data);
            i++;
            pNode = pNode->pLink;
        }
    }
}

int main(int argc, char *argv[])
{
    LinkedQueue *pQueue = NULL;
    LinkedQueueNode *pNode = NULL;

    pQueue = createLinkedQueue();
    if (pQueue != NULL)
    {
        enqueueLQ(pQueue, 'A');
        enqueueLQ(pQueue, 'B');
        enqueueLQ(pQueue, 'C');
        enqueueLQ(pQueue, 'D');
        displayLinkedqueue(pQueue);

        pNode = dequeueLQ(pQueue);
        if (pNode != NULL)
        {
            printf("Dequeue Value - [%c]\n", pNode->data);
            free(pNode);
        }
        displayLinkedqueue(pQueue);

        pNode = peekLQ(pQueue);
        if (pNode != NULL)
        {
            printf("Peek Value - [%c]\n", pNode->data);
        }
        displayLinkedqueue(pQueue);

        enqueueLQ(pQueue, 'E');

        displayLinkedqueue(pQueue);
    }
    return 0;
}