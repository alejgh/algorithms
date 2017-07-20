struct Node
{
    int value;
    Node* next;
};

Node* buildList(int size)
{
    Node* head = nullptr;
    for (int i = size - 1; i >= 0; i--)
    {
        Node *curr = new Node();
        curr->value = i;
        curr->next = head;
        head = curr;
    }
    return head;
}

Node* removeNode(Node** head, int searchValue)
{
    Node** doublePtr = head;

    while(*doublePtr != nullptr && (*doublePtr)->value != searchValue)
        doublePtr = &((*doublePtr)->next);

    if (*doublePtr == nullptr) return *doublePtr;

    Node* nodeToRemove = *doublePtr;
    *doublePtr = nodeToRemove->next;
    return nodeToRemove;
}

int main()
{
    Node* head = buildList(6);

    Node* removedNode = removeNode(&head, 7);
    Node* removedNode2 = removeNode(&head, 3);
    Node* removedNode3 = removeNode(&head, 0);
    Node* removedNode4 = removeNode(&head, 5);

    Node* nullNode = nullptr;
    Node* removedNode5 = removeNode(&nullNode, 25);
}