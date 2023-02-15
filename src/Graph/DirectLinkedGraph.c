#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType
{
  int data;
  struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType
{
  int currentCount;
  LinkedListNode headerNode;
} LinkedList;

LinkedList *createLinkedList()
{
  LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList));
  memset(pReturn, 0, sizeof(LinkedList)); // 할당된 메모리를 0으로 초기화
  return pReturn;
}

int getLinkedListData(LinkedList *pList, int position)
{
  int i = 0;

  LinkedListNode *pCurrentNode = &(pList->headerNode);
  for (; i <= position; i++)
  {
    pCurrentNode = pCurrentNode->pLink;
  }

  return pCurrentNode->data;
}

int addLinkedListData(LinkedList *pList, int position, int data)
{
  int i = 0;

  if (pList->currentCount < position)
  {
    fprintf(stderr, "오류 발생 프로그램 종료");
    exit(1);
  }

  LinkedListNode *pNewNode = (LinkedListNode *)malloc(sizeof(LinkedList));
  pNewNode->data = data;

  LinkedListNode *preNode = &(pList->headerNode);

  for (; i < position; i++)
  {
    preNode = preNode->pLink;
  }

  pNewNode->pLink = preNode->pLink;
  preNode->pLink = pNewNode;
  pList->currentCount++;
  return 0;
}

int removeLinkedListData(LinkedList *pList, int position)
{

  int i = 0;
  LinkedListNode *preNode = &(pList->headerNode);
  LinkedListNode *delNode = NULL;

  for (; i < position; i++)
  {
    preNode = preNode->pLink;
  }

  delNode = preNode->pLink;
  preNode->pLink = delNode->pLink;
  free(delNode);
  pList->currentCount--;
  return 0;
}

void deleteLinkedList(LinkedList *pList)
{
  LinkedListNode *pDelNode;
  LinkedListNode *pPreNode = pList->headerNode.pLink; // 헤더 노드가 가리키는 노드 주소
  while (pPreNode != NULL)
  {
    pDelNode = pPreNode;
    pPreNode = pPreNode->pLink;

    free(pDelNode);
  }

  free(pList); // 연결리스트 자체 메모리 해제
}

int getLinkedListLength(LinkedList *pList)
{
  if (pList != NULL)
  {
    return pList->currentCount;
  }
  return 0;
}

void displayList(LinkedList *pList)
{
  for (int i = 0; i < pList->currentCount; i++)
  {
    printf("[%d], %d\n", i, getLinkedListData(pList, i));
  }
}

void iterateLinkedList(LinkedList *pList)
{
  int count = 0;
  LinkedListNode *pNode = pList->headerNode.pLink;

  while (pNode != NULL)
  {
    printf("[%d], %d\n", count++, pNode->data);
    pNode = pNode->pLink;
  }
  printf("노드 개수 : %d\n", count);
}

int getListLength(LinkedList *pList)
{
  int length = pList->currentCount;
  return length;

  int i = 0, count = -1;
  LinkedListNode *pCountList = &(pList->headerNode);

  for (; pCountList != NULL; i++)
  {
    pCountList = pCountList->pLink;
    count++;
  }
  return count;
}

typedef struct DirectLinkedGrapthType
{
  int nodeCount;
  LinkedList **ppAdjEdge;
} DirectLinkedGraph;

