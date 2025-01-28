#define CONCURRENTLINKEDLIST_H

#include <iostream>
#include <memory>
#include "FilterLock.h"

// ConcurrentLinkedList class that implements a thread-safe linked list using FilterLock.
class ConcurrentLinkedList {
public:
    // Constructor initializes the linked list with an empty head and filter lock.
    ConcurrentLinkedList();

    // Insert method adds a value to the end of the list while ensuring thread synchronization.
    void insert(int value, int threadId);

    // Print method prints all the values in the linked list.
    void print();

private:
    // Node structure represents a single element in the linked list.
    struct Node {
        int data;                      // Data stored in the node.
        std::shared_ptr<Node> next;     // Pointer to the next node in the list.
        
        Node(int data) : data(data), next(nullptr) {}
    };

    std::shared_ptr<Node> head;    // Pointer to the head (first node) of the list.
    FilterLock filterLock;         // Filter lock for thread synchronization during insert operations.
};
