#include "stack.cpp"

int min(int a, int b) {
    if(a < b) {
        return a;
    }
    return b;
}

void FLOYD_WARSHALL(vertex** matrix, int size) {
    // modifies the weight matrix in place
    for(int kk=0; kk<size; kk++) {  // intermediate
        for(int ii=0; ii<size; ii++) {  // sources
            for(int jj=0; jj<size; jj++) {  // destinations
                if(ii != jj) {  // we never use the diagonal values
                    matrix[ii][jj].val = min(matrix[ii][jj].val, matrix[ii][kk].val + matrix[kk][jj].val);
                }
                else { // change from 'infinity' to 0 to match output
                    matrix[ii][jj].val = 0;
                }
            }
        }
    }
}

vertex* get_degrees(vertex** matrix, int size) {
    // this stores the respective number of the vertex in val and degree in degree
    auto* result = new vertex[size];
    for(int ii=0; ii<size; ii++) {
        result[ii].val = ii;
        result[ii].degree = 0;
        for(int jj=0; jj<size; jj++) {
            result[ii].degree += matrix[ii][jj].degree;
        }
    }
    return result;
}

weight_list* create_head(weight_list* h, edge e) {
    auto* w = new weight_list;
    w->prev = nullptr;
    w->next = nullptr;
    w->e = e;
    return w;
}

weight_list* add_edge(weight_list* w, edge e) {
    if(w == nullptr) {
        auto* head = new weight_list;
        head->prev = nullptr;
        head->next = nullptr;
        head->e = e;
        return head;
    }
    weight_list* itr = w;
    while(itr->next != nullptr and itr->e.weight < e.weight) {  // find the weight category to insert
        itr = itr->next;
    }
    while(itr->next != nullptr and itr->e.u <= e.u and itr->e.weight == e.weight) {  // find where edge belongs
        if(itr->e.u == e.u) {
            if(itr->e.v > e.v) {
                break;
            }
        }
        itr = itr->next;
    }

    if(itr->next == nullptr and ((itr->e.u < e.u or (itr->e.u == e.u and itr->e.v < e.v)) and
        e.weight == itr->e.weight) or itr->e.weight < e.weight) { // inserting edge is the new largest in data set
        // create new memory for the new largest
        itr->next = new weight_list;
        itr->next->next = nullptr;
        itr->next->prev = itr;
        itr->next->e = e;
    }
    else {
        itr = itr->prev; // this is where we want to insert for a new head
        if(itr == nullptr) { // creating a new head
            auto* new_head = new weight_list;
            new_head->e = e;
            new_head->prev = nullptr;
            new_head->next = w; // relink new head to old
            w->prev = new_head;
            return new_head;
        }

        // go to where we should insert otherwise
        while (itr->next->e.weight == e.weight and
        (itr->next->e.u < e.u or (itr->next->e.u == e.u and itr->e.v < e.v))) {
            itr = itr->next;
        }
        // create insertion variable and new memory
        auto* ins = new weight_list;
        ins->e = e;  // assign edge

        weight_list* new_next = itr->next;
        itr->next = ins;
        ins->prev = itr;
        ins->next = new_next;
    }
    return w;
}

weight_list* create_weight_list(vertex** matrix, int size) {
    weight_list* result = nullptr;
    vertex* vertices = get_degrees(matrix, size);

    // find out how many odd degree vertices there are
    int odd_size = 0;
    for(int ii=0; ii<size; ii++) {
        if(vertices[ii].degree % 2 != 0) {
            odd_size++;
        }
    }

    // create array of only odd vertices
    auto* odds = new vertex[odd_size];
    int index = 0;
    for(int ii=0; ii<size; ii++) {
        if(vertices[ii].degree % 2 != 0) {
            odds[index] = vertices[ii];
            index++;
        }
    }

    // create sorted list
    for(int ii=0; ii<(odd_size - 1); ii++) {
        for(int jj=(ii + 1); jj<odd_size; jj++) {
            // allocate memory for new edge
            edge* e = new edge;
            e->weight = matrix[odds[ii].val][odds[jj].val].val;  // index the matrix at given vertices
            e->u = odds[ii].val;
            e->v = odds[jj].val;

            // add to data set
            result = add_edge(result, *e);
        }
    }
    return result;
}

