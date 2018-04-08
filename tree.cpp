#include "node.h"

//----FRIEND FUNCTION----


//----END FRIEND FUNCTIONS----
//----NODE----

Node::Node()//Constructor
{
  static unsigned int m_id = 0;//Used for auto incrementing id
  id = m_id++;
  marked = false;
  for(unsigned int i = 0; i < TREE_ORDER; i++)
  {
    childNodes[i] = nullptr;
    parent = nullptr;
  }//end for loop
}//end node constructor

Node::Node(const Node &node)
{
  keys = node.keys;
  for(unsigned int i = 0; i < TREE_ORDER; i++)
  {
    childNodes[i] = node.childNodes[i];
  }//end for
  parent = node.parent;
}//end copy constructor

unsigned int Node::getNumKeys()
{
  return keys.size();
}//end getNumKeys method

unsigned int Node::getKey(int index)
{
  return keys[index];
}//end getKeys

unsigned int Node::getLastKey()
{
  if(!keys.empty())
    return keys.back();
}//end get last key meothod

bool Node::isLeafNode()
{
  if(dynamic_cast<leafNode*>(this))
  {
    return true;
  }
  return false;
}//end isLeafNode

Node* Node::getChild(int index)
{
  return childNodes[index];
}//end getChild

Node* Node::getParent()
{
  return parent;
}

bool Node::isFull()
{
  if(keys.size() == TREE_ORDER-1)//Shoud be three
    return true;
  return false;
}//end isFull method

bool Node::isMemberOf(unsigned int key)
{
  for(unsigned int i = 0; i < keys.size(); i++)
    if(key == keys[i])
      return true;
  return false;
}//end isMemberof function

void Node::insertKey(unsigned int key)
{
  keys.push_back(key);
  std::sort(keys.begin(), keys.end());
}//end insertionKey

std::vector<unsigned int> Node::getKeys()
{
  return keys;
}//end getKeys method

void Node::deleteKeyIndex(int index)
{
  if(index < keys.size())
  {
    keys.erase(keys.begin()+index);
  }//end if

}//end deleteKey method

bool Node::deleteKey(unsigned int const key)
{
  for(unsigned int i = 0; i < keys.size(); i++)
  {
    if(key == keys[i])
    {
      deleteKeyIndex(i);
      return true;
    }
  }//end for
  return false;
}//end end delete Key

void Node::clearAllKeys()
{
  keys.clear();
}

void Node::setChild(Node* node, int index)
{
  childNodes[index] = node;
}//end setChild moethod

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
  }//end for
  buffer += "<f3> \"]\n";
  return buffer;
}//end print method

//----END NODE----
//----LEAF NODE----

leafNode::leafNode()
{
  Node();
  siblings[0] = nullptr;
  siblings[1] = nullptr;
}//end leafNode constructor

leafNode* leafNode::getLeftSibling()
{
  return siblings[0];
}//end left get

leafNode* leafNode::getRightSibling()
{
  return siblings[1];
}//end Right get

void leafNode::setLeftSibling(leafNode* node)
{
  siblings[0] = node;
}//end left get

void leafNode::setRightSibling(leafNode* node)
{
  siblings[1] = node;
}//end Right get

//----END LEAF NODE----
//----B PLUS TREE----

BPlusTree::BPlusTree()
{
  root = new leafNode();//Starting Node is a leaf node!
}//end BPlusTree constructor

Node* BPlusTree::searchKey(unsigned int const key)
{
  return searchLeaf(root, key);
}//end searchKey method

Node* BPlusTree::searchLeaf(Node* node ,unsigned int const key)
{
  if(node->isLeafNode())
  {
    return node;
  }//this is the node that contains the key
  else
  {
    //std::cout << "TEST 4" << std::endl;
    //std::cout << key << std::endl;
    //std::cout << node->print() << std::endl;
    if(node->getNumKeys() == 1)//There is only 1 key in this node
    {
      //std::cout << "TEST 5" << std::endl;
      if(key <= node->getKey(0))
        return BPlusTree::searchLeaf(node->getChild(0), key);//The left most child Node
      else
        return BPlusTree::searchLeaf(node->getChild(1), key);
    }//end if numKeys == 1
    else if(node->getNumKeys() == 2)//There are 2 keys in the node
    {
      //std::cout << "TEST 6" << std::endl;
      if(key <= node->getKey(0))
        return BPlusTree::searchLeaf(node->getChild(0), key);//goto left most child
      else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
        return BPlusTree::searchLeaf(node->getChild(1), key);//goto middle child
      else//The key is greater than all the keys in the node
        return BPlusTree::searchLeaf(node->getChild(2), key);//goto right most child
    }//end if numKeys == 2
    else if(node->getNumKeys() == 3)
    {
      //std::cout << "TEST 7" << std::endl;
      if(key <= node->getKey(0))
        return BPlusTree::searchLeaf(node->getChild(0), key);//goto left most child
      else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
        return BPlusTree::searchLeaf(node->getChild(1), key);//goto second child
      else if(key > node->getKey(1) && key <= node->getKey(2))//keys[1] < key <= keys[2]
        return BPlusTree::searchLeaf(node->getChild(2), key);//goto third child
      else//The key is greater than all the keys in the node
        return BPlusTree::searchLeaf(node->getChild(3), key);//goto right most child
    }//end else numKeys == 3
  }//end else
}//end search method

