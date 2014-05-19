#pragma once

template<typename T>
class LinkedList 
{
public:
    LinkedList() {}

    unsigned size() { return size_; }

private:
    unsigned size_;
    struct _Node
    {
        _Node(T v) : val(v), next(nullptr) {}

        T val;
        _Node *next;
    };
};