weight_list* get_virtual_edges(vertex** matrix, int size) {
    weight_list* all = create_weight_list(matrix, size);  // sorted odd degree edges
    weight_list* added = nullptr;

    while(all != nullptr) {
        weight_list* itr = added;
        bool can_add = true;
        while(itr != nullptr) {
            if(itr->e.u == all->e.u or itr->e.u == all->e.v or itr->e.v == all->e.u or itr->e.v == all->e.v) {
                can_add = false;
                break;
            }
            itr = itr->next;
        }
        if(can_add) {
            added = add_edge(added, all->e);
        }
        all = all->next;
    }
    return added;
}

void add_adjacency(adj** list, int u, int v) {
    if(list[u - 1] == nullptr) { // first item
        list[u - 1] = new adj;
        list[u - 1]->val = v - 1; // fixing val for index
    }
    else {
        adj* itr = list[u - 1];
        while(itr->next != nullptr) {
            itr = itr->next;
        }
        itr->next = new adj;
        itr->next->val = v - 1; // fixing val for index
        itr->next->next = nullptr;
    }
    if(list[v - 1] == nullptr) { // first item
        list[v - 1] = new adj;
        list[v - 1]->val = u - 1; // fixing val for index
    }
    else {
        adj* itr = list[v - 1];
        while(itr->next != nullptr) {
            itr = itr->next;
        }
        itr->next = new adj;
        itr->next->val = u - 1; // fixing val for index
        itr->next->next = nullptr;
    }
}

int find_next(adj** list, int index, int prev, int size) {
    adj* itr = list[index];
    if(itr == nullptr) {
        return size;
    }
    while(itr->next != nullptr) {
        if(itr->val != prev) {
            break;
        }
        itr = itr->next;
    }
    return itr->val;
}

void remove(adj** list, int u, int v) {
    adj* itr = list[u];
    adj* prev = itr;
    while(itr->val != v) {
        prev = itr;
        itr = itr->next;
    }
    if(prev == itr) {
        list[u] = itr->next;
    }
    else {
        prev->next = itr->next;
    }
    itr = list[v];
    prev = itr;
    while(itr->val != u) {
        prev = itr;
        itr = itr->next;
    }
    if(prev == itr) {
        list[v] = itr->next;
    }
    else {
        prev->next = itr->next;
    }
}

circuit* add_to_circuit(circuit* c, int u, int v) {
    edge* e = new edge;
    e->u = u;
    e->v = v;
    if(c == nullptr) {
        auto* ret = new circuit;
        ret->next = nullptr;
        ret->e = *e;
        return ret;
    }

    circuit* itr = c;
    while(itr->next != nullptr) {
        itr = itr->next;
    }

    itr->next = new circuit;
    itr->next->next = nullptr;
    itr->next->e = *e;
    return c;
}

weight_list* add_edge_rev(weight_list* w, edge e) {
    if(w == nullptr) {
        auto* head = new weight_list;
        head->prev = nullptr;
        head->next = nullptr;
        head->e = e;
        return head;
    }

    w->next = new weight_list;
    w->next->next = nullptr;
    w->next->prev = w;
    w->next->e = e;
    return w->next;
}


void find_path(vertex** matrix, int matrixSize, int start, int end) {
    weight_list* w = nullptr;
    for(int ii=0; ii<matrixSize; ii++) {
        if(matrix[start][ii].val == 1) {
            edge* e = new edge;
            e->u = ii;
            e->v = start;
            w = add_edge_rev(w, *e);
            start = ii;
            ii = -1; // reset index

            if(start == end) {
                break;
            }
        }
    }
    while(w != nullptr) {
        std::cout << "      (" << w->e.u + 1 << "," << w->e.v + 1 << ")\n";
        w = w->prev;
    }

}


