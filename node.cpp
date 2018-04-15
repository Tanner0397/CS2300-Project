#include "node.h"

Node::Node()//Constructor
{
  static unsigned int m_id = 0;//Used for auto incrementing id
  id = m_id++;
  marked = false;
  for(unsigned int i = 0; i < TREE_ORDER; i++)
  {
    childNodes[i] = nullptr;
    parent = nullptr;
  }
}

Node::Node(const Node &node)
{
  keys = node.keys;
  for(unsigned int i = 0; i < TREE_ORDER; i++)
  {
    childNodes[i] = node.childNodes[i];
  }
  parent = node.parent;
}

unsigned int Node::getNumKeys()
{
  return keys.size();
}

unsigned int Node::getKey(int index)
{
  return keys[index];
}

unsigned int Node::getLastKey()
{
  if(!keys.empty())
    return keys.back();
}

bool Node::isLeafNode()
{
  if(dynamic_cast<leafNode*>(this))
  {
    return true;
  }
  return false;
}

Node* Node::getChild(int index)
{
  return childNodes[index];
}

Node* Node::getParent()
{
  return parent;
}

Node* Node::getLastChild()
{
  //1 keys -> 2nd child which is index at 1
  //2 keys -> 3rd child...
  for(int i = 3; i >= 0; i--)//4 children
  {
    if(childNodes[i] != nullptr)
      return childNodes[i];
  }
}

bool Node::isFull()
{
  if(keys.size() == TREE_ORDER-1)//Shoud be three
    return true;
  return false;
}

bool Node::isMemberOf(unsigned int key)
{
  for(unsigned int i = 0; i < keys.size(); i++)
    if(key == keys[i])
      return true;
  return false;
}

void Node::insertKey(unsigned int key)
{
  keys.push_back(key);
  std::sort(keys.begin(), keys.end());
}

std::vector<unsigned int> Node::getKeys()
{
  return keys;
}

void Node::deleteKeyIndex(int index)
{
  if(index < keys.size())
  {
    keys.erase(keys.begin()+index);
  }

}

bool Node::deleteKey(unsigned int const key)
{
  for(unsigned int i = 0; i < keys.size(); i++)
  {
    if(key == keys[i])
    {
      deleteKeyIndex(i);
      return true;
    }
  }
  return false;
}

void Node::clearAllKeys()
{
  keys.clear();
}

void Node::setChild(Node* node, int index)
{
  childNodes[index] = node;
}

void Node::setParent(Node* node)
{
  parent = node;
}

unsigned int Node::getID()
{
  return id;
}

void Node::mark()
{
  marked = true;
}

void Node::unmark()
{
  marked = false;
}

bool Node::isMarked()
{
  return marked;
}

std::string Node::print()
{
  std::string buffer;
  buffer += ("node" + std::to_string(id) + " [label = \"");
  for(unsigned int i = 0; i < TREE_ORDER-1; i++)
  {
    if(i < keys.size())
      buffer += "<f" + std::to_string(i) + "> |" + std::to_string(keys[i]) + "|";
    else
      buffer += "<f" + std::to_string(i) + "> | |";
  }
  buffer += "<f3> \"]\n";
  return buffer;
}

//----END NODE----
//----LEAF NODE----

leafNode::leafNode()
{
  Node();
  siblings[0] = nullptr;
  siblings[1] = nullptr;
}

leafNode* leafNode::getLeftSibling()
{
  return siblings[0];
}

leafNode* leafNode::getRightSibling()
{
  return siblings[1];
}

void leafNode::setLeftSibling(leafNode* node)
{
  siblings[0] = node;
}

void leafNode::setRightSibling(leafNode* node)
{
  siblings[1] = node;
}

//----END LEAF NODE----
