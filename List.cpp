#include <iostream>

using std::cin;
using std::cout;
using std::swap;
using std::endl;

template <class T>
struct Node {
    T data;
    Node * next;

    Node()
    : data(0)
    , next(nullptr) {
    }

    explicit Node(T data)
    : data(data)
    , next(nullptr) {
    }
};

template <class T>
class List {
    Node<T> * first;
    Node<T> * last;
    size_t size;
    bool is_basic;

    size_t distance(Node<T> * first, Node<T> * last) const {
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
    , is_basic(true) {
    }

    List(Node<T> * first, Node<T> * last)
    : first(first)
    , last(last)
    , size(distance(first, last))
    , is_basic(false) {
    }

    ~List() {
        if (is_basic) {
            while (first != last) {
                Node<T> *temp = first->next;
                delete first;
                first = temp;
            }
            delete last;
        }
    }

    void push_back(int x) {
        auto * temp = new Node<T>(x);
        if (size == 0) {
            first = temp;
        }
        else {
            last->next = temp;
        }
        last = temp;
        ++size;
    }

    void merge(List<T> list1, List<T> list2) {
        if (list1.first->data > list2.first->data)
            swap(list1, list2);

        Node<T> * it1 = list1.first;
        Node<T> * it2 = list2.first;
        bool flag = false;
        while (true) {
            while (!flag && it1 != list1.last && it1->next->data < it2->data) {
                it1 = it1->next;
            }
            if (it1 == list1.last)
                flag = true;

            Node<T> * temp = it2;
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

    void sort() {
        if (size == 1)
            return;

        Node<T> * mid = first;
        for (int i = 0; i < size / 2 - 1; ++i)
            mid = mid->next;

        List<T> list1(first, mid), list2(mid->next, last);
        list1.sort();
        list2.sort();

        merge(list1, list2);
    }

    void print() const {
        for (Node<T> * it = first; it != last; it = it->next) {
            cout << it->data << " ";
        }
        cout << last->data << endl;
    }
};

int main() {
    size_t n = 0;
    List<int> list;
    cin >> n;

    for (size_t i = 0; i < n; ++i) {
        int x;
        cin >> x;
        list.push_back(x);
    }

    list.sort();

    list.print();
}