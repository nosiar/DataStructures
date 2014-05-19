#pragma once

template<class T, class A = std::allocator<T>>
class LinkedList final
{
    struct _Node
    {
        _Node() {}
        _Node(const T &v) : val(v), next(nullptr) {}
        _Node(T &&v) : val(std::move(v)), next(nullptr) {}

        T val;
        _Node *next;
    };
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    class iterator 
    {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::forward_iterator_tag iterator_category;

        iterator(_Node *x)
        {

        }
        iterator(const iterator&);
        ~iterator();

        reference operator*() { return node->val; }
        pointer operator->() { return &node->val; }

    private:
        _Node *node;
    };

    LinkedList() : head(&end_), size_(0) {}
    ~LinkedList() {}

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(&end_); }

    unsigned size() { return size_; }

    _Node end_;
    _Node *head;

    unsigned size_;
};

