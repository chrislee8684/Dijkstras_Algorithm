#ifndef _GRAPH_H
#define _GRAPH_H


#include <list> //provided C++ list class
#include <string>
#include <limits>
#include <vector>
#include "hash.h"
#include "heap.h"

class graph{
    class node;
    class edge;

public:
    graph(); //constructor
    int load_graph(const std::string& input_file);
    void apply_dijkstra(const std::string& start_vertex);
    void output(const std::string& output_file);
    bool check_if_exists(const std::string& vertex);
    static void decreaseKey(class node *temp, heap &pqueue);

private: //define node and edge
    class node{
    public:
        std::string vertex_id;
        int dist {INT_MAX}; // initialize dist to infinity
        bool explored {false};
        std::list<edge> adj_list; //for holding connections
        std::vector<std::string> route; //for holding shortest path
    };

    class edge{
    public:
        node *dest_vertex; //pointer to destination vertex -> creates linked list
        int cost;
    };

    std::list<node> node_list;
    hashTable ht;
};


#endif