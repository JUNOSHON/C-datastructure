void concatLinkedList(LinkedList* pListA, LinkedList* pListB){

    LinkedListNode* pNodeA = NULL;
    if(pListA != NULL && pListB != NULL){
        pNodeA = pListA->headerNode.pLink;
        while(pNodeA != NULL && pNodeA->pLink != NULL){
            pNodeA = pNodeA->pLink;
        }

        pNodeA->pLink = pListB->headerNode.pLink;
        pListB->headerNode.pLink = NULL;
    }
}