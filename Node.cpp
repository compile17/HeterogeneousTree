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

class nodeTypeExeption : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Unregistered type";
    }
} nodeTypeEx;

Node::Node(std::string &&smthng, Node *parent) : _parent(parent), _data(smthng)
{

//    std::cout << "construct " << std::any_cast<std::string>(_data) << std::endl;
    if (smthng == "")
        throw nodeEx;

    if (smthng.find('"') != std::string::npos)
        return;

    if (smthng.find('.') != std::string::npos) {
        try {
            _data = std::stof(smthng);
            return;
        } catch (std::out_of_range) {
            try {
                _data = std::stod(smthng);
                return;
            } catch (std::out_of_range) {
                try {
                    _data = std::stold(smthng);
                    return;
                } catch (...) {
                    _data = smthng;
                    return;
                }
            }
        } catch (...) {
            _data = smthng;
            return;
        }
    }

    try {
        _data = std::stoi(smthng);
        return;
    } catch (std::out_of_range) {
        try {
            _data = std::stol(smthng);
            return;
        } catch (std::out_of_range) {
            try {
                _data = std::stoll(smthng);
                return;
            } catch (...) {
                _data = smthng;
                return;
            }
        }
    } catch (...) {
        _data = smthng;
    }
}

Node::~Node()
{
//    std::cout << "deleter " << std::any_cast<std::string>(_data) << std::endl;
    auto size = _children.size();
    for (auto i = 0; i < size; ++i)
        delete _children[i];

    _children.clear();
}

std::string Node::getData() const
{
    if (const auto it = any_visitor.find(std::type_index(_data.type()));
        it != any_visitor.cend()) {
        return it->second(_data);
    } else {
        throw nodeTypeEx;
    }
}

std::any Node::getRawData() const noexcept
{
    return _data;
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

