#ifndef NODE_H
#define NODE_H
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
  Node* getParent();//get the parent of the node
  /*Obtain the child at the specified index. 0: leftmost and 3: rightMost*/
  Node* getChild(int index);
  //Obtain a pointer to the last child of the node. Mostly used to find the last node of a tree/subtree
  Node* getLastChild();
  bool isLeafNode();//retursn true of this is a leaf node
  bool isFull();//returns tree if we are full on keys in a node
  bool isMemberOf(unsigned int key);//true if this key is a member of this node
  void insertKey(unsigned int const key);//insert a key into a node
  void deleteKeyIndex(int index);//Delete a key in the node at the index
  //Attempt to delete the exact key from node. Retursn true of successful, othersize it is false
  bool deleteKey(unsigned int const key);
  void clearAllKeys();//clears all the keys in this node
  //set node as this nodes child for index
  void setChild(Node* node, int index);
  //set the parent of this node to be node
  void setParent(Node* node);
  //prints out the current node with it's id. Formatted for graphviz
  std::string print();
  unsigned int getID();//get this nodes unique id
  void mark();//For In otder tree traversal
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

#endif //End of preprocessor directive
