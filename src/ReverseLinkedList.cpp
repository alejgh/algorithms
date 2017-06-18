/**
 * Simple exercise where you have to reverse
 * a linked list. The skeleton is given, and
 * I only had to implement the 'reverse_list(Node* head)'
 * function.
 */

#include <iostream>

struct Node {
    int data;
    Node* next;
};

Node* create_node(int node_data){

    //Create the node.
    Node* n = new Node();

    //Set the data.
    n->data = node_data;

    return n;
}

//Create a new node and set the inputted node's next pointer
//to the new node. Returns a reference to the new node.
Node* push_node(Node* curr, int node_data){

    if(curr == NULL){
        return NULL;
    }

    Node* n = create_node(node_data);

    //Set the next pointer of the current node to the new node.
    curr->next = n;

    return n;
}

//Creates a linked list with the number of nodes equal to the inputted size.
//Node data is set to 0, 1, 2, ... through "N" sequentially.
//Returns a reference to the head of the list.
Node* create_linked_list(int size){

    if(size < 1){
        return NULL;
    }

    Node* head = create_node(0);
    Node* curr = head;

    for(int i = 1; i < size; i++){
        curr = push_node(curr, i);
    }

    return head;
}

void print_linked_list(Node* head){

    Node* curr = head;

    while(curr != NULL){
        std::cout << curr->data;
        curr = curr->next;
    }

    std::cout << std::endl;
}

void reverse_list(Node* head){
    if(head == NULL || head->next==NULL){
        return;
    }

    //Your code here.
    Node* previous = NULL;
    Node* next = NULL;
    Node* curr = new Node();
    curr->data = head->data;
    curr->next = head->next;

    while(curr->next != NULL){
        next = curr->next;
        curr->next = previous;
        previous = curr;
        curr = next;
    }
    head->data = curr->data;
    head->next = previous;
    delete curr;
}

int main()
{
    Node* head = create_linked_list(10);
    print_linked_list(head);

    //You should see: 0123456789

    reverse_list(head);
    print_linked_list(head);

    //You should see: 9876543210

    return 0;
}