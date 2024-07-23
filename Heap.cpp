// heap.cpp -- implementation file for a min-heap
// c. 2015 A. Deeter, revisions c. 2015 C. Reilly

#include "Heap.hpp"
#include "HNode.hpp"
#include <vector>

// anonymous namespace to hide helper functions, so that they're not confused with the STL functions
namespace {

    // get the minimum node of two indices
    int min(std::vector<HNode*>& v, int indexA, int indexB) {
        if (v[indexA] < v[indexB]) {
            return indexA;
        }
        else {
            return indexB;
        }
    }

    // swap two indices in the tree
    void swap(std::vector<HNode *> &tree, int indexA, int indexB)
    {
        auto temp = tree[indexA];
        tree[indexA] = tree[indexB];
        tree[indexB] = temp;
    }
}

// add an element to the tree
void Heap::enqueue(HNode *node)
{
    // the first element is always 0 in the heap vector, so if it's empty, before adding anything else, put 0
    // this is the standard definition of the heap in that the array/vector has a trivial value in the 0th index
    // and the true root is at index 1
    if (tree.size() == 0)
    {
        tree.push_back(new HNode(0, 0));
    }

    tree.push_back(node);
    ++position;
    ++count;

    // we need to heapify the tree from the root.
    fix_up(position);

}

// fix the heap from a specific index up
void Heap::fix_up(const int &index)
{
    // if the heap is only one element, then no need to heapify because it's a heap by definiton.
    // if index is 0 or lower, then it is out of bounds.
    if (index <= 1)
    {
        return;
    }

    // start at the current index, and go up the tree by finding the parent and swaping until we reach the root.
    for (int currentIndex = index; currentIndex > 0; --currentIndex)
    {
        int parentIndex = currentIndex / 2;

        // if the parent is smaller than the current node, then swap them.
        while (parentIndex > 0 && tree[currentIndex]->weight < tree[parentIndex]->weight)
        {
            swap(tree, currentIndex, parentIndex);
            parentIndex /= 2;
        }
    }
}

// remove the smallest element
HNode *Heap::dequeue()
{
    // if tree has 1 or no elements, then it's empty because we don't count the element at index 0.
    if (tree.size() <= 1)
    {
        return nullptr;
    }

    // take first element and replace it with last element to maintain the heap property.
    HNode *minNode = tree[1];
    tree[1] = tree[position];

    tree.pop_back(); // Remove the last element.
    --position;
    --count;

    // we just put the last element in the root, now we need to heapify it from root.
    fix_down(1);

    return minNode;
}

// fix the tree after replacing the smallest element
// This assumes that the heap is organized except for the element at given index
void Heap::fix_down(const int &index)
{
    //if the heap has only one node or none (since the first node is on index 1)
    if(tree.size() <= 2) {
        return;
    }


    int parent = index;
    while (parent < tree.size()) {
        int left = parent * 2;
        int right = left + 1;
        // if left index exists, then check if its smaller than parent. If right index exists, then check if its smaller than parent.
        // if either are smaller than parent, then we will swap the smaller with the parent
        if ( (left < tree.size() && tree[left] < tree[parent]) || ( right < tree.size() && tree[right] < tree[parent]) ) {
            int smaller = min(tree, left, right);
            swap(tree, parent, smaller);
            parent = smaller;
        }
        else {
            break;
        }

    }
}

void deleteChildren(HNode* node) {
    if(node == nullptr)
        return;
    if(node->left != nullptr) {
        deleteChildren(node->left);
    }
    if(node->right != nullptr) {
        deleteChildren(node->right);
    }
    delete node;
}

void Heap::clear()
{
    for (HNode *node : tree)
    {
        deleteChildren(node);
    }
    tree.clear();
    position = 0;
}
