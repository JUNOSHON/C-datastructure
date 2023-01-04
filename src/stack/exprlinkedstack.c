
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum PrecedenceType { lparen, rparen, multiply, divide, plus, minus, operand} Precedence;



typedef struct ExprTokenType {
    double value;
    Precedence type;
} ExprToken;

typedef struct LinkedStackNodeType {
   
   ExprToken data;
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
int pushLS(LinkedStack* pStack, ExprToken data) {
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

void clacExpr(ExprToken *pExprTokens, int tokenCount){
    
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode1 = NULL, *pNode2 = NULL;
    Precedence tokenType;
    
    int i = 0;

    if(pExprTokens == NULL) {
        return ;
    }

    pStack = createLinkedStack();
    if(pStack != NULL) {
        for(i = 0;i<tokenCount; i++){
            tokenType = pExprTokens[i].type;

            if(tokenType == operand){
                pushLS(pStack, pExprTokens[i]);
            }
            else{
                pNode2 = popLS(pStack);
                if(pNode2 != NULL) {
                    pNode1 = popLS(pStack);
                    if(pNode1 != NULL){
                        double op1 = pNode1->data.value;
                        double op2 = pNode2->data.value;

                        ExprToken newToken;
                        newToken.type = operand;
                        switch(tokenType) {
                            case plus : 
                                newToken.value = op1 + op2;
                                break;
                            case minus:
                                newToken.value = op1 - op2;
                                break;
                            case multiply:
                                newToken.value = op1*op2;
                                break;
                            case divide:
                                newToken.value = op1/op2;
                                break;
                        }
                        pushLS(pStack, newToken);
                        free(pNode1);
                    }
                    free(pNode2);
                }
            }
        }
            pNode1 = popLS(pStack);
            if(pNode1 != NULL) {
                printf("수식 계산 결과는 [%f]입니다\n", pNode1->data.value);
                free(pNode1);
            }
            else{
                printf("오류, 수식에 오류가 있습니다\n");
            }
            deleteLinkedStack(pStack);
        }
    }


int main(int argc, const char * argv[]){
    int i =0 ;


    ExprToken *pExprTokens = (ExprToken *)malloc(sizeof(ExprToken) * 7);

    pExprTokens[0].type = operand;
    pExprTokens[0].value = 2;

    pExprTokens[1].type = operand;
    pExprTokens[1].value = 3;

    pExprTokens[2].type = operand;
    pExprTokens[2].value = 4;

    pExprTokens[3].type = plus;
    pExprTokens[3].value = 0;

    pExprTokens[4].type = operand;
    pExprTokens[4].value = 5;

    pExprTokens[5].type = multiply;
    pExprTokens[5].value = 0;

    pExprTokens[6].type = minus;
    pExprTokens[6].value = 0;

    printf("Expression : 2 3 4 + 5 * - \n");
    clacExpr(pExprTokens, 7);

    free(pExprTokens);

    return 0;

}