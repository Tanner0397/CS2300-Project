#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>

int const TREE_ORDER = 4;
int const LAST_KEY = 2;
int const NUMBER_OF_SIBLINGS = 2;

class leafNode;//Forward declaration

class Node
{
protected:
  std::vector<unsigned int> keys;
private:
  unsigned int numKeys;
  Node* childNodes[TREE_ORDER];//Array of pointers to children
  Node* parent;
public:
  virtual ~Node() = default;//For dynamic casting
  Node();//class constructor
  Node(const Node &node);
  unsigned int getNumKeys();//This will return the number of keys in the node
  std::vector<unsigned int> getKeys();//returns vector of keys
  unsigned int getKey(int index);//Returns the key value af the given index
  unsigned int getLastKey();
  Node* getParent();
  Node* getChild(int index);//0 is left most and 3 is right most
  bool isLeafNode();//retursn true if this is a leaf node
  bool isFull();//
  void insertKey(unsigned int const key);
  void deleteKeyIndex(int index);
  void setChild(Node* node, int index);
  void setParent(Node* node);
  void insertChild(Node* node);
  std::string print(int num);
};//End of class Node

class leafNode : public Node //leafNode inherits from Node
{
private:
  leafNode* siblings[NUMBER_OF_SIBLINGS];//0 will be left sibling, 1 will be right siblings

public:
  leafNode();
  leafNode* getLeftSibling();//returns pointer to the left sibling
  leafNode* getRightSibling();
  void setLeftSibling(leafNode* node);
  void setRightSibling(leafNode* node);

};//End of Class Leaf Node

struct BPlusTree
{

  Node* root;//Root of the tree
  BPlusTree();
  Node* searchKey(unsigned int const key);
  Node* search(Node* node ,unsigned int const key);
  void insertKey(unsigned int const key);
  void insert(Node* node, unsigned int const key);
  void split(Node* node, unsigned int const key);
  void del(unsigned int key);
  void iteratePrint(Node* node, std::ofstream &buffer, int &index);
  void print();

};//end of BPlusTree struct


#endif //End of preprocessor directive
