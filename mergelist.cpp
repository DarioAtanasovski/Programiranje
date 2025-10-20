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

void Insert(List &l, int x);
void Print(const List &l);
void BubbleSort(List &l);
void MergePoint(List &l1, List &l2);
void DelDup(List &l);

void Insert(List &l, int x) {
    Node *p = l.start;
    while (p->next)
        p=p->next;
    p->next = new Node();
    p->next->val = x;
    p->next->next = nullptr;
}

void BubbleSort(List &l) {
    if (!l.start->next) return;
    Node *q = l.start->next;  //skip dummy node
    while (true) {
        bool sorted = true;
        Node *p = q;
        while (p->next) {
            if (p->val > p->next->val) {
                int temp = p->val;
                p->val = p->next->val;
                p->next->val = temp;
                sorted = false;
            }
            p = p->next;
        }
        if (sorted) break;
    }
}

void MergePoint(List &l1, List &l2) {
    Node *p1 = l1.start;
    while (p1->next)
        p1 = p1->next;
    p1->next=l2.start->next;
    delete l2.start;
    l2.start=nullptr;
}

void DelDup(List &l) {
    if (!l.start->next) return;
    if (!l.start->next->next) return;
    Node *p = l.start->next;
    while (p->next) {
        if (p->val == p->next->val) {
            Node * q=p->next->next;
            delete p->next;
            p->next = q;
        }
        else
            p=p->next;
    }
}

void Print(const List &l) {
    Node *p=l.start;
    while (p->next) {
        std::cout << p->next->val << " ";
        p=p->next;
    }
}

int main() {
    List l1, l2;
    int n;
    while (std::cin>>n) {
        Insert(l1, n);
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    while (std::cin>>n) {
        Insert(l2, n);
    }
    MergePoint(l1, l2);
    BubbleSort(l1);
    DelDup(l1);
    Print(l1);
}