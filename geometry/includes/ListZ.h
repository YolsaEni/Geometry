#pragma once

#include "ListNode.h"

namespace li {
    /*
     * we will assume that the items in a list are pointers to objects of a given type.
     * */
    template<class T>
    class ListZ {
    private:
        ListNode<T> *header;
        ListNode<T> *win;
        int _length;
    public:
        ListZ(void);

        ~ListZ(void);
    };


    template<class T>
    ListZ<T>::ListZ(void):_length(0) {
    }
    template<class T>
    ListZ<T>::~ListZ(void) {
    }

}