void print_ad_list(adj** list, int size) {
    for(int ii=0; ii<size; ii++) {
        adj* itr = list[ii];
        std::cout << ii + 1 << ": ";
        while(itr != nullptr) {
            std::cout << itr->val + 1 << " ";
            itr = itr->next;
        }
        std::cout <<"\n";
    }
}

void print_circuit(vertex** matrix, int matrixSize, adj** list, weight_list* vrt_edges) {
    Stack edges;

    int prev = 0;
    int next = 0;
    int u = 0;
    int not_ok = 0;

    std::cout << "The Euler circuit in G with virtual edges is:\n";

    do {
        next = find_next(list, prev, not_ok, matrixSize);
        if(next == matrixSize) {
            std::cout << "      (" << u + 1 << "," << not_ok + 1 << ")\n";

            u = prev = not_ok;
            edges.pop();
            not_ok = edges.get_last_node();
        }
        else {
            edges.push(prev, next);
            //std::cout << "adding: " << "(" << prev + 1 << "," << next + 1 << ")\n";
            remove(list, prev, next);
            not_ok = prev;
            prev = next;

            if(next == u) {
                std::cout << "      (" << u + 1 << "," << not_ok + 1 << ")\n";

                u = prev = not_ok;
                edges.pop();
                not_ok = edges.get_last_node();
            }

            // check for virtual edges
            weight_list* itr = vrt_edges;
            int ref = find_next(list, prev, not_ok, matrixSize);
            while(itr != nullptr) {
                if(prev == itr->e.u and itr->e.v < ref) {
                    edges.push(prev, itr->e.v);
                    //std::cout << "adding: " << "(" << prev + 1 << "," << itr->e.v + 1 << ")\n";
                    not_ok = prev;
                    prev = itr->e.v;

                    if(itr->e.v == u) {
                        find_path(matrix, matrixSize, not_ok, itr->e.v);
                        u = prev = not_ok;
                        edges.pop();
                        not_ok = edges.get_last_node();
                    }

                    // remove
                    if(itr->prev == nullptr) {
                        vrt_edges = itr->next; // first element
                        if(vrt_edges != nullptr) {
                            vrt_edges->prev = nullptr;
                        }
                    }
                    else if(itr->next == nullptr) {
                        itr = itr->prev;
                        itr->next = nullptr;
                    }
                    else {
                        weight_list* new_next = itr->next;
                        itr = itr->prev;
                        itr->next = new_next;
                        new_next->prev = itr;
                    }
                    break;
                }
                else if(prev == itr->e.v and itr->e.u < ref) {
                    edges.push(prev, itr->e.u);
                    //std::cout << "adding: " << "(" << prev + 1 << "," << itr->e.u + 1 << ")\n";
                    not_ok = next;
                    prev = itr->e.u;

                    if(itr->e.u == u) {
                        find_path(matrix, matrixSize, not_ok, itr->e.u);
                        u = prev = not_ok;
                        edges.pop();
                        not_ok = edges.get_last_node();
                    }

                    // remove
                    if(itr->prev == nullptr) {
                        vrt_edges = itr->next; // first element
                        if(vrt_edges != nullptr) {
                            vrt_edges->prev = nullptr;
                        }
                    }
                    else if(itr->next == nullptr) {
                        itr = itr->prev;
                        itr->next = nullptr;
                    }
                    else {
                        weight_list* new_next = itr->next;
                        itr = itr->prev;
                        itr->next = new_next;
                        new_next->prev = itr;
                    }
                    break;
                }
                itr = itr->next;
            }
        }
    } while(!edges.isEmpty());
}