Node* BPlusTree::firstInstance(Node* node, unsigned int key)
{
  if(node->isMemberOf(key))
    return node;
  std::cout << node->print() << std::endl;

  if(node->getNumKeys() == 1)//There is only 1 key in this node
  {
      //std::cout << "TEST 5" << std::endl;
    if(key <= node->getKey(0))
      return firstInstance(node->getChild(0), key);//The left most child Node
    else
      return firstInstance(node->getChild(1), key);
  }//end if numKeys == 1
  else if(node->getNumKeys() == 2)//There are 2 keys in the node
  {
    //std::cout << "TEST 6" << std::endl;
    if(key <= node->getKey(0))
      return firstInstance(node->getChild(0), key);//goto left most child
    else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
        return firstInstance(node->getChild(1), key);//goto middle child
    else//The key is greater than all the keys in the node
      return firstInstance(node->getChild(2), key);//goto right most child
  }//end if numKeys == 2
  else if(node->getNumKeys() == 3)
  {
    //std::cout << "TEST 7" << std::endl;
    if(key <= node->getKey(0))
      return firstInstance(node->getChild(0), key);//goto left most child
    else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
      return firstInstance(node->getChild(1), key);//goto second child
    else if(key > node->getKey(1) && key <= node->getKey(2))//keys[1] < key <= keys[2]
      return firstInstance(node->getChild(2), key);//goto third child
    else//The key is greater than all the keys in the node
      return firstInstance(node->getChild(3), key);//goto right most child
  }//end else numKeys == 3

}//end firstSintance method

