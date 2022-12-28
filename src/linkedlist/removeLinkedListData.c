int removeLinkedListData(LinkedList* pList, int positioin){
    int i =0;
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPreNode = NULL;

    pPreNode = &(pList->headerNode);
    for(i=0;i<positioin;i++){
        pPreNode = pPreNode->pLinkl;
    }

    pDelNode = pPreNode -> pLink;//제거하려논 노드 지정,이전 노드가 가리키는 값
    pPreNode -> pLink = pDelNode->pLink;//이전 노드 처리

    free(pDelNode);
    pList->currentCount--;
    return 0;

}