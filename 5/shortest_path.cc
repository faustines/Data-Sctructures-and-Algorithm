//
//  shortest_path.cc
//  Program05
//
//  Copyright © 2018 Ye Wang and Faustine Yiu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stack>
#include "index_min_pq.h"

void errorHandle(int argc, char *argv[], std::ifstream& File) {
    if (argc != 4) {
        // handling errors caused by number of arguments
        std::cerr << "Usage: ./shortest_path <graph.dat> src dst" << std::endl;
        exit(1);
    }
    File.open(argv[1]);
    // handling errors caused by wrong file name or size number
    if (!File) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        exit(1);
    }
}

void readingError(int nv, int s, int d, double w) {
    // error caused by loading graph
    if (s >= nv) {
        std::cerr << "Invalid source vertex number " << s << std::endl;
        exit(1);
    } else if (d >= nv) {
        std::cerr << "Invalid dest vertex number " << d << std::endl;
        exit(1);
    } else if (w <= 0) {
        std::cerr << "Invalid weight " << w << std::endl;
        exit(1);
    }
}

void inputError(int nv, int s, int d) {
    // error caused by the command line
    if (s >= nv) {
        std::cerr << "Error: invalid source vertex number " << s << std::endl;
        exit(1);
    } else if (d >= nv) {
        std::cerr << "Error: invalid dest vertex number " << d << std::endl;
        exit(1);
    }
}

class Edge {
// contains the destination and weight from the vertex u
 public:
    Edge(unsigned int d, double w): dest(d), weight(w) {}
    double getWeight() {return weight;}
    unsigned int getDest() {return dest;}
 private:
    unsigned int dest;
    double weight;
};

class Vertex {
 public:
    void AddEdge(Edge e);
    std::vector<Edge> returnEdge() {return edges;}
 private:
    std::vector<Edge> edges;
// contains all the neighbors and length from vertex u
};

void Vertex::AddEdge(Edge e) {
    edges.emplace_back(e);
}

class Graph {
 public:
    // Create graph from input stream
    Graph(std::ifstream &ifs, char *argv[]);
    int nvReturn() {return nv;}
    int getSum() {return sumWeight;}
    std::vector<Vertex> returnVertices() {return vertices;}
    // contains all the vertices
 private:
    int nv;
    double sumWeight;
    std::vector<Vertex> vertices;
};

Graph::Graph(std::ifstream &ifs, char *argv[]) {
    /*
    loading graph from the input file,
    handling errors during the loading
    */
    ifs >> nv;
    if (ifs.fail()) {
        std::cerr << "Error: invalid graph size" << std::endl;
        exit(1);
    }
    inputError(nv, atoi(argv[2]), atoi(argv[3]));
    vertices.resize(nv);
    // set the number of vertices
    unsigned int s, d;
    double w;
    sumWeight = 0;

    while (ifs >> s >> d >> w) {
        readingError(nv, s, d, w);
        vertices[s].AddEdge(Edge(d, w));
        sumWeight += w;
    }
}

void Dijkstra(Graph G, unsigned int src, unsigned int dst) {
    IndexMinPQ<double> Q(G.nvReturn());
    // priority queue with size = number of vertices
    double limit = G.getSum() + 1;
    // limit is INFINITY (not reachable)
    std::vector<double> dist(G.nvReturn(), limit);
    std::vector<unsigned int> prev(G.nvReturn(), -1);

    unsigned int u;
    double alt;

    dist[src] = 0;
    // Distance from src to itself is 0
    Q.Push(dist[src], src);

    while (Q.Size() > 0) {
        u = Q.Top();
        Q.Pop();
        if (u == dst)
            break;
        for (auto i : G.returnVertices()[u].returnEdge()) {
        /*
        go through every neighbor of vertex u
        find the shortest path
        */
            alt = dist[u] + i.getWeight();
            if (alt < dist[i.getDest()]) {
                dist[i.getDest()] = alt;
                prev[i.getDest()] = u;
                if (Q.Contains(i.getDest())) {
                    Q.ChangeKey(dist[i.getDest()], i.getDest());
                } else {
                    Q.Push(dist[i.getDest()], i.getDest());
                }
            }
        }
    }

    // backtracking part
    std::stack<unsigned int> S;
    u = dst;

    if (dist[u] < limit) {
    // if there exists a path
        while (static_cast<int>(u) != -1) {
            S.push(u);
            u = prev[u];
        }
    } else {
        std::cout << "no path" << std::endl;
        return;
    }

    // print the result
    while (!S.empty()) {
        if (S.size() != 1) {
            std::cout << S.top() << " => ";
        } else {
            std::cout << S.top();
        // no need to print => for the last vertex
        }
        S.pop();
    }
    std::cout << " (" << dist[dst] << ")" << std::endl;
}

int main(int argc, char *argv[]) {
    std::ifstream datFile;
    errorHandle(argc, argv, datFile);
    // if the file is valid
    Graph G(datFile, argv);
    int src = atoi(argv[2]);
    int dest = atoi(argv[3]);
    std::cout << src << " to " << dest << ": ";
    Dijkstra(G, src, dest);
}
