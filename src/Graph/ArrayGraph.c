#define ARRAY_GRAPH_TYPE_DIRECT 0
#define ARRAY_GRAPH_TYPE_UNDIRECT 1
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
typedef struct ArrayGraphType
{
  int graphType;
  int nodeCount;
  int **ppEdge;
} ArrayGraph;

ArrayGraph *createArrayGraph(int graphType, int nodeCount)
{
  int i = 0;
  ArrayGraph *pReturn = NULL;

  pReturn = (ArrayGraph *)malloc(sizeof(ArrayGraph));

  if (pReturn == NULL)
  {
    return NULL;
  }
  pReturn->graphType = graphType;
  pReturn->nodeCount = nodeCount;
  pReturn->ppEdge = (int **)malloc(sizeof(int *) * nodeCount);
  if (pReturn->ppEdge == NULL)
  {
    return NULL;
  }
  for (i = 0; i < nodeCount; i++)
  {
    pReturn->ppEdge[i] = (int *)malloc(sizeof(int) * nodeCount);
    if (pReturn->ppEdge[i] == NULL)
    {
      return NULL;
    }
    memset(pReturn->ppEdge[i], 0, sizeof(int) * nodeCount);
  }
  return pReturn;
}

int checkVertexValid(ArrayGraph *pGraph, int node)
{
  if (pGraph != NULL && node < pGraph->nodeCount && node >= 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
int addEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode)
{
  int ret = 0;

  if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
  {
    pGraph->ppEdge[fromNode][toNode] = 1;
  }
  else
  {
    ret = -1;
  }
  return ret;
}
int addEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode)
{
  int ret = 0;

  ret = addEdgeInternalAG(pGraph, fromNode, toNode);
  if (0 == ret && ARRAY_GRAPH_TYPE_UNDIRECT == pGraph->graphType)
  {
    ret = addEdgeInternalAG(pGraph, toNode, fromNode);
  }
  return ret;
}

int removeEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode)
{
  int ret = 0;

  if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
  {
    pGraph->ppEdge[fromNode][toNode] = 0;
  }
  else
  {
    ret = -1;
  }
  return ret;
}

int removeEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode)
{
  int ret = 0;

  ret = removeEdgeInternalAG(pGraph, fromNode, toNode);
  if (0 == ret && ARRAY_GRAPH_TYPE_UNDIRECT == pGraph->graphType)
  {
    ret = removeEdgeInternalAG(pGraph, toNode, fromNode);
  }

  return ret;
}
int getEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode)
{
  int ret = 0;

  if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
  {
    ret = pGraph->ppEdge[fromNode][toNode];
  }
  return ret;
}
void deleteGraphAG(ArrayGraph *pGraph)
{
  int i = 0;

  if (pGraph != NULL)
  {
    for (i = 0; i < pGraph->nodeCount; i++)
    {
      free(pGraph->ppEdge[i]);
    }
    free(pGraph->ppEdge);
    free(pGraph);
  }
}
void traversalDFS(ArrayGraph *pGraph, int startNodeID, int *pVisit)
{
  int i = 0;

  pVisit[startNodeID] = 1;
  printf("노드-[%d] 방문\n", startNodeID);
  for (i = 0; i < pGraph->nodeCount; i++)
  {
    if (i != startNodeID)
    {
      if (0 != getEdgeAG(pGraph, startNodeID, i))
      {
        if (0 == pVisit[i])
        {
          traversalDFS(pGraph, i, pVisit);
        }
      }
    }
  }
}

void traversalBFS(ArrayGraph *pGraph, int startNodeID)
{
  int i = 0;
  int nodeID = 0;
  LinkedQueue *pQueue = NULL;
  LinkedQueueNode *pQueueNode = NULL;
  int *pVisit = NULL;

  if (pGraph == NULL)
  {
    return;
  }
  pQueue = createLinkedQueue();
  pVisit = malloc(sizeof(int) * pGraph->nodeCount);
  if (pQueue == NULL || pVisit == NULL)
  {
    return;
  }
  memset(pVisit, 00, sizeof(int) * pGraph->nodeCount);
  pVisit[startNodeID] = 1;
  enqueueLQ(pQueue, startNodeID);

  while (isLinkedQueueEmpty(pQueue) == 0)
  {
    pQueueNode = dequeueLQ(pQueue);
    if (pQueueNode != NULL)
    {
      nodeID = pQueueNode->data;
      printf("노드-[%d] 방문\n", nodeID);
      for (i = 0; i < pGraph->nodeCount; i++)
      {
        if (i != nodeID)
        {
          if (0 != getEdgeAG(pGraph, nodeID, i))
          {
            if (0 == pVisit[i])
            {
              pVisit[i] = 1;
              enqueueLQ(pQueue, i);
            }
          }
        }
      }
      free(pQueueNode);
    }
  }
  deleteLinkedQueue(pQueue);
  free(pVisit);
}

int main(int argc, char *argv[])
{
  int nodeCount = 4;
  ArrayGraph *pG1 = createArrayGraph(ARRAY_GRAPH_TYPE_UNDIRECT, nodeCount);
  int *pVisit = malloc(sizeof(int) * nodeCount);
  if (pG1 != NULL)
  {
    addEdgeAG(pG1, 0, 1);
    addEdgeAG(pG1, 0, 2);
    addEdgeAG(pG1, 1, 3);

    printf("G1: BFS\n");
    traversalBFS(pG1, 0);
    deleteGraphAG(pG1);
  }
  // {
  //   addEdgeAG(pG1, 0, 1);
  //   addEdgeAG(pG1, 0, 2);
  //   addEdgeAG(pG1, 1, 3);
  //   memset(pVisit, 0, sizeof(int) * nodeCount);
  //   printf("G1 : DFS\n");
  //   traversalDFS(pG1, 0, pVisit);
  //   deleteGraphAG(pG1);
  //   free(pVisit);
}
