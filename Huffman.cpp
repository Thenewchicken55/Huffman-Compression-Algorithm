// huffman.cpp -- Huffman tree class
// c. 2015 A. Deeter

#include "Huffman.hpp"

// implement this function
// use a pre-order traversal, keeping track of the path to the current node (0 for left, 1 for right)
// all leaf nodes will be letters within the original string
// the path to the node will be the code for that letter
// the code parameter for each recursive call is determined by the current code + '0' if youre recursing left
// and '1' if youre recursing right
// add a new <char, std::string> to the codes map with the character and its code for each leaf node
// using std::make_pair (see create_freq)
void Huffman::create_codes(HNode* node, const std::string &code)
{
    // error handling, in case the previous node is a leaf node
    if (node == nullptr) {
        return;
    }

    // base case, if the node is a leaf node, add its code to the codes map
    if(node->value != '*') {
        codes.insert(std::make_pair(node->value, code));
    }

    create_codes(node->left, code + '0');
    create_codes(node->right, code + '1');
}

// implement this function
// this recursive function should do a pre-order traversal
// the string s is a reference to a string that holds the serialized tree
// this is similar to how we serialized before but without a vector
// use binary tree serialization (using '/')
// the characters from each HNode will be used (inner nodes should use '*')
// there is no return value as s is being edited with each resursive call
void Huffman::serialize_tree(HNode *node, std::string &s)
{
    // base case.
    if(node == nullptr) {
        s += '/';
        return;
    }

    s += node->value;

    serialize_tree(node->left, s);
    serialize_tree(node->right, s);
}

// implement this function
// this will use the codes map to encode the given string
// for each character in the input string, add the code for that letter to the end of the encoded string
// the encoded_string is not const because we are changing the reference as we go
// if the code for a is 1, the code for b is 01, and the code for c is 00
// the code for the word 'bad' would be '01100'
void Huffman::encode_string(const std::string &input, std::string &encoded_string)
{
    for (auto iter = input.begin(); iter!= input.end(); ++iter) {
        encoded_string += codes[*iter];
    }
}

Encoded Huffman::encode(const std::string &s)
{
    // your heap implementation MUST have a clear function that
    // removes all HNodes from it
    heap.clear();

    // clear out the maps
    freq.clear();
    codes.clear();

    // the return value holding the encoded string and serialized tree
    Encoded ret;

    // create the frequency map
    create_freq(s);

    // create huffman nodes and add them to your heap
    // your heap must have an enqueue function that takes an HNode*
    for (auto iter = freq.begin(); iter != freq.end(); ++iter)
    {
        heap.enqueue(new HNode(iter->first, iter->second));
    }

    // while there are at least two items in the heap
    // create a new node that combines the first and second node into a new node
    // the char should be '*' and the value should be the values of the children added together
    // I recommend making a constructor tat takes two node pointers to do this easily
    while (heap.count > 1)
    {
        heap.enqueue(new HNode(heap.dequeue(), heap.dequeue()));
    }

    // store the pointer to the huffman tree
    HNode *huffman_tree = heap.dequeue();

    // create the codes for each leaf in the final tree
    // the default code is an empty string, as the function recurses the code is added to
    create_codes(huffman_tree, "");

    // serialize the huffman tree
    // store it within ret
    serialize_tree(huffman_tree, ret.serialized_tree);

    // encode the original string using the codes map
    // store it within ret
    encode_string(s, ret.encoded_string);

    heap.clear();

    // delete the tree
    delete huffman_tree;

    // return the final Encoded object
    return ret;
}

// this function will create a map of characters to values based on the number of times the character was in the given string
// in order to store the frequencies of the letters in the string
void Huffman::create_freq(const std::string &s)
{
    for (int i = 0; i < s.size(); ++i)
    {
        // this will atempt to insert a character into the freq map
        // if it is already in the map, the 'second' member will be false, and we know to increase the count
        // iter is an iterator pointing to the found item in the map
        if (freq.insert(std::make_pair(s[i], 1)).second == false)
        {
            auto iter = freq.find(s[i]);
            iter->second += 1;
        }
    }
}