Node* BPlusTree::split(Node* node, unsigned int const key)
{
  std::vector<unsigned int> copy = node->getKeys();//get copy of keys
  copy.push_back(key);
  std::sort(copy.begin(), copy.end());//Sort the keys
  unsigned int index = std::find(copy.begin(), copy.end(), key) - copy.begin();

  /*copy has all the keys values + 1 extra node. The left two nodes will
  be put in the left child and the 2 right most nodes will be put in the right child
  The second child from the lest will be copied into the parent node*/

  //Create a new leaf node and move half of the keys to it
  if(node->isLeafNode())
  {
    Node* parent = node->getParent();
    leafNode* newLeaf = new leafNode();
    newLeaf->setLeftSibling(dynamic_cast<leafNode*>(node));//this node is the left sibling of the node
    newLeaf->setRightSibling(dynamic_cast<leafNode*>(node)->getRightSibling());//right sibling of the new leaf is old right sibling of the node
    dynamic_cast<leafNode*>(node)->setRightSibling(newLeaf);//right sibling of the node is the new leaf
    if(newLeaf->getRightSibling() != nullptr)//if the right siblings isnt null, set the right siblings left siblings as new leaf
      newLeaf->getRightSibling()->setLeftSibling(newLeaf);
    newLeaf->insertKey(copy[2]);
    newLeaf->insertKey(copy[3]);//Insert the last two elements of the keys
    newLeaf->setParent(parent);//set parent of new sibling
    node->clearAllKeys();
    node->insertKey(copy[0]);//this should be the first key of the nodes
    node->insertKey(copy[1]);//insert the key being split, the reduncant entry
    if(node != root)//If the parent of the node isn't full
    {
      if(!parent->isFull())//
      {
        parent->insertKey(copy[1]);//insert the second key of the copy vector
        insertChild(parent, newLeaf);
      }
      else
      {
        Node* result = split(parent, copy[1]);//This will be an internal node
        newLeaf->setParent(result);
        insertChild(result, newLeaf);
      }
    }//end if
    else if(node == root)
    {
      Node* newRoot = new Node();
      newRoot->insertKey(copy[1]);//insert second key
      newRoot->setChild(node, 0);//node is leftChild
      newRoot->setChild(newLeaf, 1);//newLeaf is right child
      node->setParent(newRoot);
      newLeaf->setParent(newRoot);
      root = newRoot;//Set the new root
    }//end else if root
    return nullptr;
  }//end ifLeaf
  else//This is an internal node
  {
    Node* parent = node->getParent();
    Node* newNode = new Node();
    newNode->insertKey(copy[2]);
    newNode->insertKey(copy[3]);//Give newNode the keys it needs
    newNode->setParent(parent);
    node->clearAllKeys();
    node->insertKey(copy[0]);
    if(index < 1)
    {
      newNode->setChild(node->getChild(1), 0);
      newNode->setChild(node->getChild(2), 1);
      newNode->setChild(node->getChild(3), 2);
      newNode->getChild(0)->setParent(newNode);
      newNode->getChild(1)->setParent(newNode);
      newNode->getChild(2)->setParent(newNode);//set children parent nodes
      node->setChild(nullptr, 1);
      node->setChild(nullptr, 2);
      node->setChild(nullptr, 3);//clear children that moved
    }//end if index is 0
    else//else the index places is one of the last two keys
    {
      newNode->setChild(node->getChild(2), 0);
      newNode->setChild(node->getChild(3), 1);
      newNode->getChild(0)->setParent(newNode);
      newNode->getChild(1)->setParent(newNode);
      node->setChild(nullptr, 2);
      node->setChild(nullptr, 3);//clear children that moved
    }//end child setting
    if(root != node)//if this is not the root
    {
      if(!parent->isFull())
      {
        parent->insertKey(copy[1]);//insert the second key into the parent now
        insertChild(parent, newNode);
        if(index < 1)
          return node;
        return newNode;
      }//end if the parent is not full
      else//the parent is actually full
      {
        //split the parent
        Node* result = split(parent, copy[1]);
        insertChild(result, newNode);
        newNode->setParent(result);
        if(index < 1)
          return node;
        return newNode;
      }//end if the parent is full
    }//end of not root
    else//this is the root
    {
      Node* newRoot = new Node();
      newRoot->insertKey(copy[1]);
      newRoot->setChild(node, 0);//node will be the left child
      newRoot->setChild(newNode, 1);//newNode has to the the second child
      node->setParent(newRoot);
      newNode->setParent(newRoot);
      root = newRoot;
      if(index < 1)
        return node;
      return newNode;
    }
  }//end else internal node

}//end split method


bool BPlusTree::insertChild(Node* parent, Node* node)
{
  unsigned int last = node->getLastKey();
  //if we're using the arrange children method the node will have 2 or 3 keys, not one
  //if a keys size of 1 is encounters, that node was split.
  if(parent->getNumKeys() == 1)
  {
    //If this node has only 1 key, that means it was actually split. This child node may or maynot be the child
    if(parent->getChild(1) != nullptr && last < parent->getChild(1)->getLastKey())//if this is true, then this is a better child for the node!
    {
      Node* temp = parent->getChild(1);
      parent->setChild(node, 1);
      //Now I need to find a way to find the node this is suppose to be inserted into
      Node* newParent = searchLeaf(root, temp->getLastKey())->getParent();//find the parent of the child swapped
      insertChild(newParent, temp);
      return true;
    }
    else if(parent->getChild(1) == nullptr)
    {
      parent->setChild(node, 1);
      return true;
    }
    return false;
  }//end if key size is equal to 1
  if(parent->getNumKeys() == 2)//this node has 2 keys
  {
    //Node* temp;//used to swap
    if(last <= parent->getKey(0))
    {/*Since the last ket of node is less than or equal to the last node of the first
      key, the first key must be the new element that was inserted into the node*/

      //shift children
      parent->setChild(parent->getChild(1), 2);
      parent->setChild(parent->getChild(0), 1);
      parent->setChild(node, 0);
    }//end if last key of node is less thatn or equal to the first key of the node
    else if(parent->getKey(0) < last && last <= parent->getKey(1))
    {/*here the second key is the new key, so the last child for 2 nodes is new*/
      parent->setChild(parent->getChild(1), 2);
      parent->setChild(node, 1);
    }//if the last key of node is greater than keys[0] but less than or equal to keys[1]
    else
    {
      parent->setChild(node, 2);
    }
  }//end if
  else if(parent->getNumKeys() == 3)//numKeys == 3
  {
    if(last <= parent->getKey(0))
    {
      parent->setChild(parent->getChild(2), 3);
      parent->setChild(parent->getChild(1), 2);
      parent->setChild(parent->getChild(0), 1);
      parent->setChild(node, 0);
    }//end f
    else if(parent->getKey(0) < last && last <= parent->getKey(1))
    {
      parent->setChild(parent->getChild(2), 3);
      parent->setChild(parent->getChild(1), 2);
      parent->setChild(node, 1);
    }//end else if
    else if(parent->getKey(1) < last && last <= parent->getKey(2))
    {
      parent->setChild(parent->getChild(2), 3);
      parent->setChild(node, 2);
    }
    else
    {
      parent->setChild(node, 3);
    }
  }//end else
  return true;
}//end function

