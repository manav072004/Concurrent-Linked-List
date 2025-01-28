#include "ConcurrentLinkedList.h"

// Constructor initializes the linked list with a nullptr head and creates a filter lock for synchronization.
ConcurrentLinkedList::ConcurrentLinkedList()
    : head(nullptr), filterLock(4) {}  // Default to 4 threads, can be adjusted based on need.

// Insert method adds a new node with the given value to the end of the linked list.
void ConcurrentLinkedList::insert(int value, int threadId) {
    filterLock.lock(threadId);  // Acquire the filter lock for thread synchronization.
    
    if (head == nullptr) {
        // If the list is empty, create the first node.
        head = std::make_shared<Node>(value);
    } else {
        // Otherwise, traverse to the end of the list and append the new node.
        std::shared_ptr<Node> current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = std::make_shared<Node>(value);
    }

    filterLock.unlock(threadId);  // Release the filter lock after the operation is complete.
}

// Print method prints all elements in the linked list.
void ConcurrentLinkedList::print() {
    std::shared_ptr<Node> current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";  // Print data of each node.
        current = current->next;           // Move to the next node in the list.
    }
    std::cout << std::endl;  // Print a newline after the list.
}