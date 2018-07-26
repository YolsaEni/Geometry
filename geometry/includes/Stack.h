#pragma once

#include "List.h"

namespace li {

    /*
     * Class Stack is a good example of an abstract data type.
     * */
    template<class T>
    class Stack {
    private:
        List<T> *s;
    public:
        Stack(void);

        ~Stack(void);

        void push(T v);

        T pop(void);

        bool empty(void);

        int size(void);

        //None of the three peek operations changes the state of the stack
        T top(void);

        T nextToTop(void);

        T bottom(void);
    };
    //////////////////////

    template<class T>
    Stack<T>::Stack(void):s(new List<T>) {}

    template<class T>
    Stack<T>::~Stack(void) {
        delete s;
    }

    template<class T>
    void Stack<T>::push(T v) {
        s->prepend(v);
    }

    template<class T>
    T Stack<T>::pop(void) {
        s->first();
        return s->remove();
    }

    template<class T>
    bool Stack<T>::empty(void) {
        return (s->length() == 0);
    }

    template<class T>
    int Stack<T>::size(void) {
        return s->length();
    }

    template<class T>
    T Stack::top(void) {
        return s->first();
    }

    template<class T>
    T Stack::nextToTop(void) {
        s->first();
        return s->next();
    }

    template<class T>
    T Stack::bottom(void) {
        return s->last();
    }

    ////////////////////////// example

    void reverse(char *a[], int n) {
        Stack<char *> s;
        for (int i = 0; i < n; i++)
            s.push(a[i]);
        for (i = 0; i < n; i++)
            a[i] = s.pop();
    }
}