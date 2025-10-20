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
void BubbleSort(List &l);
void InsertionSort(List &l);
void Print(List &l);

void Insert(List &l, int x) {
    Node *p = l.start;
    while (p->next)
        p = p->next;
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


void InsertionSort(List &l) {
    if (!l.start->next || !l.start->next->next) return;

    Node *sortedEnd = l.start->next;
    Node *p = sortedEnd->next;

    while (p) {
        if (p->val >= sortedEnd->val) {
            sortedEnd = p;
            p = p->next;
            continue;
        }

        Node *t = p->next;
        sortedEnd->next = t;

        Node *q = l.start;
        while (q->next && q->next->val < p->val) {
            q = q->next;
        }

        p->next = q->next;
        q->next = p;

        p = t;
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
    List l;
    int n;
    while (std::cin>>n)
        Insert(l, n);
    InsertionSort(l);
    Print(l);
}