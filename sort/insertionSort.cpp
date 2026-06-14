#include <iostream>
using namespace std;

/*
Loop invariant: At the start of each iter, A[0..i-1] is sorted and contains the same elements as originally (the unsorted ver).
In each iter, take A[i] as key, and shift all elements > key to the right. Then put key in correct position.
After insertion, A[0..i] is sorted, and contains the exact same elements. -> Loop invariant maintained.
Termination: stop when i == n, then A[0..n-1] is sorted -> the entire array is sorted.

Time complexity: (depend on the inner while loop) 
- Best case (sorted array, only one comparison per element): Theta(n)
- Worst case (reversed array, each insertion shifts all previous elements -> cause arithmetic series): Theta(n^2)
*/

//=========================
// Insertion Sort on Array
//=========================

void INSERTION_SORT(int* A, int n) {
    for (int i = 1; i < n; ++i) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}

//=========================
// Insertion Sort on Linked List
//=========================

struct Node {
    int data;
    Node* next;
};

Node* INSERT(Node* newNode, Node* sorted) {

    if (!sorted || sorted->data > newNode->data) {
        newNode->next = sorted;
        sorted = newNode;
    }
    else {
        Node* cur = sorted;
        while (cur->next && cur->next->data <= newNode->data) {
            cur = cur->next;
        }

        newNode->next = cur->next;
        cur->next = newNode;
    }
    return sorted;
}

Node* INSERTION_SORT(Node* head) {
    if (!head || !head->next) return head;

    Node* sorted = nullptr;
    Node* cur = head;

    while (cur) {
        Node* next = cur->next;
        sorted = INSERT(cur, sorted);
        cur = next;
    }
    return sorted;
}