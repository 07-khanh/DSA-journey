#include <iostream>
using namespace std;

//=========================
// Merge Sort on Array
//=========================

void MERGE(int A[], int low, int mid, int high) {
    int n_l = mid - low + 1;
    int n_r = high - mid;

    int L[n_l];
    int R[n_r];

    for (int i = 0; i < n_l; ++i) 
        L[i] = A[low+i];
    for (int i = 0; i < n_r; ++i) 
        R[i] = A[mid+i+1];

    int i = 0;
    int j = 0;
    int k = low;

    while (i < n_l && j < n_r) {
        if (L[i] <= R[j]) 
            A[k++] = L[i++];
        else 
            A[k++] = R[j++];
    }

    while (i < n_l) 
        A[k++] = L[i++];
    while (j < n_r) 
        A[k++] = R[j++];
    

}

void MERGE_SORT(int A[ ], int low, int high) {
    if (low >= high) return;

    int mid = (low+high)/2;
    MERGE_SORT(A, low, mid);
    MERGE_SORT(A, mid+1, high);
    MERGE(A, low, mid, high);
}


//=========================
// Merge Sort on Linked List
//=========================

struct Node {
    int data;
    Node* next;
};

Node* SPLIT(Node* head) {
    Node* fast = head;
    Node* slow;

    while (fast && fast->next) {
        fast = fast->next->next;

        if (fast->next)
            slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node* MERGE(Node* first, Node* second) {
    if (!first) return first;
    if (!second) return second;

    if (first->data <= second->data) {
        first->next = MERGE(first->next, second);
        return first;
    }
    else {
        second->next = MERGE(first, second->next);
        return second;
    }
} 

Node* MERGE_SORT(Node* head) {
    if (!head || !head->next) return head;
    
    Node* mid = SPLIT(head);

    MERGE_SORT(head);
    MERGE_SORT(mid);
    MERGE(head, mid);

    return head;
}