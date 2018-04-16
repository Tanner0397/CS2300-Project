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
  string param;
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
    cin >> param;
    if(option == ".")
      running = false;
    else
    {
      if(option == "i")
      {
        tree.insert(stoi(param));
      }
      else if(option == "d")
      {
        tree.del(stoi(param));
      }
      tree.print();
      string output = "";
      string output2 = "";
      string one = "dot dots/output";
      string two = to_string(counter);
      string three = ".dot -Tpng -o images/image";
      string four = ".png";
      output.append(one);
      output.append(two);
      output.append(three);
      output.append(four);
      //For progessive images
      output2.append(one);
      output2.append(two);
      output2.append(three);
      output2.append(two);//Makes a new image
      output2.append(four);
      system(output.c_str());
      system(output2.c_str());
    }
  }


}
