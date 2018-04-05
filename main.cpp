#include <iostream>
#include <stdio.h>
#include <fstream>
#include "node.h"

using namespace std;

int main()
{
  BPlusTree tree;
  string option;
  bool running = true;
  unsigned int counter = 0;
  /*while(running)
  {
    counter++;
    cin >> option;
    if(option == ".")
      running = false;
    else
    {
      tree.insert(stoi(option));
      cout << "Current Number of Nodes: " << counter << endl;
      tree.print();
      system("dot output.gv -Tpng -o image.png");
    }//end else
  }//end while*/

  ifstream buffer;
  int input;
  buffer.open("testInput");
  while(buffer >> input)
  {
    tree.insert(input);
    //tree.print();
    //system("dot output.gv -Tpng -o image.png");
  }

  tree.del(793);
  tree.del(788);
  tree.del(804);
  tree.del(438);
  tree.del(223);

  cout << "Numer of keys found: " << tree.countKeys(tree.root) << endl;

  tree.print();
  system("dot output.gv -Tpng -o image.png");


  /*tree.insert(50);
  tree.insert(45);
  tree.insert(30);
  tree.insert(10);
  tree.insert(3);
  tree.insert(90);
  tree.insert(100);
  tree.insert(200);
  tree.insert(250);
  tree.insert(190);
  tree.insert(300);
  tree.insert(14);
  tree.insert(13);
  tree.insert(12);
  tree.insert(8);
  tree.insert(5);
  tree.print();
  system("dot output.gv -Tpng -o image.png");*/
}
