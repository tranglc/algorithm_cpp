#include<iostream>

using namespace std;

class StringNode {
private:
    string elem;
    StringNode* next;

    friend class StringLinkedList;
public:
    StringNode()
        : next(nullptr) {}
};

class StringLinkedList {
public:
    StringLinkedList();
    ~StringLinkedList();
    bool empty() const;
    const string& front() const;
    void addFront(const string& e);
    void removeFront();
    void print();
private:
    StringNode* head;
};

StringLinkedList::StringLinkedList()
    :head(nullptr) {}
StringLinkedList::~StringLinkedList()
{
    while (!empty())
    {
        removeFront();
    }
    delete head;

}

bool StringLinkedList::empty() const {
    return head == nullptr;
}

void StringLinkedList::addFront(const string& e) {
    StringNode* v = new StringNode;
    v->elem = e;
    v->next = head;
    head = v;
}

const string& StringLinkedList::front() const {
    return head->elem;
}

void StringLinkedList::removeFront() {
    StringNode* old = head;
    head = old->next;
    delete old;
}


void StringLinkedList::print() {
    StringNode* it;
    it = head;
    while (it != nullptr)
    {
        cout << it->elem <<endl;
        it = it->next;
    }

}
int main() {
    StringLinkedList list;
    list.addFront("A");
    list.addFront("B");
    list.addFront("C");
    list.addFront("D");
    list.addFront("E");
    list.print();
    return 0;
}