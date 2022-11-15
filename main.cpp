#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include "dijkstra.h"
using namespace std;

int main() {

    string input_file;
    string start_vertex;
    string output_file;
    graph input_graph;
    clock_t start, end; //time function (returns clock ticks in elapsed time)

    cout<<"Enter name of graph file: ";
    cin>>input_file;
    input_graph.load_graph(input_file);

    while (!input_graph.check_if_exists(start_vertex)){
        cout<< "Enter name of starting vertex: ";
        cin>>start_vertex;
    }
        start = clock();
        input_graph.apply_dijkstra(start_vertex); //apply dijkstra's algo
        end = clock();

        cout<<"Total time (in seconds) to apply Dijkstra's algorithm: " <<fixed<<double(end-start)/double(CLOCKS_PER_SEC)<<setprecision(5)<<"seconds"<<endl;

    cout<<"Enter name of output file: ";
    cin>>output_file;
    input_graph.output(output_file);

    return 0;
}
