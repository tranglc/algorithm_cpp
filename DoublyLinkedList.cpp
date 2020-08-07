#include<iostream>

using namespace std;

class StringNode {
private:
    string elem;
    StringNode* next;
    StringNode* prev;
    friend class StringLinkedList;
public:
    StringNode()
        : next(nullptr), prev(nullptr) {}
};

class StringLinkedList {
public:
    StringLinkedList();
    ~StringLinkedList();
    bool empty() const;
    const string& front() const;
    const string& back() const;
    void insert(StringNode* v, const string& e);
    void addFront(const string& e);
    void addBack(const string& e);
    void removeFront();
    void removeBack();
    void print();
private:
    StringNode* header;
    StringNode* trailer;
};

StringLinkedList::StringLinkedList()
    :header(nullptr), trailer(nullptr) {}
StringLinkedList::~StringLinkedList()
{
    while (!empty())
    {
        removeFront();
    }
    delete header;
    delete trailer;

}

bool StringLinkedList::empty() const {
    return header == trailer;
}

void StringLinkedList::addFront(const string& e) {
    StringNode* u = new StringNode;
    u->elem = e;
    if ((header == nullptr)&&(trailer == nullptr)) {
        u->next = nullptr;
        u->prev = nullptr;
        header = u;
        trailer = u;
    }
    else {
        header->prev = u;
        u->next = header;
        u->prev = nullptr;
        header = u;
    }
}
void StringLinkedList::addBack(const string& e) {
    StringNode* u = new StringNode;
    u->elem = e;
    if ((header == nullptr)&&(trailer == nullptr)) {
        u->next = nullptr;
        u->prev = nullptr;
        header = u;
        trailer = u;
    }
    else {
        trailer->next = u;
        u->next = nullptr;
        u->prev = trailer;
        trailer = u;
    }
}

const string& StringLinkedList::front() const {
    return header->elem;
}

void StringLinkedList::removeFront() {
    StringNode* old = header;
    header = old->next;
    delete old;
}


void StringLinkedList::print() {
    StringNode* it;
    it = header;
    while (it != nullptr)
    {
        cout << it->elem <<endl;
        it = it->next;
    }

}
int main() {
    StringLinkedList list;
    list.addFront("A");
    list.addBack("B");
    list.addFront("C");
    list.addBack("D");
    list.addBack("E");
    list.print();
    return 0;
}