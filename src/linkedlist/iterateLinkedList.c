void iterateLinkedList(LinkedList* pList)
{
    int count =0 ;
    LinkedListNode* pNode = NULL;

    pNode = pList -> headerNode.pLink;
    while(pNode != NULL){
        printf("[%d], %d\n", count , pNode->data); //로직 처리 부분, 자료 출력
        pNode = pNode->pLink;
    }
    printf("노드 개수 : %d\n",count);
}