DirectLinkedGraph *createDirectLinkedGraph(int nodeCount)
{
  int i = 0;
  DirectLinkedGraph *pReturn = NULL;

  if (nodeCount > 0)
  {
    pReturn = (DirectLinkedGraph *)malloc(sizeof(DirectLinkedGraph));
    if (pReturn == NULL)
    {
      printf("오류,in createDirectLinkedGraph()\n");
      return NULL;
    }
    pReturn->nodeCount = nodeCount;
  }
  else
  {
    printf("오류 최대 노드 개수는 0보다 커야함\n");
    return NULL;
  }
  pReturn->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList *) * nodeCount);
  if (pReturn->ppAdjEdge == NULL)
  {
    printf("오류, 메모리 할당,in createLinkedGrapth()\n");
    if (pReturn != NULL)
    {
      free(pReturn);
    }
    return NULL;
  }
  for (i = 0; i < nodeCount; i++)
  {
    pReturn->ppAdjEdge[i] = createLinkedList();
    if (pReturn->ppAdjEdge[i] == NULL)
    {
      printf("오류,메모리할당\n");
      if (pReturn->ppAdjEdge != NULL)
        free(pReturn->ppAdjEdge);

      if (pReturn != NULL)
        free(pReturn);

      return NULL;
    }
  }
  return pReturn;
}

int checkVertexValid(DirectLinkedGraph *pGraph, int node)
{
  if (pGraph != NULL && node >= 0 && node < pGraph->nodeCount)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int addEdgeDLG(DirectLinkedGraph *pGraph, int fromNode, int toNode)
{
  int ret = 0;

  if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
  {
    addLinkedListData(pGraph->ppAdjEdge[fromNode], 0, toNode);
  }
  else
  {
    ret = -1;
  }
  return ret;
}
int removeEdgeDLG(DirectLinkedGraph *pGraph, int fromNode, int toNode)
{
  int ret = -1;
  LinkedList *pList = NULL;
  int i = 0, count = 0;

  if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
  {
    pList = pGraph->ppAdjEdge[fromNode];
    count = getLinkedListLength(pList);
    for (i = 0; i < count; i++)
    {
      if (getLinkedListLength(pList) == toNode)
      {
        removeLinkedListData(pList, i);
        ret = 0;
        break;
      }
    }
  }
  else
  {
    ret = -1;
  }
  return ret;
}
int getEdgeDLG(DirectLinkedGraph *pGraph, int fromNode, int toNode)
{
  int ret = 0;
  LinkedList *pList = NULL;
  int i = 0, count = 0;

  if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
  {
    pList = pGraph->ppAdjEdge[fromNode];
    count = getLinkedListLength(pList);
    for (i = 0; i < count; i++)
    {
      if (getLinkedListData(pList, i) == toNode)
      {
        ret = 1;
        break;
      }
    }
  }
  return ret;
}
void displayGraphDLG(DirectLinkedGraph *pGraph)
{
  int i = 0, j = 0, count = 0;
  if (pGraph != NULL)
  {
    count = pGraph->nodeCount;
    for (i = 0; i < count; i++)
    {
      for (j = 0; j < count; j++)
      {
        if (getEdgeDLG(pGraph, i, j))
        {
          printf("1 ");
        }
        else
        {
          printf("0 ");
        }

        printf("\n");
      }
    }
  }
}

void deleteGraphDLG(DirectLinkedGraph *pGraph)
{
  int i = 0;

  if (pGraph != NULL)
  {
    for (i = 0; i < pGraph->nodeCount; i++)
    {
      deleteLinkedList(pGraph->ppAdjEdge[i]);
    }
    if (pGraph->ppAdjEdge != NULL)
      free(pGraph->ppAdjEdge);
    free(pGraph);
  }
}
int main(int argc, char *argv[])
{
  int nodeCount = 6;
  DirectLinkedGraph *pG2 = createDirectLinkedGraph(nodeCount);
  if (pG2 != NULL)
  {
    addEdgeDLG(pG2, 0, 1);
    addEdgeDLG(pG2, 1, 2);
    addEdgeDLG(pG2, 2, 0);
    addEdgeDLG(pG2, 2, 3);
    addEdgeDLG(pG2, 3, 2);
    addEdgeDLG(pG2, 4, 5);
    addEdgeDLG(pG2, 5, 3);

    printf("G2: 방향 그래프\n");
    displayGraphDLG(pG2);

    deleteGraphDLG(pG2);
  }
  return 0;
}