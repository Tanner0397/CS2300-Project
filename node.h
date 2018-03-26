#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <vector>

int const TREE_ORDER = 4;
int const NUMBER_OF_SIBLINGS = 2;

class leafNode;//Forward declaration

class Node
{
protected:
  std::vector<unsigned int> keys;
private:
  unsigned int numKeys;
  Node* childNodes[TREE_ORDER];//Array of pointers to children
public:
  Node();//class constructor
  unsigned int getNumKeys();//This will return the number of keys in the node
  unsigned int getKey(int index);//Returns the key value af the given index
  Node* getChild(int index);//0 is left most and 3 is right most
  bool isLeafNode();//retursn true if this is a leaf node
};//End of class Node

class leafNode : public Node //leafNode inherits from Node
{
private:
  leafNode* siblings[NUMBER_OF_SIBLINGS];//0 will be left sibling, 1 will be right siblings

public:
  leafNode();
  leafNode* getLeftSibling();//returns pointer to the left sibling
  leafNode* getRightSibling();

};//End of Class Leaf Node

struct BPlusTree
{

  Node* root;//Root of the tree
  BPlusTree();
  Node* searchKey(unsigned int const key);
  Node* search(Node* node ,unsigned int const key);
  void insert(unsigned int key);
  void del(unsigned int key);
  void print();

};//end of BPlusTree struct


#endif //End of preprocessor directive
