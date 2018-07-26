#pragma once

#include "Node.h"
namespace li {
    template<class T>
    class List;

    template<class T>
    class ListNode : public Node {
    public:
        ListNode(T val);

        friend class List<T>;

    private:
        T _val;
    };

    template<class T>
    ListNode<T>::ListNode(T val):_val(val) {}
}
