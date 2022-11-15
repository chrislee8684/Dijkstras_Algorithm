#include <fstream>
#include <sstream>
#include <vector>
#include "dijkstra.h"

using namespace std;

graph::graph() = default;

int graph::load_graph(const string& input_file){
    ifstream graph; //declare stream object
    graph.open(input_file);
    node *start_node, *dest_node;
    string line;
    string start;
    string dest;
    string cost;
    bool b; //negligible

    //load graph
    if(graph.is_open()){
        while (getline(graph, line)) {
            istringstream stream(line);
            stream >> start >> dest >> cost; //separating row into respective components
            node temp_node;
            edge temp_edge;

            if (!(ht.contains(start))) { //hashtable doesn't contain start vertex (for row)
                temp_node.vertex_id = start;
                node_list.push_back(temp_node); //add to node list
                ht.insert(start, &node_list.back()); //add to ht
            }

            if (!(ht.contains(dest))){ //repeat for destination
                temp_node.vertex_id = dest;
                node_list.push_back(temp_node);
                ht.insert(dest, &node_list.back());
            }

            //update adjacency list
            start_node = static_cast<node *>(ht.getPointer(start, &b)); //points to nodes in node list
            dest_node = static_cast<node *>(ht.getPointer(dest, &b));

            temp_edge.dest_vertex = dest_node;
            temp_edge.cost = stoi(cost);
            start_node->adj_list.push_back(temp_edge); //add edge
        }
    }
    else
    {
        cout<<"The graph file cannot be opened."<<endl;
        exit(EXIT_FAILURE);
    }
    graph.close(); //close dictionary

    return 0;
}


void graph::apply_dijkstra(const string& start_vertex){
    bool b; //negligible
    node *start = static_cast<node *>(ht.getPointer(start_vertex, &b)); //pointer to start vertex

    heap pqueue(node_list.size()); //initialize priority queue

    (*start).dist = 0; //start vertex has 0 distance
    (*start).route.push_back(start_vertex); //save itself as starting route'

    for (auto &node: node_list){ //insert nodes into heap
        pqueue.insert(node.vertex_id, node.dist, &node);
    }

    node *temp; //pointer to node with minimum distance
    while (!pqueue.deleteMin(nullptr, nullptr, &temp)){ //deleteMin returns 1 if empty, else 0
        (*temp).explored = true;
        decreaseKey(temp, pqueue);
    }
}

void graph::decreaseKey(class node *temp, heap &pqueue){
    for (auto edge: temp->adj_list){
        if ((!edge.dest_vertex->explored) && temp->dist != INT_MAX && temp->dist + edge.cost < edge.dest_vertex->dist){ //hasn't been explored and want min distance
            edge.dest_vertex->route = temp->route; //update route
            edge.dest_vertex->route.push_back(edge.dest_vertex->vertex_id); //ends in edge dest vertex
            edge.dest_vertex->dist = temp->dist + edge.cost ;
            pqueue.setKey(edge.dest_vertex->vertex_id, edge.dest_vertex->dist); //change key value in heap
        }
    }
}

void graph::output(const string& output_file){
    ofstream output; //declare stream object
    output.open(output_file);

    for (auto node: node_list){
        output<< node.vertex_id << ": ";

        if (node.route.empty()){
            output << "NO PATH" << endl;
        }
        else{
            output << node.dist << " [";

            for (int i=0; i<node.route.size()-1; i++){ //don't want comma after last vertex
                output << node.route[i] << ", ";
            }
            output << node.route.back(); //last vertex
            output << "]";

            if (node.vertex_id != node_list.back().vertex_id){ //no newline after last vertex
                output<<endl;
            }
        }

    }
}

bool graph::check_if_exists(const string& vertex){
    return ht.contains(vertex);
}

