#ifndef STRUCTS
#define DATA_STRUCTS

struct vertex {
    int val;
    int degree;
};

struct edge {
    int u;
    int v;
    int weight;
};

struct weight_list {
    edge e;
    weight_list* next;
    weight_list* prev;
};

struct circuit {
    edge e;
    circuit* next;
};

struct adj {
    int val;
    adj* next;
};

#endif