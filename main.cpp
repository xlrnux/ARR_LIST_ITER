#include <stdio.h>
#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

template<typename T>
struct NODE {
    int prev;
    int next;
    T val;
};

const int NODE_SIZE = 30000;

template<typename T>
class MY_LIST {
public:
    int pos;
    int HEAD = NODE_SIZE;
    int TAIL = NODE_SIZE + 1;
    NODE<T> node[NODE_SIZE + 2];
    MY_LIST() {
        pos = 0;
        node[HEAD].next = TAIL;
        node[TAIL].prev = HEAD;
    }

    class Iter{
        NODE<T>* _node;
    public:
        int it;
        Iter(){}
        Iter(NODE<T>* __node) : _node(__node){
        }

        Iter(NODE<T>* __node, int _it) : _node(__node), it(_it){
        }

        T& operator * (){
            return _node[it].val;
        }

        T operator * () const{
            return _node[it].val;
        }

        int operator ++ () {
            return it = _node[it].next;
        }

        int operator ++ (int){
            return it = _node[it].next;
        }

        int operator -- (){
            return it = _node[it].prev;
        }

        bool operator == (const Iter& A) const{
            return _node == A._node && it == A.it;
        }

        bool operator != (const Iter& A) const{
            return _node != A._node || it != A.it;
        }
    };
    void push_back(T data) {
        int prev = node[TAIL].prev;
        int next = node[prev].next; // TAIL;

        node[pos].val = data;

        node[pos].prev = prev;
        node[prev].next = pos;

        node[pos].next = next;
        node[next].prev = pos;
        ++pos;
    }

    void push_front(T data) {
        int next = node[HEAD].next;
        int prev = node[next].prev; // HEAD

        node[pos].val = data;

        node[pos].prev = prev;
        node[prev].next = pos;

        node[pos].next = next;
        node[next].prev = pos;
        ++pos;
    }

    void insert(int p, T data) {
        int next = node[HEAD].next;
        for(int i = 0; i < p; ++i) {
            next = node[next].next;
        }
        int prev = node[next].prev;

        node[pos].val = data;

        node[pos].prev = prev;
        node[prev].next = pos;

        node[pos].next = next;
        node[next].prev = pos;
        ++pos;
    }

    void pop_back() {
        int target = node[TAIL].prev;

        int prev = node[target].prev;
        int next = node[target].next;

        node[prev].next = next;
        node[next].prev = prev;
    }

    void pop_front() {
        int target = node[HEAD].next;

        int prev = node[target].prev;
        int next = node[target].next;

        node[prev].next = next;
        node[next].prev = prev;
    }

    void erase(int p) {
        int target = node[HEAD].next;
        for (int i = 0; i < p; ++i) {
            target = node[target].next;
        }
        int prev = node[target].prev;
        int next = node[target].next;

        node[prev].next = next;
        node[next].prev = prev;
    }

    Iter erase(MY_LIST<T>::Iter& p) {
        int target = p.it;
        int prev = node[target].prev;
        int next = node[target].next;

        node[prev].next = next;
        node[next].prev = prev;
        p.it = prev;
        return p;
    }

    int ibegin() {
        return node[HEAD].next;
    }

    Iter begin() {
        return Iter(node, node[HEAD].next);
    }

    int iend() {
        return TAIL;
    }

    Iter end(){
        return Iter(node, TAIL);
    }
};

int main()
{
    MY_LIST<int> ml;
    for(int i = 10; i < 20; i++) {
        ml.push_back(i);
    }

    int it = ml.ibegin(); // 그냥 int 형 인덱스 기반
    while( ml.node[it].next != ml.iend() ){
        cout << ml.node[it].val << "\n";
        it = ml.node[it].next;
    }

    cout << "\n\n";

    // 좀 더 객체지향스럽게. 유사 iterator
    for(MY_LIST<int>::Iter _it = ml.begin(); _it != ml.end(); ++_it){
        if(*_it == 16){
            ml.erase(_it);
        }
        //cout << *_it << "\n";
    }

    for(MY_LIST<int>::Iter _it = ml.begin(); _it != ml.end(); ++_it){
        cout << *_it << "\n";
    }

    return 0;
}

