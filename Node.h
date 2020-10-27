#ifndef NODE_H
#define NODE_H

#include <memory>
#include <any>
#include <typeinfo>
#include <exception>
#include <deque>

#include "OperationsWithAny.h"

class Node;

class Node
{
public:
    Node() = delete;
    Node(std::string &&smthng, Node* parent = nullptr);

    ~Node();

    std::string getData() const;
    void addChild(Node* child) noexcept;
    auto childCount() const noexcept;
    std::deque<Node*> children() const noexcept;

private:
    std::deque<Node*> _children;
    Node* _parent;

    std::any _data;
};

#endif // NODE_H
