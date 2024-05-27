// CIS 22C - Kanan Ibadzade - HW 4 extra credit


//percolDown:
// Utilizing the parent node's index, the function will make sure the subtree rooted at this index matches the min-heap condition.


void StudMinHeap::percolDown(int parentIndex) {
    int childIndex = 2 * parentIndex + 1; // Left child index
    int heapSize = /* size of your heap array */;

    if (childIndex < heapSize) {
        // Check if right child exists and is smaller than left child
        int rightChildIndex = childIndex + 1;
        if (rightChildIndex < heapSize&& /* right child is smaller than left child */) {
            childIndex = rightChildIndex; // Use the smaller child
        }

        // Compare selected child with parent
        if (/* child is smaller than parent */) {
            // Swap parent with smaller child
            // ...

            // Recursively percolate down the child now
            percolDown(childIndex);
        }
    }
}



//GetSize:
//Recursive Method: Count the nodes with the given priority as you iteratively go over the heap.
//Non-Recursive Method: Count the nodes with the specified priority by iterating over the heap's array.


int StudMinHeap::getPriSize(int priorityLevel, int index = 0) {
    if (index >= /* size of your heap array */) return 0;
    int count = (/* priority of node at index */ == priorityLevel) ? 1 : 0;
    count += getPriSize(priorityLevel, 2 * index + 1); // Left child
    count += getPriSize(priorityLevel, 2 * index + 2); // Right child
    return count;
}


//Used CHatGPT 