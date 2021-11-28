#include "data_structures.h"

class Stack {
protected:
    int top = -1;
    int max = 1000;
    edge* edges;

public:
    explicit Stack(int size=1000) {  // default of 1000 for our data sets
        max = size;
        edges = new edge[size];
    }

    void push(int u, int v) {
        top++;
        if(top == max) {
            top--;
            std::cout << "Stack is Full" << std::endl;
            return;
        }
        else {
            edge e{};
            e.u = u;
            e.v = v;
            edges[top] = e;
        }
    }

    void push(edge e) {
        top++;
        if(top == max) {
            top--;
            std::cout << "Stack is Full" << std::endl;
            return;
        }
        else {
            edges[top] = e;
        }
    }

    edge pop() {
        if(top < 0) {  // base case for pop
            edge null_edge{};
            null_edge.weight = -1;
            return null_edge;
        }
        else {
            edge temp = edges[top]; // return and decrement
            top--;
            return temp;
        }
    }

    int get_last_node() {
        if(top < 0) {
            return - 1;
        }
        return edges[top].u;
    }

    void clear() {
        while(pop().weight != -1) {
            pop();
        }
    }

    bool isEmpty() {
        return top < 0;
    }
};