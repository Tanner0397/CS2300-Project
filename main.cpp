#include <iostream>
#include "node.h"

using namespace std;

int main()
{
  BPlusTree tree;
  tree.insertKey(10);
  tree.insertKey(3);
  tree.insertKey(6);
  tree.insertKey(4);
  tree.insertKey(11);
  tree.insertKey(12);
  //tree.insertKey(2);
  cout << tree.root->getChild(0)->getKey(0) << endl;
  cout << tree.root->getNumKeys() << endl;
  tree.print();
}//end main
