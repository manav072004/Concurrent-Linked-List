#include "ConcurrentLinkedList.h"
#include "FilterLock.h"

// Constructor initializes the linked list with a nullptr head and creates a filter lock for synchronization.
ConcurrentLinkedList::ConcurrentLinkedList()
    : head(nullptr) {
    filterLock.init(4);  // Initialize the filter lock for 4 threads (adjust as needed).
}

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

// Delete method removes a node with the given value from the linked list.
void ConcurrentLinkedList::deleteNode(int value, int threadId) {
    filterLock.lock(threadId);  // Acquire the filter lock for thread synchronization.

    // Special case: if the list is empty, there's nothing to delete.
    if (head == nullptr) {
        filterLock.unlock(threadId);
        return;
    }

    // Special case: if the node to delete is the head node.
    if (head->data == value) {
        head = head->next;  // Update head to the next node.
        filterLock.unlock(threadId);
        return;
    }

    // Traverse the list to find the node to delete.
    std::shared_ptr<Node> current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    // If we found the node to delete, remove it.
    if (current->next != nullptr) {
        current->next = current->next->next;  // Bypass the node to delete.
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