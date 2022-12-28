int addLinkedListData(LinkedList * plist, int position int data){
    int i = 0;
    LinkedListNode *pNewNode = NULL;
    LinkedListNode *pPreNode = NULL;

    pNewnode = (LinkedListNode * )malloc(sizeof(LinedListNode));
    pNewNode->data = data;

    pPreNode = &(plist->headerNode);
    for(i=0;i<position;i++){
        pPreNode = pPreNode->pLinkl;
    }

    pNewNode->pLink = pPreNode->pLink; //다음 노드 처
    pPreNode->pLink = pNewNode;//이전 노드 처리

    pList->currentNcount++;// 현재 노드 증가
    return 0;

}