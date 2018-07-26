#pragma once

#include "ListNode.h"

namespace li {
    /*
     * we will assume that the items in a list are pointers to objects of a given type.
     * Here each of the operations supported by Stack runs in constant time.
     * */
    template<class T>
    class List {
    private:
        ListNode<T> *header;
        ListNode<T> *win;
        int _length;
    public:
        List(void);

        ~List(void);


        //Member functions insert, prepend, and append are used to insert new items into a list.
        T insert(T);

        //Member functions prepend and append insert a new item at the beginning and end of the list, respectively, and return the new item:
        T append(T);

        List *append(List *);

        T prepend(T);

        T remove(void);

        void val(T);

        T val(void);

        T next(void);

        T prev(void);

        T first(void);

        T last(void);

        int length(void);

        bool isFirst(void);

        bool isLast(void);

        bool isHead(void);
    };

    template<class T>
    List<T>::List(void):_length(0) {
        header = new ListNode<T>(NULL);
        win = header;
    }

    template<class T>
    List<T>::~List(void) {
        while (length() > 0) {
            first();
            remove();
        }
        delete header;
    }

    template<class T>
    T List<T>::insert(T val) {
        win->insert(new ListNode<T>(val));
        ++length;
        return val;
    }

    template<class T>
    T List<T>::prepend(T val) {
        header->insert(new ListNode<T>(val));
        ++_length;
        return val;
    }

    template<class T>
    T List<T>::append(T val) {
        header->prev()->insert(new ListNode<T>(val));
        ++_length;
        return val;
    }

    template<class T>
    List<T> *List<T>::append(List<T> *l) {
        ListNode<T> *a = (ListNode<T> *) header->prev();
        a->splice(l->header);
        _length += l->_length;
        l->header->remove();
        l->_length = 0;
        l->win = header;
        return this;
    }

    template<class T>
    T List<T>::remove(void) {
        if (win == header)
            return NULL;
        T val = win->_val;
        win = (ListNode<T> *) win->prev();
        delete (ListNode<T> *) win->next()->remove();
        --_length;
        return val;
    }

    template<class T>
    void List<T>::val(T v) {
        if (win != header)
            win->val = v;
    }

    template<class T>
    T List<T>::val(void) {
        return win->_val;
    }

    template<class T>
    T List<T>::next(void) {
        win = (ListNode<T> *) win->next();
        return win->_val;
    }

    template<class T>
    T List<T>::prev(void) {

        win = (ListNode<T> *) win->prev();
        return win->_val;
    }

    template<class T>
    T List<T>::first(void) {
        win = (ListNode<T> *) header->next();
        return win->_val;
    }

    template<class T>
    T List<T>::last(void) {
        win = (ListNode<T> *) header->prev();
        return win->_val;
    }

    template<class T>
    int List<T>::length(void) {
        return _length;
    }

    template<class T>
    bool List<T>::isFirst(void) {
        return ((win == header->next()) && (_length > 0));
    }

    template<class T>
    bool List<T>::isLast(void) {
        return ((win == header->prev()) && (_length > 0));
    }

    template<class T>
    bool List<T>::isHead(void) {
        return (win == header);
    }

    /////////////////////////////// List Examples
    template<class T>
    List<T> *arrayToList(T a[], int n) {
        List<T> *s = new List<T>;
        for (int i = 0; i < n; i++)
            s->append(a[i]);
        return s;
    }

    template<class T>
    T leastItem(List<T> &s, int(*cmp)(T, T)) {
        int i;
        if (s.length() == 0)
            return NULL;
        T v = s.first();
        for (s.next(); !s.isHead(); s.next())
            if (cmp(s.val(), v) < 0)
                v = s.val();
        return v;
    }


}
