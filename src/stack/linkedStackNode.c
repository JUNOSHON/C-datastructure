#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct LinkedStackNodeType {
    char data;
    struct LinkedStackNode* pLink;
} LinkedStackNode; //연결스택의 노드

typedef struct LinkedStacType {
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
int main(int argc, char *argv[]) {


    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();
    if(pStack != NULL){
        pushLS(pStack,'a');
        pushLS(pStack,'b');
        pushLS(pStack,'c');
        pushLS(pStack,'d');

        displayLinkedStack(pStack);
        
        pNode = popLS(pStack);
        if(pNode != NULL) {
            printf("pop한 값 - [%c]\n", pNode->data);
            free(pNode);
        }

        displayLinkedStack(pStack);

        pNode = peekLS(pStack);

        pNode = peekLS(pStack);
        if(pNode != NULL) {
            printf("peek 값 - [%c]\n", pNode ->data);

        }
        deleteLinkedStack(pStack);


    }
    return 0;


}