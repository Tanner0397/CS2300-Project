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
  ifstream buffer;
  buffer.open("testInput");
  while(buffer >> option)
  {
    tree.insert(stoi(option));
  }


  tree.print();
  system("dot dots/output0.dot -Tpng -o images/image.png");

  while(running)
  {
    counter++;
    cin >> option;
    if(option == ".")
      running = false;
    else
    {
      tree.del(stoi(option));
      tree.print();
      string output = "";
      string one = "dot dots/output";
      string two = to_string(counter);
      string three = ".dot -Tpng -o images/image.png";
      output.append(one);
      output.append(two);
      output.append(three);
      system(output.c_str());
    }
  }


}
