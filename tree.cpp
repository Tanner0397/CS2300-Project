#include <typeinfo>
#include "node.h"

//----NODE----

Node::Node()//Constructor
{
  numKeys = 0;//First its empty
  for(unsigned int i = 0; i < TREE_ORDER; i++)
  {
    childNodes[i] = nullptr;
  }//end for loop
}//end node constructor

unsigned int Node::getNumKeys()
{
  return numKeys;
}//end getNumKeys method

unsigned int Node::getKey(int index)
{
  return keys[index];
}//end getKeys

bool Node::isLeafNode()
{
  if(typeid(*this) == typeid(leafNode))
    return true;
  return false;
}//end isLeafNode

Node* Node::getChild(int index)
{
  return childNodes[index];
}//end getChild

//----END NODE----
//----LEAF NODE----

leafNode::leafNode()
{
  Node();
  siblings[0] = nullptr;
  siblings[1] = nullptr;
}//end leafNode constructor

//----END LEAF NODE----
//----B PLUS TREE----

BPlusTree::BPlusTree()
{
  root = new leafNode();//Starting Node is a leaf node!
}//end BPlusTree constructor

Node* BPlusTree::searchKey(unsigned int const key)
{
  return search(root, key);
}//end searchKey method

Node* BPlusTree::search(Node* node ,unsigned int const key)
{
  if(node->isLeafNode())//this is the node that contains the key
    return node;
  else
  {
    if(node->getNumKeys() == 1)//There is only 1 key in this node
    {
      if(key <= node->getKey(0))
        return BPlusTree::search(node->getChild(0), key);//The left most child Node
      else
        BPlusTree::search(node->getChild(1), key);
    }//end if numKeys == 1
    else if(node->getNumKeys() == 2)//There are 2 keys in the node
    {
      if(key <= node->getKey(0))
        return BPlusTree::search(node->getChild(0), key);//goto left most child
      else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
        return BPlusTree::search(node->getChild(1), key);//goto middle child
      else//The key is greater than all the keys in the node
        return BPlusTree::search(node->getChild(2), key);//goto right most child
    }//end if numKeys == 2
    else if(node->getNumKeys() == 3)
    {
      if(key <= node->getKey(0))
        return BPlusTree::search(node->getChild(0), key);//goto left most child
      else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
        return BPlusTree::search(node->getChild(1), key);//goto second child
      else if(key > node->getKey(1) && key <= node->getKey(2))//keys[1] < key <= keys[2]
        return BPlusTree::search(node->getChild(2), key);//goto third child
      else//The key is greater than all the keys in the node
        return BPlusTree::search(node->getChild(3), key);//goto right most child
    }//end else numKeys == 3
  }//end else
}//end search method

void BPlusTree::insert(unsigned int key)
{

}//end insert method

//----END B PLUS TREE----
