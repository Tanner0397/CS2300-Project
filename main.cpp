#include <iostream>
#include <stdio.h>
#include <fstream>
#include "node.h"
#include "tree.h"

using namespace std;

int main()
{
  BPlusTree tree;
  string option;
  bool running = true;
  unsigned int counter = 0;

  //initial tree
  tree.insert(12);
  tree.insert(35);
  tree.insert(3);
  tree.insert(20);
  tree.insert(85);
  tree.insert(22);
  tree.insert(5);
  tree.insert(10);
  tree.insert(1);
  tree.insert(18);
  tree.insert(11);
  tree.insert(55);
  tree.insert(99);
  tree.insert(36);
  tree.insert(47);
  tree.print();
  system("dot dots/output0.dot -Tpng -o images/image1.png");

  //Extra operations
  tree.del(85);
  tree.print();
  system("dot dots/output1.dot -Tpng -o images/image2.png");
  tree.del(84);
  tree.print();
  system("dot dots/output2.dot -Tpng -o images/image3.png");
  tree.del(18);
  tree.print();
  system("dot dots/output3.dot -Tpng -o images/image4.png");
  tree.insert(19);
  tree.print();
  system("dot dots/output4.dot -Tpng -o images/image5.png");
  tree.del(5);
  tree.print();
  system("dot dots/output5.dot -Tpng -o images/image6.png");
  tree.del(47);
  tree.print();
  system("dot dots/output6.dot -Tpng -o images/image7.png");
  tree.del(99);
  tree.print();
  system("dot dots/output7.dot -Tpng -o images/image8.png");
  tree.insert(11);
  tree.print();
  system("dot dots/output8.dot -Tpng -o images/image9.png");


}