void BPlusTree::removeChild(Node* parent, Node* node)
{

  if(parent->getNumKeys() == 2)
  {
    if(node == parent->getChild(0))//node is the first
    {
      parent->deleteKeyIndex(0);//remove the first key in the parent
      parent->setChild(parent->getChild(1), 0);//shift all 2 remaining children
      parent->setChild(parent->getChild(2), 1);
      parent->setChild(nullptr, 2);//pointer has moved, delete old one
    }
    else if(node == parent->getChild(1))//second
    {
      parent->deleteKeyIndex(1);//remove the second key
      parent->setChild(parent->getChild(2), 1);//shirt only 1
      parent->setChild(nullptr, 2);
    }
    else if(node == parent->getChild(1))//second again
    {
      parent->deleteKeyIndex(LAST_KEY-1);//third, but it's the last as well
      parent->setChild(nullptr, 2);
    }
    else//We have an error here, node isn't the child of parent at all!
    {
      throw "Oops";
    }//end else
  }//end if the parent has 3 children
  else if(parent->getNumKeys() == 3)
  {
    if(node == parent->getChild(0))
    {
      parent->deleteKeyIndex(0);//remove first key
      parent->setChild(parent->getChild(1), 0);//shift all 2 remaining children
      parent->setChild(parent->getChild(2), 1);
      parent->setChild(parent->getChild(3), 2);
      parent->setChild(nullptr, 3);
    }//end if
    else if(node == parent->getChild(1))
    {
      parent->deleteKeyIndex(1);//second
      parent->setChild(parent->getChild(2), 1);
      parent->setChild(parent->getChild(3), 2);
      parent->setChild(nullptr, 3);
    }//end else if
    else if(node == parent->getChild(2))
    {
      std::cout << "HEY "<< parent->getKey(2) << std::endl;
      parent->deleteKeyIndex(LAST_KEY);//remove last key
      parent->setChild(parent->getChild(3), 2);
      parent->setChild(nullptr, 3);
    }
    else if(node == parent->getChild(3))
    {
      std::cout << "HEYYOO "<< parent->getKey(2) << std::endl;
      parent->deleteKeyIndex(LAST_KEY);//remove the last key!
      parent->setChild(nullptr, 3);
    }
    else//We have an error here, node isn't the child of parent at all!
    {
      throw "Oops";
    }//end else
  }//end if this node has all four children
}//end function removeChild

void BPlusTree::insert(unsigned int const key)
{
  Node* result = BPlusTree::searchKey(key);
  if(!result->isFull())
  {
    result->Node::insertKey(key);
  }//end if node is full
  else//the node is full
  {
    BPlusTree::split(result, key);//This also inserts the key, but with the split.
  }//end else
}//end insert method

void BPlusTree::outputNodes(Node* node, std::ofstream &buffer)
{
  if(node == nullptr)
    return;
  outputNodes(node->getChild(0), buffer);
  outputNodes(node->getChild(1), buffer);
  if(!node->isMarked())
    buffer << node->print();
  node->mark();
  outputNodes(node->getChild(2), buffer);
  outputNodes(node->getChild(3), buffer);

}//end print method


void BPlusTree::outputLinks(Node* node, std::ofstream &buffer)
{
  if(node==nullptr)
    return;
  outputLinks(node->getChild(0),buffer);
  outputLinks(node->getChild(1),buffer);
  //LINK
  node->unmark();
  if(node->getChild(0) != nullptr)
    buffer << "node" << node->getID() << ":f0 -> node" << node->getChild(0)->getID() << '\n';
  if(node->getChild(1) != nullptr)
    buffer << "node" << node->getID() << ":f1 -> node" << node->getChild(1)->getID() << '\n';
  if(node->getChild(2) != nullptr)
    buffer << "node" << node->getID() << ":f2 -> node" << node->getChild(2)->getID() << '\n';
  if(node->getChild(3) != nullptr)
    buffer << "node" << node->getID() << ":f3 -> node" << node->getChild(3)->getID() << '\n';
  outputLinks(node->getChild(2),buffer);
  outputLinks(node->getChild(3),buffer);
}

