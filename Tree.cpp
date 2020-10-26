#include "Tree.h"
#include <iostream>
#include <fstream>
#include <vector>

Tree::Tree(std::any rootData) : _root(new Node(std::move(rootData)))
{}

Tree::~Tree()
{
    std::cout << "DESTRUCTION!\n";
    delete _root;
}

Node* Tree::root() const noexcept
{
    return _root;
}

void Tree::print() const noexcept
{
    printTree("", _root, false);
}

void Tree::printTree(const std::string& prefix, const Node* node, bool isLast) const noexcept
{
    if (node != nullptr)
    {
        std::cout << prefix;

//        std::cout << (isLast ? "├──" : "└──" );
        std::cout << (isLast ? "+--" : "L__" );

        // print the value of the node
        std::cout << node->getData() << std::endl;

        // enter the next tree level - left and right branch
        size_t size = node->children().size();
        for (size_t i = 0; i < size; ++i) {
            if (i != size - 1)
//                printTree( prefix + (isLast ? "│   " : "    "), node->children()[i], true);
                printTree( prefix + (isLast ? "|   " : "    "), node->children()[i], true);
            else
                printTree( prefix + (isLast ? "|   " : "    "), node->children()[i], false);
//                printTree( prefix + (isLast ? "│   " : "    "), node->children()[i], false);
        }
    }
}

size_t Tree::countNodes(const Node *node, size_t& count) const noexcept
{
    size_t size = node->children().size();
    count += size;
    for (size_t i = 0; i < size; ++i)
        countNodes(node->children()[i], count);

    return count;
}

size_t Tree::size() const noexcept
{
    size_t count {1};

    countNodes(_root, count);

    return count;
}

void Tree::split(const std::string &txt, std::vector<std::string> &strs)
{
    char ch = ' ';
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );
}

Tree* Tree::deserealisation(const std::string &fileName)
{
    std::string buf;
    std::ifstream file(fileName);

    getline(file, buf);
    if (buf == "") {
        file.close();
        return nullptr;
    }
    Tree* tree = new Tree(buf);

    std::vector<std::string> strs;
    std::vector<Node*> nodes;
    nodes.reserve(1);
    nodes.push_back(tree->root());

     while (getline(file, buf)) {
        split(buf, strs);
        int count {0};
        std::vector<Node*> temp;
        temp.reserve(strs.size());

        for (const auto& str : strs) {
            if (str == "-2" || str == "") {
                ++count;
                continue;
            }

            auto node = new Node(str, nodes[count]);
            nodes[count]->addChild(node);
            temp.push_back(node);
        }
        nodes = temp;
    }
     file.close();

     return tree;
}

void Tree::serelisation(const std::string &fileName) const
{
    std::ofstream out;
    out.open(fileName);
    if (out.is_open()) {
        out << this->root()->getData() << '\n';

        std::deque<Node*> children = this->root()->children();
        std::deque<Node*> temp;

        while (true) {
            std::string res;
            for (const auto& child : children) {
                res += child->getData() + " ";
                if (child->getData() != "-2") {
                    for (const auto& subchild : child->children())
                        temp.push_back(subchild);
                    temp.emplace_back(new Node(std::string("-2")));
                }
            }
            out << res << '\n';
            if (!temp.size()) break;
            children = temp;
            temp.clear();
        }
    }
}
