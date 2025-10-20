#include <iostream>

struct Node {
    int val;
    Node* next;
};

struct List {
    Node* start;
    List() {
        start = new Node();   // dummy node
        start->next = nullptr;
    }
};

void SortInsert(List &l, int x) {
    Node* p = l.start;
    while (p->next && p->next->val < x)
        p = p->next;

    if (p->next && p->next->val == x)
        return;

    Node* q = new Node();
    q->val = x;
    if (p->next)
        q->next = p->next;
    else
        q->next = nullptr;
    p->next = q;
}

void Print(const List &l) {
    Node *p=l.start;
    while (p->next) {
        std::cout << p->next->val << " ";
        p=p->next;
    }
}


int main() {
    int n;
    List l;
    while (std::cin>>n)
        SortInsert(l, n);
    Print(l);
}