void BPlusTree::outputSiblings(Node* node, std::ofstream &buffer)
{
  if(node==nullptr)
    return;
  outputSiblings(node->getChild(0),buffer);
  outputSiblings(node->getChild(1),buffer);
  //LINK
  node->unmark();
  if(node->isLeafNode())
  {
    leafNode* leaf = dynamic_cast<leafNode*>(node);
    leafNode* left = leaf->getLeftSibling();
    leafNode* right = leaf->getRightSibling();
    if(left != nullptr)
      buffer << "node" << left->getID() << ":f3->node" << node->getID() << ":f0" << std::endl;
  }
  outputSiblings(node->getChild(2),buffer);
  outputSiblings(node->getChild(3),buffer);
}

void BPlusTree::print()
{
  int index = 0;
  std::ofstream buffer;
  buffer.open("output.gv");
  buffer << "digraph {\n node [ shape = record]\n";
  //buffer << root->print(index) << std::endl;
  outputNodes(root, buffer);
  outputLinks(root, buffer);
  //outputSiblings(root, buffer);
  buffer << "}";
}//end print method

unsigned int BPlusTree::countKeys(Node* node)//For testing
{
  if(!node->isLeafNode())
    return countKeys(node->getChild(0));
  else
  {
    leafNode* leaf = dynamic_cast<leafNode*>(node);
    if(leaf->getRightSibling() != nullptr)
      return countKeys(leaf->getRightSibling())+leaf->getNumKeys();
    else
      return leaf->getNumKeys();
  }//end else
}
//works for now, if internal nodes will have multiple instances of keys this is not good enough.
void BPlusTree::moveKey(Node* node, unsigned int const key)
{
  Node* container = firstInstance(root, key);
  //if this node is the last child, it actually isnt in the parent. of that node
  node->deleteKey(key);
  container->deleteKey(key);//remove that old key
  unsigned int newKey = node->getLastKey();//the new key
  container->insertKey(newKey);
  return;
}//end moveKey method

void BPlusTree::redistrubute(Node* node, Node* sibling, unsigned int const key)
{//node will have 2 keys
  std::cout << "NODE: " << node->print() << std::endl;
  std::cout << "SIBLING: " << sibling->print() << std::endl;
  if(node->isLeafNode())//this is a leaf node, so sibling is also a leaf node
  {
    bool result = false;
    unsigned int oldLastKey = node->getLastKey();
    leafNode* leaf = dynamic_cast<leafNode*>(node);
    leafNode* leafSibling = dynamic_cast<leafNode*>(sibling);
    unsigned int newKey = leafSibling->getKey(0);//get the first key, implying this is a right sibling
    if(leafSibling == leaf->getLeftSibling())//change to last key if the this is the left sibling
      newKey = leafSibling->getLastKey();
    Node* container = firstInstance(root, key);
    std::cout << newKey << std::endl;
    node->deleteKey(key);
    result = container->deleteKey(key);//wont delete if it actually isn't there
    node->insertKey(newKey);
    if(result)//if the key was in an internal node
      container->insertKey(node->getLastKey());//insert the last key of the node
    else//this wasn't in in internal node, however an internal node could change!
    {//here container == node, since it wasn't in an internal node so the first instance is the leaf!
      unsigned int newLastKey = node->getLastKey();//new last key in node, since it chould change
      if(oldLastKey != newLastKey)
      {
        node->getParent()->deleteKey(oldLastKey);//remove the old last ky from the parent
        node->getParent()->insertKey(newLastKey);//add the new last key to the parent!
      }//edn keys no longer match
    }
    if(leafSibling == leaf->getLeftSibling())//we tood the last key, so we need to remove it from an internal node
    {
      moveKey(leafSibling, newKey);//this should remove the key from the sibling and and whatever internal node it was in
    }
    else
      leafSibling->deleteKey(newKey);//just remove that key since it's not in any internal nodes, since it was from the right.
  }//end if this is a leaf node
  else//this is an internal node
  {

  }//end else
}//end redistrubute method

