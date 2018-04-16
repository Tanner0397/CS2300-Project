#include "node.h"
#include "tree.h"

unsigned int BPlusTree::print_id = 0;//initialize static member
//----B PLUS TREE----

BPlusTree::BPlusTree()
{
  print_id = 0;
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
    if(node->getNumKeys() == 1)//There is only 1 key in this node
    {
      if(key <= node->getKey(0))
        return BPlusTree::searchLeaf(node->getChild(0), key);//The left most child Node
      else
        return BPlusTree::searchLeaf(node->getChild(1), key);
    }//end if numKeys == 1
    else if(node->getNumKeys() == 2)//There are 2 keys in the node
    {
      if(key <= node->getKey(0))
        return BPlusTree::searchLeaf(node->getChild(0), key);//goto left most child
      else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
        return BPlusTree::searchLeaf(node->getChild(1), key);//goto middle child
      else//The key is greater than all the keys in the node
        return BPlusTree::searchLeaf(node->getChild(2), key);//goto right most child
    }//end if numKeys == 2
    else if(node->getNumKeys() == 3)
    {
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
}

Node* BPlusTree::firstInstance(Node* node, unsigned int key)
{
  if(node->isMemberOf(key))
    return node;
  else if(node->isLeafNode())
    return nullptr;


  if(node->getNumKeys() == 1)//There is only 1 key in this node
  {
    if(key <= node->getKey(0))
      return firstInstance(node->getChild(0), key);//The left most child Node
    else
      return firstInstance(node->getChild(1), key);
  }//end if numKeys == 1
  else if(node->getNumKeys() == 2)//There are 2 keys in the node
  {
    if(key <= node->getKey(0))
      return firstInstance(node->getChild(0), key);//goto left most child
    else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
        return firstInstance(node->getChild(1), key);//goto middle child
    else//The key is greater than all the keys in the node
      return firstInstance(node->getChild(2), key);//goto right most child
  }//end if numKeys == 2
  else if(node->getNumKeys() == 3)
  {
    if(key <= node->getKey(0))
      return firstInstance(node->getChild(0), key);//goto left most child
    else if(key > node->getKey(0) && key <= node->getKey(1))//keys[0] < key <= keys[1]
      return firstInstance(node->getChild(1), key);//goto second child
    else if(key > node->getKey(1) && key <= node->getKey(2))//keys[1] < key <= keys[2]
      return firstInstance(node->getChild(2), key);//goto third child
    else//The key is greater than all the keys in the node
      return firstInstance(node->getChild(3), key);//goto right most child
  }//end else numKeys == 3
}

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
    //this node is the left sibling of the node
    newLeaf->setLeftSibling(dynamic_cast<leafNode*>(node));
    //right sibling of the new leaf is old right sibling of the node
    newLeaf->setRightSibling(dynamic_cast<leafNode*>(node)->getRightSibling());
    //right sibling of the node is the new leaf
    dynamic_cast<leafNode*>(node)->setRightSibling(newLeaf);
    //if the right siblings isnt null, set the right siblings left siblings as new leaf
    if(newLeaf->getRightSibling() != nullptr)
      newLeaf->getRightSibling()->setLeftSibling(newLeaf);
    newLeaf->insertKey(copy[2]);
    newLeaf->insertKey(copy[3]);//Insert the last two elements of the keys
    newLeaf->setParent(parent);//set parent of new sibling
    node->clearAllKeys();
    node->insertKey(copy[0]);//this should be the first key of the nodes
    node->insertKey(copy[1]);//insert the key being split, the redundant entry
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
      if(!parent->isFull())//no problems, we can insert the key and the child
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
    else//this is the root, so we need to make a node node
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
}


