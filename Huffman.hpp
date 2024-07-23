// huffman.hpp -- Huffman tree header
// c. 2015 A. Deeter

#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <map>
#include "Heap.hpp"
#include "HNode.hpp"

// this struct is used to return the encoded strings and tree
struct Encoded
{
    // store your encoded string here
    std::string encoded_string;

    // store your serialied tree here
    // use binary tree serialization (using '/')
    // inner nodes should use '*' for their value, leaf nodes should use the character they represent
    std::string serialized_tree;
};

// this struct will take a string, build a huffman coding tree with it,
// and return an object with the encoded string and the serialied tree in it
struct Huffman
{
private:
    // the heap used to store your HNodes
    Heap heap;

    // store the frequencies for each character here
    // the function that does this, create_freq, is given
    std::map<char, int> freq;

    // store the codes for each character
    // you will implement the create_codes function to fill this after your tree is built
    // reference the given create_freq function to see how to work with maps
    // you can also reference http://www.cplusplus.com/reference/map/map/
    std::map<char, std::string> codes;

    // implement these functions
    // their descriptions are below
    void create_freq(const std::string &);

    void create_codes(HNode *, const std::string &);
    void serialize_tree(HNode *, std::string &);
    void encode_string(const std::string &, std::string &);

public:
    // this function will take a string as a parameter and return an Encoded object
    // the object containts the encoded string and the serialied tree used to encode/decode
    Encoded encode(const std::string &);
};

#endif