void BPlusTree::merge(Node* node, Node* sibling, unsigned int const key)
{
  if(node->isLeafNode())//this is a leaf, and so sibling is also a leaf
  {
    leafNode* leaf = dynamic_cast<leafNode*>(node);
    leafNode* leafSibling = dynamic_cast<leafNode*>(sibling);
    Node* parent = leaf->getParent();
    unsigned int oldLastKey = node->getLastKey();
    bool result = false;
    if(parent->getNumKeys() >= 2)//if the parent of this node had more than 2 children, we have no problem
    {
      Node* container = firstInstance(root, key);//gets the first instance
      node->deleteKey(key);//delete the key
      result = container->deleteKey(key);
      //vectors
      std::cout << "YOO" << std::endl;
      std::vector<unsigned int> newKeys = sibling->getKeys();
      std::cout << "YOO" << std::endl;

      //node->clearAllKeys();//clear all the keys for node
      for(unsigned int i = 0; i < newKeys.size(); i++)
      {
       node->insertKey(newKeys[i]);//insert all the newKeys into the recently emptied node
      }//end for loop
      unsigned int newKey = node->getLastKey();//This is the new key that is refrenced
      if(result)//if the node deleted was in an internal node
        container->insertKey(newKey);//insert the new key into the node that lost it's record
      else
      {
        unsigned int newLastKey = node->getLastKey();//new last key in node, since it chould change
        if(oldLastKey != newLastKey)
        {
          node->getParent()->deleteKey(oldLastKey);//remove the old last ky from the parent
          node->getParent()->insertKey(newLastKey);//add the new last key to the parent!
        }//edn keys no longer match
      }

      //rearrange the siblings
      if(leafSibling == leaf->getLeftSibling())
      {
        leaf->setLeftSibling(leafSibling->getLeftSibling());
        if(leaf->getLeftSibling() != nullptr)
          leaf->getLeftSibling()->setRightSibling(leaf);
      }//end this is right siblings
      else if(leafSibling == leaf->getRightSibling())
      {
        leaf->setRightSibling(leafSibling->getRightSibling());
        if(leaf->getRightSibling() != nullptr)
          leaf->getRightSibling()->setLeftSibling(leaf);
      }//end this is left siblings

      //New we msut rearrange the children of the parent.
      if(parent == sibling->getParent())
      {
        removeChild(parent, sibling);
      }//end if parents are the same
      else//the two nodes don't have the same parent, so they hopped boundries
      {

      }
    }//end if
  }//end is leaf
  else//this is an internal node
  {

  }//end else
}//end merge method

void BPlusTree::del(unsigned int const key)
{
  Node* result = searchKey(key);
  if(result->getNumKeys() == 3)//node has to be full
  {
    if(key == result->getLastKey())
    {
      moveKey(result, key);//this will deal with the deletion of the key in this node
    }//this is the last key of the node, so it has an entry in an internal node
    else//not the last key so this isn't really a problem
    {
      result->deleteKey(key);//delete that key
    }//end else
  }//end if node is at least half full
  else//node has only one key
  {
    //try and see if you can redistrubute the nodes
    //---------------------------------------------------------------
    bool accepted = false;
    leafNode* leaf = dynamic_cast<leafNode*>(result);
    leafNode* leftSibling = leaf->getLeftSibling();
    leafNode* rightSibling = leaf->getRightSibling();
    if(rightSibling != nullptr)//avoid setFault
    {
      if(rightSibling->getNumKeys() == 3)
      {
        accepted = true;//we can redistrubute
        redistrubute(result, rightSibling, key);
      }//end if
    }//end if rightSibling exist
    if(leftSibling != nullptr && !accepted)//avoid segFault
    {
      if(leftSibling->getNumKeys() == 3)
      {
        accepted = true;//we can redistrubute
        redistrubute(result, leftSibling, key);
      }
    }//end else if left sibling exist
    //-----------------------------------------------------------------------
    //This isn't the root and we didn't redistrubute, so we must merge
    if(!accepted && result != root)
    {
      if(rightSibling != nullptr)
      {
        accepted = true;
        merge(result, rightSibling, key);
      }//if the right sibling exist
      if(leftSibling != nullptr && !accepted)
      {
        accepted = true;
        merge(result, leftSibling, key);
      }//end if the left child exist
    }//end if not accpted and this isn't the root
    else if(!accepted && result == root)//this was the root all along, we can just remove the key since we can't merge
    {

    }//end else if
  }//end else statment
}//end delete method

//----END B PLUS TREE----