void BPlusTree::insertChild(Node* parent, Node* node)
{
  unsigned int last = node->getLastKey();
  //if we're using the arrange children method the node will have 2 or 3 keys, not one
  //if a keys size of 1 is encounters, that node was split.
  if(parent->getNumKeys() == 1)
  {
    //If this node has only 1 key, that means it was actually split.
    //This child node may or may not be the child
    //if this is true, then this is a better child for the node!
    if(parent->getChild(1) != nullptr && last < parent->getChild(1)->getLastKey())
    {
      Node* temp = parent->getChild(1);
      parent->setChild(node, 1);
      Node* newParent = searchLeaf(root, temp->getLastKey())->getParent();
      insertChild(newParent, temp);
    }
    else if(parent->getChild(1) == nullptr)
    {
      parent->setChild(node, 1);
    }
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
}

void BPlusTree::removeChild(Node* parent, Node* node)
{

  if(parent->getNumKeys() == 1)
  {//This in particular whoudl only be executed when merging with some node
    if(node == parent->getChild(0))
    {
      parent->setChild(parent->getChild(1), 0);
      parent->setChild(nullptr, 1);
    }//end if
    else if(node == parent->getChild(1))
    {//cant delete the key
      parent->setChild(nullptr, 1);
    }
  }//if ther is only one key
  else if(parent->getNumKeys() == 2)
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
      parent->setChild(parent->getChild(2), 1);//shift only 1
      parent->setChild(nullptr, 2);
    }
    else if(node == parent->getChild(2))//second again
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
      parent->deleteKeyIndex(LAST_KEY);//remove last key
      parent->setChild(parent->getChild(3), 2);
      parent->setChild(nullptr, 3);
    }
    else if(node == parent->getChild(3))
    {
      parent->deleteKeyIndex(LAST_KEY);//remove the last key!
      parent->setChild(nullptr, 3);
    }
    else//We have an error here, node isn't the child of parent at all!
    {
      throw "Oops";
    }//end else
  }//end if this node has all four children
}

//Returns nullptr if the root or has no right sibling
Node* BPlusTree::findRightSibling(Node* node)
{
  if(node != root)//this node has to have a sibling then
  {
    Node* parent = node->getParent();
    if(node == parent->getChild(0))
      return parent->getChild(1);
    else if(node == parent->getChild(1))
      return parent->getChild(2);
    else if(node == parent->getChild(2))
      return parent->getChild(3);
    else if(node == parent->getChild(3))
      return nullptr;
  }//end if
  else
    return nullptr;
}//end findSibling funciton

Node* BPlusTree::findLeftSibling(Node* node)
{
  if(node != root)//this node has to have a sibling then
  {
    Node* parent = node->getParent();
    if(node == parent->getChild(0))
      return nullptr;
    else if(node == parent->getChild(1))
      return parent->getChild(0);
    else if(node == parent->getChild(2))
      return parent->getChild(1);
    else if(node == parent->getChild(3))
      return parent->getChild(2);
  }//end if
  else
    return nullptr;
}//end findSibling funciton

Node* BPlusTree::getLastNode(Node* node)
{
  if(node->isLeafNode())
    return node;
  return getLastNode(node->getLastChild());
}//end getLastNode

void BPlusTree::insert(unsigned int const key)
{
  Node* result = BPlusTree::searchKey(key);
  if(result->isMemberOf(key))
  {
    std::cout << "Key: " << key << " already exist. Ignoring insertion operation." << std::endl;
    return;
  }
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
  std::string output = "";
  output.append("dots/output");
  output.append(std::to_string(BPlusTree::print_id));
  output.append(".dot");
  buffer.open(output.c_str());
  buffer << "digraph {\n node [ shape = record]\n";
  //buffer << root->print(index) << std::endl;
  outputNodes(root, buffer);
  outputLinks(root, buffer);
  //outputSiblings(root, buffer);
  buffer << "}";
  print_id++;
}//end print method
//works for now, if internal nodes will have multiple instances of keys this is not good enough.
void BPlusTree::moveKey(Node* node, unsigned int const key)
{
  Node* container = firstInstance(root, key);
  //if this node is the last child, it actually isn't in the parent. of that node
  node->deleteKey(key);
  container->deleteKey(key);//remove that old key
  unsigned int newKey = node->getLastKey();//the new key
  container->insertKey(newKey);
  return;
}

