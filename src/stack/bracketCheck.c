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

int checkBracketMatching(char *pSource) {

    int ret=0;
    int i = 0;
    char symbol = '\0';
    char checkSymbol = '\0';
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();
    if(pStack != NULL) {
        while( 0 != pSource[i] && 0 ==ret){
            symbol = pSource[i];
            switch(symbol) {
                case '(' :
                case '[' :
                case '{' :
                    pushLS(pStack, symbol);
                    break;

                case ')' :
                case ']' :
                case '}' :
                    pNode = popLS(pStack);
                    if(pNode == NULL) {
                        ret = 1;
                    }
                    else {
                        checkSymbol = pNode->data;
                        if((symbol == ')' && checkSymbol == '(')
                        || (symbol == ']' && checkSymbol == '[')
                        || (symbol == '}' && checkSymbol == '{')){
                            
                        }
                        else {
                            ret = 2;
                        }
                        free(pNode);
                    }
                    break;
            }
            i++;
        }
        if( 0 ==ret && isLinkedStackEmpty(pStack) == 0) {
            ret = 3;
        }
        deleteLinkedStack(pStack);
    }


    return ret;

}

int main(int argc, const char * argv[]) {
    int checkResult =0;
    int i=0;
    char szExpressionStr[][50] = {
        "(A + B ) * C",
        "{ ( A + B ) * C } * D", 
        " ( A + B )  * C)",
        "( ( A + B )  * C",
        "{ ( A + B } ) * C * D"
    };

    for(i = 0; i<sizeof(szExpressionStr)/sizeof(szExpressionStr[0]); i++){
        checkResult = checkBracketMatching(szExpressionStr[i]);
        if(checkResult==0){
            printf("성공, %s\n", szExpressionStr[i]);
        }
        else {
            printf("실패 - [%d], %s\n", checkResult, szExpressionStr[i]);
        }
    }
    return 0;
}