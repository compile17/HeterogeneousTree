#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <vector>

class Tree
{
public:
    Tree() = delete;
    Tree(std::any rootData);
    ~Tree();

    Node* root() const noexcept;
    void print() const noexcept;
    size_t size() const noexcept;

    static Tree* deserealisation(const std::string& fileName);
    void serelisation(const std::string& fileName) const;

private:
    void printTree(const std::string& prefix, const Node* node, bool isLast) const noexcept;
    size_t countNodes(const Node* node, size_t &count) const noexcept;
    static void split(const std::string &txt, std::vector<std::string> &strs);

    Node* _root;
};

#endif // TREE_H