void BPlusTree::redistribute(Node* node, Node* sibling, unsigned int const key)
{//node will have 2 keys
  if(node->isLeafNode())//this is a leaf node, so sibling is also a leaf node
  {
    bool result = false;
    unsigned int oldLastKey = node->getLastKey();
    unsigned int newKey = sibling->getKey(0);//get the first key, implying this is a right sibling
    leafNode* leaf = dynamic_cast<leafNode*>(node);
    leafNode* leafSibling = dynamic_cast<leafNode*>(sibling);
    if(leafSibling == leaf->getLeftSibling())//change to last key if the this is the left sibling
      newKey = leafSibling->getLastKey();
    Node* container = firstInstance(root, key);
    node->deleteKey(key);
    result = container->deleteKey(key);//wont delete if it actually isn't there
    node->insertKey(newKey);
    if(result)//if the key was in an internal node
      container->insertKey(node->getLastKey());//insert the last key of the node
    else//this wasn't in in internal node, however an internal node could change!
    {//here container == node, since it wasn't in an internal node so the first instance is the leaf!
      unsigned int newLastKey = node->getLastKey();//new last key in node, since it could change
      if(oldLastKey != newLastKey)
      {
        if(node != node->getParent()->getLastChild())//if this isn't the last child
        {
          node->getParent()->deleteKey(oldLastKey);//remove the old last key from the parent
          node->getParent()->insertKey(newLastKey);//add the new last key to the parent!
        }//end if
        else//this is the last child, so replace the key in the internal node that contains the oldLastKey
        {
          container = firstInstance(root, oldLastKey);
          container->deleteKey(oldLastKey);
          container->insertKey(newLastKey);
        }//end else
      }//end keys no longer match
    }
    if(leafSibling == leaf->getLeftSibling())//we took the last key, so we need to remove it from an internal node
    {
      moveKey(leafSibling, newKey);//this should remove the key from the sibling and and whatever internal node it was in
    }
    else
      leafSibling->deleteKey(newKey);//just remove that key since it's not in any internal nodes, since it was from the right.
  }//end if this is a leaf node
  else//this is an internal node
  {
    Node* parent = node->getParent();
    Node* movedChild = sibling->getChild(0);

    Node* last_node_node = getLastNode(node);
    Node* last_node_moved = getLastNode(movedChild);

    unsigned int node_last_key = last_node_node->getLastKey();
    unsigned int new_last_key = last_node_moved->getLastKey();

    if(sibling == findRightSibling(node))//we're getting stuff from the right
    {
      removeChild(sibling, movedChild);
      node->setChild(movedChild, 1);
      movedChild->setParent(node);
      parent->deleteKey(node_last_key);
      parent->insertKey(new_last_key);
    }
    else//we're getting stuff from the left
    {
      unsigned int first_key = getLastNode(sibling)->getLastKey();
      movedChild = sibling->getLastChild();
      unsigned int sibling_last_key = getLastNode(sibling)->getLastKey();
      new_last_key = last_node_moved->getLastKey();
      node_last_key = getLastNode(sibling)->getLastKey();
      node->deleteKeyIndex(0);
      node->insertKey(first_key);
      removeChild(sibling, movedChild);//remove the child
      unsigned int new_last_key_sibling = getLastNode(sibling)->getLastKey();
      node->setChild(node->getChild(0), 1);
      movedChild->setParent(node);
      node->setChild(movedChild, 0);
      parent->deleteKey(node_last_key);
      parent->insertKey(new_last_key_sibling);

    }
  }
}

