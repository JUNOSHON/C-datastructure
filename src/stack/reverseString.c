#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct LinkedStackNodeType {
    char data;
    struct LinkedStackNodeType* pLink;
}LinkedStackNode;

typedef struct LinkedStackType {
    int currentCount;
    LinkedStackNode* pTop;
}LinkedStack;

LinkedStack* createLinkedStack() {
    LinkedStack *pReturn = NULL;
    pReturn = (LinkedStack *)malloc(sizeof(LinkedStack));
    memset(pReturn, 0, sizeof(LinkedStack));
    return pReturn;
}
int pushLS(LinkedStack* pStack, char data) {
    int ret= 0;
    LinkedStackNode *pNode = NULL;

    if(pStack != NULL) {
        pNode = (LinkedStackNode *)malloc(sizeof(LinkedStackNode));
        if(pNode != NULL) {
            pNode = (LinkedStackNode *) malloc(sizeof(LinkedStackNode));
            
                pNode->data = data;
                pNode -> pLink = pStack -> pTop;
                pStack->pTop = pNode;

                pStack->currentCount++;
                ret =1;
        }
            else {
                    printf("오류,  메모리할당,pushLS()\n");
            }
        }
    
    return ret;
}

int isLinkedStackEmpty(LinkedStack* pStack){
    int ret = 0 ;

    if(pStack != NULL) {
        if(pStack->currentCount == 0 ){
            ret = 1;
        }
    }
    return ret;
}

LinkedStackNode* popLS(LinkedStack* pStack){
    LinkedStackNode* pReturn = NULL;
    if(pStack != NULL) {
        if(isLinkedStackEmpty(pStack) == 0) {
            pReturn = pStack->pTop;
            pStack->pTop = pReturn ->pLink;
            pReturn->pLink = NULL;

            pStack->currentCount--;
        }
    }
    return pReturn;
}

LinkedStackNode* peekLS(LinkedStack* pStack){
    LinkedStackNode* pReturn = NULL;
    if(pStack != NULL) {
        if(isLinkedStackEmpty(pStack) == 0) {
            pReturn = pStack->pTop;
        }
    }
    return pReturn;
}

void deleteLinkedStack(LinkedStack* pStack){
  LinkedStackNode *pNode = NULL;
  LinkedStackNode *pDelNode = NULL;
  while(pNode != NULL) {
    pDelNode = pNode;
    pNode = pNode->pLink;
    free(pDelNode);
  }
  free(pStack);
}

void displayLinkedStack(LinkedStack *pStack){


    LinkedStackNode *pNode = NULL;
    int i=0;
    if(pStack != NULL) {
        printf("노드 개수 : %d\n", pStack->currentCount);
        pNode = pStack->pTop;
        while(pNode != NULL) {
            printf("[%d] = [%c]\n",pStack->currentCount-i,pNode->data);
            i++;
            pNode = pNode->pLink;
        }
    }
}

char* reverseString(char *pSource){
    char* pReturn = NULL;
    int i = 0;
    int size = 0;
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;


    pStack = createLinkedStack(); //스택 생성
    if(pStack != NULL) { //유효성 검사
        while(pSource[size] != '₩0'){  //while문을 돌며 스택에 입력받은 문자열 저장
            pushLS(pStack, pSource[size]);
            size++;
        }
    
        pReturn = (char *)malloc(sizeof(char)*(size + 1));
        memset(pReturn, 0, sizeof(char) * (size + 1));
        while(i<size){
            pNode = popLS(pStack);
            if(pNode != NULL) {
                pReturn[i] = pNode->data;
                free(pNode);
            }
            i++;
        }
        deleteLinkedStack(pStack);
    }
    return pReturn;
}

int main(int argc, const char * argv[]){
    char szSource[] = "ABCD";
    char *pszReverse = reverseString(szSource);
    if(pszReverse != NULL) {
        printf("[%s] => [%s\n]", szSource, pszReverse);

        free(pszReverse);
    }
    return 0;
}