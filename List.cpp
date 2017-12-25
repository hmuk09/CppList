#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node * next;

    Node()
    : data(0)
    , next(nullptr) {
    }

    explicit Node(int data)
    : data(data)
    , next(nullptr) {
    }
};

class List {
    Node * first;
    Node * last;
    size_t size;
    bool root;

    size_t distance(Node * first, Node * last) {
        if (first == nullptr)
            return 0;

        size_t number = 0;
        while (first != last) {
            ++number;
            first = first->next;
        }

        return number + 1;
    }

public:
    List()
    : first(nullptr)
    , last(nullptr)
    , size(0)
    , root(true) {
    }

    List(Node * first, Node * last)
    : first(first)
    , last(last)
    , size(distance(first, last))
    , root(false) {
    }

    ~List() {
        if (root) {
            while (first != last) {
                Node *temp = first->next;
                delete first;
                first = temp;
            }
            delete last;
        }
    }

    void push_back(int x) {
        auto * temp = new Node(x);
        if (size == 0) {
            first = temp;
        }
        else {
            last->next = temp;
        }
        last = temp;
        ++size;
    }

    void sort() {
        if (size == 1)
            return;

        Node * mid = first;
        for (int i = 0; i < size / 2 - 1; ++i)
            mid = mid->next;

        List list1(first, mid), list2(mid->next, last);
        list1.sort();
        list2.sort();

        if (list1.first->data > list2.first->data)
            swap(list1, list2);

        Node * it1 = list1.first;
        Node * it2 = list2.first;
        bool flag = false;
        while (true) {
            while (!flag && it1 != list1.last && it1->next->data < it2->data) {
                it1 = it1->next;
            }
            if (it1 == list1.last)
                flag = true;

            Node * temp = it2;
            it2 = it2->next;

            temp->next = it1->next;
            it1->next = temp;
            it1 = it1->next;

            if (temp == list2.last) {
                break;
            }
        }

        this->first = list1.first;
        if (flag)
            this->last = list2.last;
        else
            this->last = list1.last;
    }

    void print() {
        for (Node * it = first; it != last; it = it->next) {
            cout << it->data << " ";
        }
        cout << last->data << endl;
    }
};

int main() {
    int n;
    List list;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        list.push_back(x);
    }

    list.sort();

    list.print();
}