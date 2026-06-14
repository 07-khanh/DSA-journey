#include <iostream>
using namespace std;

/*
Loop invariant: 
- Inner loop: At the start of each iteration of the inner loop (indexed by j), a[j] is the largest element in the subarray a[0...j].
- Outer loop: At the start of each iteration of the outer loop (indexed by i), the subarray a[n-i...n-1] consists of the 
i largest elements of the original array in their final sorted positions.


Time complexity: Theta(n^2) for all cases.
    Theta(n) in best cases for optimized version
Space complexity: O(1).

*/

//=========================
// Bubble Sort on Array
//=========================

void BUBBLE_SORT(int a[], int n) {
    for (int i{0}; i < n-1; ++i) 
        for (int j{0}; j < n-i-1 ; ++j) 
            if (a[j] > a[j+1]) 
                swap(a[j], a[j+1]);
}

// OPTIMIZED
void BUBBLE_SORT(int a[], int n) {
    for (int i{0}; i < n-1; ++i) {
        bool didSwap = false;
        for (int j{0}; j < n-i-1 ; ++j) {
            if (a[j] > a[j+1]) {
                didSwap = true;
                swap(a[j], a[j+1]);
            }
        }
        // If no two elements are swapped, then break
        if (!didSwap) break;
    } 
}

//=========================
// Bubble Sort on Linked List
//=========================

struct Node {
    int data;
    Node* next;
};

int COUNT_NODE(Node* head) {
    int count{0};

    Node* it = head;
    while (it) {
        it = it->next;
        ++count;
    }
    return count;
}

Node* BUBBLE_SORT(Node* head) {
    if (!head || !head->next) return head;

    int it = COUNT_NODE(head);

    for (int i{0}; i < it; ++i) {
        Node* prev = nullptr;
        Node* cur = head;
        bool swapped = false;

        while (cur->next) {
            Node* next = cur->next;

            if (cur->data > next->data) {
                swapped = true;
                if (cur == head) {
                    cur->next = next->next;
                    next->next = cur;
                    prev = next;
                    head = prev;
                }
                else {
                    cur->next = next->next;
                    next->next = cur;
                    prev->next = next;
                    prev = next;
                }
            }
            else {
                prev = cur;
                cur = cur->next;
            }
        }
        if (!swapped) break;
    }
    return head;
}