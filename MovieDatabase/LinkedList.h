#pragma once

#include <memory>

template<class T, class A = std::allocator<T>>
class LinkedList final
{
    struct _Node
    {
        _Node(_Node *prev, _Node*next) : prev(prev), next(next) {}
        _Node(const T& v, _Node *prev, _Node*next) : val(v), prev(prev), next(next) {}
        _Node(T&& v, _Node *prev, _Node*next) : val(std::forward<T>(v)), prev(prev), next(next) {}

        T val;
        mutable _Node *prev;
        mutable _Node *next;
    };
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    class iterator;
    class const_iterator
    {
        friend class LinkedList < T > ;
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::const_reference reference;
        typedef typename A::const_pointer pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

        const_iterator(const _Node *node) : node(node) {}
        const_iterator(const iterator& other) : node(other.node) {}
        const_iterator(const const_iterator& other) : node(other.node) {}
        ~const_iterator() {};

        const_iterator& operator++()
        {
            node = node->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator r = *this;
            ++(*this);
            return r;
        }

        const_iterator& operator--()
        {
            node = node->prev;
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator r = *this;
            --(*this);
            return r;
        }

        bool operator==(const const_iterator& other) const { return this->node == other.node; }
        bool operator!=(const const_iterator& other) const { return !(*this == other.node); }

        reference operator*() const { return node->val; }
        pointer operator->() const { return &node->val; }

    private:
        const _Node *node;
    };

    class iterator
    {
        friend class LinkedList < T > ;
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

        iterator(_Node *node) : node(node) {};
        iterator(const iterator& other) : node(other.node) {}
        ~iterator() {};

        iterator& operator++()
        {
            node = node->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator r = *this;
            ++(*this);
            return r;
        }

        iterator& operator--()
        {
            node = node->prev;
            return *this;
        }

        iterator operator--(int)
        {
            iterator r = *this;
            --(*this);
            return r;
        }

        bool operator==(const const_iterator& other) const { return this->node == other.node; }
        bool operator!=(const const_iterator& other) const { return !(*this == other.node); }

        reference operator*() const { return node->val; }
        pointer operator->() const { return &node->val; }

    private:
        _Node *node;
    };

    LinkedList() : end_(&before_begin_, &before_begin_), before_begin_(&end_, &end_), size_(0) {}
    LinkedList(const LinkedList<T>& other)
        : end_(&before_begin_, &before_begin_), before_begin_(&end_, &end_), size_(0)
    {
        auto b = other.begin();
        auto e = other.end();

        auto it = before_begin();
        for (auto& x : other)
        {
            it = insert_after(it, x);
        }
    }
    ~LinkedList()
    {
        auto cur_pointer = before_begin_.next;
        auto end_pointer = &end_;

        while (cur_pointer != end_pointer)
        {
            auto next_pointer = cur_pointer->next;
            delete cur_pointer;
            cur_pointer = next_pointer;
        }
    }

    iterator before_begin() { return iterator(&before_begin_); }
    const_iterator before_begin() const { return const_iterator(&before_begin_); }
    const_iterator cbefore_begin() const { return const_iterator(&before_begin_); }

    iterator begin() { return iterator(before_begin_.next); }
    const_iterator begin() const { return const_iterator(before_begin_.next); }
    const_iterator cbegin() const { return const_iterator(before_begin_.next); }

    iterator end() { return iterator(&end_); }
    const_iterator end() const { return const_iterator(&end_); }
    const_iterator cend() const { return const_iterator(&end_); }

    unsigned size() const { return size_; }
    bool empty() const { return size_ == 0; }

    iterator insert_after(const_iterator pos, const T& val)
    {
        _Node *node = new _Node(val,
            const_cast<_Node *>(pos.node), pos.node->next);
        pos.node->next->prev = node;
        pos.node->next = node;
        ++size_;

        return iterator(node);
    }

    iterator insert_after(const_iterator pos, T&& val)
    {
        _Node *node = new _Node(std::forward<T>(val),
            const_cast<_Node *>(pos.node), pos.node->next);
        pos.node->next->prev = node;
        pos.node->next = node;
        ++size_;

        return iterator(node);
    }

    void push_front(const T& val)
    {
        insert_after(before_begin(), val);
    }

    void push_front(T&& val)
    {
        insert_after(before_begin(), std::forward<T>(val));
    }

    iterator erase_after(const_iterator pos)
    {
        auto toremove = pos.node->next;

        pos.node->next->next->prev = const_cast<_Node*>(pos.node);
        pos.node->next = pos.node->next->next;

        delete toremove;

        --size_;

        return iterator(pos.node->next);
    }

private:
    _Node end_;
    _Node before_begin_;

    unsigned size_;
};