void BPlusTree::merge(Node* node, Node* sibling, unsigned int const key, bool leftMerge)
{
  bool mergeRoot = false;
  std::vector<unsigned int> copy = sibling->getKeys();
  Node* container = firstInstance(root, node->getLastKey());
  Node* parent = node->getParent();
  if(parent->getNumKeys() < 2)
  {
    Node* right = findRightSibling(parent);
    Node* left = findLeftSibling(parent);
    if(right != nullptr && right->getNumKeys() >= 2)
      redistribute(parent, right, key);
    else if(left  != nullptr && left->getNumKeys() >= 2)
      redistribute(parent, left, key);
    else//we didn't distrubute
    {
      if(right != nullptr)
        merge(parent, right, key, false);//merge it to the right
      else if(left != nullptr)
        merge(parent, left, key, true);//merge parent with it's left sibling
      else
        mergeRoot = true;//Node is going to be the new root when done merging
    }//end else
  }//end if the parent doesn't have enough keys to survive
  //We have now merged all the nodes that need to be merged. So we can delete a node.
  if(node->isLeafNode())//We are merging two leaf nodes together
  {
    parent = node->getParent();//re obtain parent
    Node* mergie = node;
    Node* old = sibling;
    if(leftMerge)
    {
      mergie = sibling;
      old = node;
    }
    Node* parent_last_child = getLastNode(parent);
    Node* first_node_contains_merge = firstInstance(root, mergie->getLastKey());
    Node* first_node_contains_parent_last =
      firstInstance(root, parent_last_child->getLastKey());
    Node* old_first_contains = firstInstance(root, old->getLastKey());
    //Cast these two so that we can change the siblings later
    leafNode* leaf = dynamic_cast<leafNode*>(mergie);
    leafNode* leafSibling = dynamic_cast<leafNode*>(old);//For setting the siblings correctly
    unsigned int old_last_key = old->getLastKey();
    unsigned int mergie_new_last_key;//Not used yet so it is uninitialized
    unsigned int parent_child_new_last_key;//uninitialized
    unsigned int mergie_old_last_key =
      mergie->getLastKey();
    unsigned int parent_child_old_last_key =
      parent_last_child->getLastKey();
    unsigned int parent_first_last_key =
      first_node_contains_merge->getLastKey();//used to detect if we merged with an other node
    unsigned int first_node_contains_merge_last_key =
      first_node_contains_merge->getLastKey();

    node->deleteKey(key);//we want to remove the key first

    //inserting new keys...
    mergie->insertKey(old->getKey(0));
    if(old == sibling)//here we need two since the node being removed is the sibling
      mergie->insertKey(old->getKey(1));

    mergie_new_last_key = mergie->getLastKey();

    parent_last_child = getLastNode(parent);
    parent_child_new_last_key = parent_last_child->getLastKey();

    mergie_new_last_key = mergie->getLastKey();

    if(first_node_contains_merge != nullptr && mergie_old_last_key
      != mergie_new_last_key && first_node_contains_merge != mergie)
    {
      first_node_contains_merge->deleteKey(mergie_old_last_key);
      first_node_contains_merge->insertKey(mergie_new_last_key);
    }//end if
    if(old_first_contains != nullptr && first_node_contains_merge
       != old_first_contains && old_first_contains != old &&
        old_last_key != mergie_new_last_key)
    {
      old_first_contains->deleteKey(old_last_key);
      old_first_contains->insertKey(mergie_new_last_key);
    }


    leaf->setRightSibling(leafSibling->getRightSibling());
      if(leaf->getRightSibling() != nullptr)
        leaf->getRightSibling()->setLeftSibling(leaf);
    if(leaf->getLeftSibling() == nullptr && leaf->getRightSibling() == nullptr)
    {
        root = leaf;//We are now at only 1 node.
        root->setParent(nullptr);//this node has no parent now
    }
  }
  else//we are merging two internal nodes together.
  {
    parent = node->getParent();
    //first we need to obtain a good key for insert into the node.
    Node* mergie = node;
    Node* old = sibling;
    if(leftMerge)
    {
      mergie = sibling;
      old = node;
    }
    Node* mergie_last_node = getLastNode(mergie);
    unsigned int mergie_last_node_last_key = mergie_last_node->getLastKey();
    unsigned int merger_key = mergie->getLastKey();
    unsigned int old_key = old->getLastKey();
    unsigned int parent_key = 0;//initialize
    //inintialized since we need to manipulate stuff
    unsigned int mergie_new_last_node_last_key = 0;
    for(unsigned int i = 0; i < parent->getNumKeys(); i++)
    {
      if(parent->getKey(i) > merger_key)
      {
        parent_key = parent->getKey(i);
        break;
      }
    }//end for loop
    //since we inserted the parent key, we need to remove it from the parent
    mergie->insertKey(parent_key);
    mergie->insertKey(old_key);
    // parent->deleteKey(parent_key);
    mergie->setChild(old->getChild(0), 2);
    mergie->setChild(old->getChild(1), 3);//set the new stuff for the node
    mergie->getChild(2)->setParent(mergie);
    mergie->getChild(3)->setParent(mergie);//set the parents
    mergie_last_node = getLastNode(mergie);
    mergie_new_last_node_last_key = mergie_last_node->getLastKey();

    //change the parent since the last value of the last node is now different!
    if(mergie_new_last_node_last_key != mergie_last_node_last_key)
    {
      parent->deleteKey(mergie_last_node_last_key);
      parent->insertKey(mergie_new_last_node_last_key);
    }//end if

    if(mergeRoot)
    {
      root = mergie;
    }//end if we descended a level
  }
  if(leftMerge)//lets remove some children
    removeChild(parent, node);
  else
    removeChild(parent, sibling);
}



