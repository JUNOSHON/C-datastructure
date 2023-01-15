#include <stdio.h>
#include <stdlib.h>

typedef struct BinTreeNodeType
{
    char data;

    struct BinTreeNodeType *pLeftChild;
    struct BinTreeNodeType *pRightChild;
} BinTreeNode;

typedef struct BinTreeType
{
    struct BinTreeNodeType *pRootNode;

} BinTree;

BinTreeNode *makeNewNodeBT(char data)
{
    BinTreeNode *pReturn = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    if (pReturn != NULL)
    {
        pReturn->data = data;
        pReturn->pLeftChild = NULL;
        pReturn->pRightChild = NULL;
    }
    return pReturn;
}

BinTree *makeBinTree(char rootNodeData)
{
    BinTree *pReturn = NULL;
    pReturn = (BinTree *)malloc(sizeof(BinTree));

    if (pReturn != NULL)
    {
        pReturn->pRootNode = makeNewNodeBT(rootNodeData);
        if (pReturn->pRootNode == NULL)
        {
            free(pReturn);
            pReturn = NULL;
            printf("오류,메모리할당");
        }
    }
    else
    {
        printf("오류");
    }
    return pReturn;
}
BinTreeNode *addLeftChildNodeBT(BinTreeNode *pParentNode, char data)
{
    BinTreeNode *pReturn = NULL;
    if (pParentNode != NULL)
    {
        if (pParentNode->pLeftChild == NULL)
        {
            pParentNode->pLeftChild = makeNewNodeBT(data);
        }
        else
        {
            printf("노드가 이미 존재");
        }
    }
    return pReturn;
}

BinTreeNode *addRightChildNodeBT(BinTreeNode *pParentNode, char data)
{
    BinTreeNode *pReturn = NULL;
    if (pParentNode != NULL)
    {
        if (pParentNode->pRightChild == NULL)
        {
            pParentNode->pRightChild = makeNewNodeBT(data);
        }
        else
        {
            printf("노드가 이미 존재");
        }
    }
    return pReturn;
}

BinTreeNode *getRootNodeBT(BinTree *pBinTree)
{
    BinTreeNode *pReturn = NULL;

    if (pBinTree != NULL)
    {
        pReturn = pBinTree->pRootNode;
    }
    return pReturn;
}

void deleteBinTreeNode(BinTreeNode *pNode)
{
    if (pNode != NULL)
    {
        deleteBinTreeNode(pNode->pLeftChild);
        deleteBinTreeNode(pNode->pRightChild);
        free(pNode);
    }
}
void deleteBinTree(BinTree *pBinTree)
{
    if (pBinTree != NULL)
    {
        deleteBinTreeNode(pBinTree->pRootNode);
        free(pBinTree);
    }
}
void preorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode)
{
    if (pRootNode != NULL)
    {
        printf("%c ", pRootNode->data);                            // 현재 노드 방문
        preorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);  // 왼쪽 서브트리로 이동
        preorderTraversalRecursiveBinTreeNode(pNode->pRightChild); // 오른쪽 서브트리로 이동
    }
}
void preorderTraversalRecursiveBinTree(BinTree *pBinTree)
{
    if (pBinTree != NULL)
    {
        preorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}

void inorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode)
{
    if (pNode != NULL)
    {
        inorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);
        printf("%c ", pRootNode->data);
        inorderTraversalRecursiveBinTreeNode(pNode->pRightChild);
    }
}
void inorderTraversalRecursiveBinTree(BinTree *pBinTree)
{
    if (pBinTree != NULL)
    {
        inorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}

void postorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode)
{
    if (pNode != NULL)
    {
        postorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);
        postorderTraversalRecursiveBinTreeNode(pNode->pRightChild);
        printf("%c ", pRootNode->data);
    }
}
void postorderTraversalRecursiveBinTree(BinTree *pBinTree)
{
    if (pBinTree != NULL)
    {
        postorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{

    BinTree *pBinTree = NULL;
    BinTreeNode *pNodeA = NULL, *pNodeB = NULL, *pNodeC = NULL;
    BinTreeNode *pNodeD = NULL, *pNodeE = NULL, *pNodeF = NULL;

    pBinTree = makeBinTree('A');
    if (pBinTree != NULL)
    {
        pNodeA = getRootNodeBT(pBinTree);
        pNodeB = addLeftChildNodeBT(pNodeA, 'B');
        pNodeC = addRightChildNodeBT(pNodeA, 'C');

        if (pNodeB != NULL)
        {
            pNodeD = addLeftChildNodeBT(pNodeB, 'D');
        }
        if (pNodeC != NULL)
        {
            pNodeE = addLeftChildNodeBT(pNodeC, 'E');
            pNodeF = addRightChildNodeBT(pNodeC, 'F');
        }
    }
    if (pBinTree != NULL)
    {
        printf("전위 순회 결과 : ");
        preorderTraversalRecursiveBinTree(pBinTree);
        printf("중위 순회 결과 : ");
        inorderTraversalRecursiveBinTree(pBinTree);
        printf("후위 순회 결과 : ");
        postorderTraversalRecursiveBinTree(pBinTree);

        deleteBinTree(pBinTree);
    }
    return 0;
}