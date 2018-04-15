#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include "node.h"

class BPlusTree
{
private:
  static unsigned int print_id;
  Node* root;//Root of the tree
  Node* searchKey(unsigned int const key);//searches for a ndoe that could contain key
  Node* searchLeaf(Node* node ,unsigned int const key);//recursive fucntion to search
  Node* firstInstance(Node* node, unsigned int const);//this retuns the first node it finds with this key in it
  /*Returns pointer to right sibling. Returns null if there is none*/
  Node* findRightSibling(Node* node);
  /*Returns pointer to left sibling. Returns null if there is none*/
  Node* findLeftSibling(Node* node);
  /*resursive function that descends node by it's last child until a leaf is found.
  Used to find what keys need to be replaced when moving and merging internal nodes*/
  Node* getLastNode(Node* node);
  /*Resursive function that will split nodes into 1 more leafNode.
  An extra internal node is generated if split proagtes to the root.
  In this implemntation where the degreee of the tree is 4, there will be at msot 3
  keys in any given node so you will split the third key up.*/
  Node* split(Node* node, unsigned int const key);
  /*This inserts a child into a node. A key has been inserted into parent
  now we must add the correct child*/
  void insertChild(Node* parent, Node* node);
  /*Removed the child node from parent. Also removes the correct key*/
  void removeChild(Node* parent, Node* node);
  /*Redistribites the nodes from sibling to node. Handles both cases where
  sibling is to the left or to the right. Also handles if node and sibling are internal
  and leaf nodes*/
  void redistribute(Node* node, Node* sibling, unsigned int const key);
  /*Resursive function that merges two nodes togther. We only want to merge two nodes if
  they share same parent. We have a leftMerge boolean to use in the case that sibling is
  to the left of node. In that case some things may change because we may need to look in
  different places to find the keys in internal nodes that need to change*/
  void merge(Node* node, Node* sibling, unsigned int const key, bool leftMerge);
  /*auxiliiary function for redistribute so that when a key is moved some leaf node, it is
  reflected in the internal nodes*/
  void moveKey(Node* node, unsigned int const key);
  /*The following functions are recursive functions that perform a inorder tree traversal so that
  we can output the nodes to an image via graphviz. */
  void outputNodes(Node* node, std::ofstream &buffer);
  void outputLinks(Node* node, std::ofstream &buffer);
  void outputSiblings(Node* node, std::ofstream &buffer);
public:
  BPlusTree();
  //render the most recent changes to the B plus tree
  void print();
  //Delete some key. Provides message if key does not exist
  void del(unsigned int const key);
  //Insert some key. Provides message if key already exist in a node.
  void insert(unsigned int const key);


};

#endif
