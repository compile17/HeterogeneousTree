#ifndef OPERATIONSWITHANY_H
#define OPERATIONSWITHANY_H

#include <type_traits>
#include <any>
#include <functional>
#include <iomanip>
#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <string>

template<class T, class F>
inline std::pair<const std::type_index,
                std::function<std::string(std::any const&)>>
    to_any_visitor(F const &f)
{
    return {
        std::type_index(typeid(T)),
        [g = f](std::any const &a)
        {
            return g(std::any_cast<T const&>(a));
        }
    };
}

static std::unordered_map<
    std::type_index, std::function<std::string(std::any const&)>>
    any_visitor {
        to_any_visitor<int>([](int x){
    return std::to_string(x);
}),
        to_any_visitor<unsigned>([](unsigned x){
    return std::to_string(x);
}),
        to_any_visitor<long>([](long x){
    return std::to_string(x);
}),
        to_any_visitor<unsigned long>([](unsigned long x){
    return std::to_string(x);
}),
        to_any_visitor<long long>([](long long x){
    return std::to_string(x);
}),
        to_any_visitor<unsigned long long>([](unsigned long long x){
    return std::to_string(x);
}),
        to_any_visitor<float>([](float x){
    return std::to_string(x);
}),
        to_any_visitor<double>([](double x){
    return std::to_string(x);
}),
        to_any_visitor<long double>([](long double x){
    return std::to_string(x);
}),
        to_any_visitor<char const*>([](char const *s) {
    return std::string(s);
}),
        to_any_visitor<std::string>([](std::string s) {
    return s;
}),

};

inline void process(const std::any& a)
{
    if (const auto it = any_visitor.find(std::type_index(a.type()));
        it != any_visitor.cend()) {
        it->second(a);
        auto kek = it->second(a);
        int k = 2;
    } else {
        std::cout << "Unregistered type "<< std::quoted(a.type().name());
    }
}


#endif // OPERATIONSWITHANY_H
