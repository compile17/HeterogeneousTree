#include "Node.h"

#include <iostream>
#include <algorithm>

class nodeExeption : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Data must not empty";
    }
} nodeEx;

Node::Node(std::any &&smthng, Node *parent) : _parent(parent), _data(smthng)
{

    std::cout << "construct " << std::any_cast<std::string>(_data) << std::endl;
    if (!smthng.has_value())
        throw nodeEx;
}

Node::~Node()
{
    std::cout << "deleter " << std::any_cast<std::string>(_data) << std::endl;
    auto size = _children.size();
    for (auto i = 0; i < size; ++i)
        delete _children[i];

    _children.clear();
}

std::string Node::getData() const noexcept
{
    return std::any_cast<std::string>(_data);
}

void Node::addChild(Node* child) noexcept
{
    _children.push_back(child);
}

auto Node::childCount() const noexcept
{
    return _children.size();
}

std::deque<Node*> Node::children() const noexcept
{
    return _children;
}