void BPlusTree::del(unsigned int const key)
{
  Node* result = searchKey(key);
  if(!result->isMemberOf(key))
  {
    std::cout << "Key: " << key << " was not found. Ignoring deletion operation." << std::endl;
    return;
  }
  Node* parent = nullptr;
  if(root != result)//if this isnt the root, get the parent
     parent = result->getParent();
  if(result->getNumKeys() == 3)//node has to be full
  {
    if(key == result->getLastKey())
    {
      leafNode* leaf = dynamic_cast<leafNode*>(result);
      if(leaf->getRightSibling() != nullptr)
        moveKey(result, key);//this will deal with the deletion of the key in this node
      else//if there is no right sibling, then this actually has no internal reference
        result->deleteKey(key);
    }//this is the last key of the node, so it has an entry in an internal node
    else//not the last key so this isn't really a problem
    {
      result->deleteKey(key);//delete that key
    }//end else
  }//end if node is at least half full
  else//node has only one key
  {
    //try and see if you can redistribute the nodes
    //---------------------------------------------------------------
    bool accepted = false;
    leafNode* leaf = dynamic_cast<leafNode*>(result);
    leafNode* leftSibling = leaf->getLeftSibling();
    leafNode* rightSibling = leaf->getRightSibling();
    if(rightSibling != nullptr)//avoid setFault
    {
      if(rightSibling->getNumKeys() == 3)
      {
        accepted = true;//we can redistribute
        redistribute(result, rightSibling, key);
      }//end if
    }//end if rightSibling exist
    if(leftSibling != nullptr && !accepted)//avoid segFault
    {
      if(leftSibling->getNumKeys() == 3)
      {
        accepted = true;//we can redistribute
        redistribute(result, leftSibling, key);
      }
    }//end else if left sibling exist
    //-----------------------------------------------------------------------
    //This isn't the root and we didn't redistribute, so we must merge
    if(!accepted && result != root)
    {
      if(rightSibling != nullptr && result->getParent() == rightSibling->getParent())
      {
        accepted = true;
        merge(result, rightSibling, key, false);
      }//if the right sibling exist
      if(leftSibling != nullptr && !accepted && result->getParent() == leftSibling->getParent())
      {
        accepted = true;
        merge(result, leftSibling,  key, true);//merge the left with with the node
      }//end if the left child exist
    }//end if not accepted and this isn't the root
    //this was the root all along, we can just remove the key since we can't merge
    else if(!accepted && result == root)
    {
      result->deleteKey(key);
    }//end else if
  }//end else statement
}

//----END B PLUS TREE----
