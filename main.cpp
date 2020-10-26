#include "Tree.h"

int main()
{
    Tree* tree = Tree::deserealisation(std::string("E:\\test.txt"));

    tree->print();

    tree->serelisation(std::string("E:\\test.txt"));

    return 0;
}
