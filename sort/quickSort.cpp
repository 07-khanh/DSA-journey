#include <iostream>
#include <cstdlib>
using namespace std;

//=========================
// Quicksort on Array
//=========================

int RANDOMIZED_PARTITION(int* A, int p, int r) {
    int s = p + rand() % (r - p + 1);
    swap(A[r], A[s]);
    
    int i = p - 1;
    int x = A[r];
    for (int j = p; j <= r - 1; ++j) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i+1;
}

void QUICKSORT(int* A, int p, int r) {
    if (p >= r) return;
    int q = RANDOMIZED_PARTITION(A, p, r);
    QUICKSORT(A, p, q-1);
    QUICKSORT(A, q+1, r);
}


//=========================
// Quicksort on Linked List
//=========================

struct Node {
    int data;
    Node* next;
};

Node* GET_TAIL(Node* head) {
    if (!head) return head;
    
    while (head->next)
        head = head->next;
    return head;
}

Node* PARTITION(Node* head, Node* tail) {
    if (!head || !head->next) return head;

    Node* pivot = head;
    Node* prev = head;
    Node* cur = head;
    
    while (cur != tail->next) {
        Node* traverse = cur->next;
        if (cur->data < pivot->data) {
            swap(cur->data, prev->next->data);
            prev = prev->next;
        }
        cur = cur->next;
    }
    swap(pivot->data, prev->data);
    return prev;
}

void QUICK_SORT_HELPER(Node* head, Node* tail) {
    if (!head || !head->next) 
        return;

    Node* pi = PARTITION(head, tail);
    
    Node* be_pi = head;
    while (be_pi && be_pi->next != pi) 
        be_pi = be_pi->next;
    
    if (be_pi != head)
        QUICK_SORT_HELPER(head, be_pi);

    if (pi->next != nullptr)
        QUICK_SORT_HELPER(pi->next, tail);
    
}

Node* QUICK_SORT(Node* head) {
    if (!head || !head->next) 
        return head;

    Node* tail = GET_TAIL(head);
    QUICK_SORT_HELPER(head, tail);
    return head;
}