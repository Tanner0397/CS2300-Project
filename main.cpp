#include <iostream>
#include "node.h"

using namespace std;

int main()
{
  BPlusTree tree;
  tree.insert(10);
  tree.insert(3);
  tree.insert(6);
  tree.insert(4);
  tree.insert(11);
  tree.insert(12);
  tree.insert(2);
  tree.insert(7);
  tree.insert(8);
  tree.insert(13);
  tree.insert(16);
  tree.insert(5);
  tree.insert(14);
  tree.insert(18);
  tree.insert(20);
  tree.insert(25);
  tree.print();
}//end main
