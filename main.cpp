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
  tree.insertKey(2);
  tree.insertKey(7);
  tree.insertKey(8);
  tree.insertKey(13);
  tree.insertKey(16);
  tree.insertKey(5);
  tree.insertKey(14);
  tree.insertKey(18);
  tree.insertKey(20);
  tree.insertKey(25);
  tree.print();
}//end main
