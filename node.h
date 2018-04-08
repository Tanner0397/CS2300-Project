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
  unsigned int id;//unique Id used for printing.
  bool marked;//Mark all the
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
  bool isMemberOf(unsigned int key);//if this key is a member of the node
  void insertKey(unsigned int const key);
  void deleteKeyIndex(int index);
  bool deleteKey(unsigned int const key);
  void clearAllKeys();
  void setChild(Node* node, int index);
  void setParent(Node* node);
  void setRoot(Node* node);
  std::string print();
  unsigned int getID();
  void mark();//For BFS
  void unmark();
  bool isMarked();
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
  Node* searchLeaf(Node* node ,unsigned int const key);
  Node* firstInstance(Node* node, unsigned int const);//this retuns the first node it finds with this key in it
  void insertKey(unsigned int const key);
  void insert(unsigned int const key);
  Node* split(Node* node, unsigned int const key);
  bool insertChild(Node* parent, Node* node);
  void removeChild(Node* parent, Node* node);
  unsigned int countKeys(Node* node);//counts the keys, testing use only
  void del(unsigned int const key);
  void redistrubute(Node* node, Node* sibling, unsigned int const key);
  void merge(Node* node, Node* sibling, unsigned int const key);
  void moveKey(Node* node, unsigned int const key);
  void outputNodes(Node* node, std::ofstream &buffer);
  void outputLinks(Node* node, std::ofstream &buffer);
  void outputSiblings(Node* node, std::ofstream &buffer);
  void print();

};//end of BPlusTree struct


#endif //End of preprocessor directive
