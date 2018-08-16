#pragma once

#include "geometry_inner.h"

namespace li {
    class Node {
    protected:
        Node *_next; // link to successor node
        Node *_prev; // link to predecessor node
    public:
        Node(void);
        virtual ~Node(void);
        Node *next(void);
        Node *prev(void);
        //insert inserts node b just after this node
        Node *insert(Node*);
        //remove removes this node from its linked list
        Node *remove(void);
        //inserting a node into a linked list and removing a node from a linked list are actually special cases of splice
        void splice(Node*);
    };
}