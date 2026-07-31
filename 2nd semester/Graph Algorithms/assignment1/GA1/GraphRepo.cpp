#include "GraphRepo.h"
#include <fstream>
#include <stdexcept>
#include <cstdlib>

GraphRepo::GraphRepo(const string& filename) : filename(filename), graph(0) {
    loadFile();
}

//read a graph from file 
void GraphRepo::loadFile() {
    ifstream f(filename);
    if (!f.is_open()) throw runtime_error("Cannot open file");

    int v, e;
    f >> v >> e;

    graph = GraphData(v);

    for (int i = 0; i < e; i++) {
        int s, t, c;
        f >> s >> t >> c;
        addDict(graph, s, t, c);
    }
}

//the actions performed when adding a new edge 
void GraphRepo::addDict(GraphData& g, int start, int end, int cost) {
    //check if already exists 
    if (g.costs().count({ start, end }))
        throw runtime_error("Edge already exists");
    //adds to every dict
    g.outEdges()[start].push_back(end);
    g.inEdges()[end].push_back(start);
    g.costs()[{start, end}] = cost;
}


//the actions performed when deleting an edge 
void GraphRepo::removeDict(GraphData& g, int start, int end) {
    //checks if it exists 
    if (!g.costs().count({ start, end }))
        throw runtime_error("Edge does not exist");

    //delete from every dict
    g.costs().erase({ start, end });

    auto& outV = g.outEdges()[start];
    outV.erase(remove(outV.begin(), outV.end(), end), outV.end());

    auto& inV = g.inEdges()[end];
    inV.erase(remove(inV.begin(), inV.end(), start), inV.end());
}

//function that generates a random graph in a txt file 
void GraphRepo::writeRandom(const string& outFile, int vertices, int edges) {
    long long maxEdges = 1LL * vertices * vertices;

    //if no edges not specified generate random number 
    if (edges < 0)
        edges = rand() % (maxEdges + 1);

    //if too many edges requested 
    if (edges > maxEdges) {
        throw runtime_error(
            "Too many edges requested: " + to_string(edges) +
            ". Maximum possible for " + to_string(vertices) +
            " vertices is " + to_string(maxEdges)
        );
    }

    //creates a graph with these characteristics
    GraphData g(vertices);

    //opens and writes in the file the random gen graph 
    ofstream f(outFile);
    if (!f.is_open())
        throw runtime_error("Cannot open output file");

    f << vertices << " " << edges << "\n";

    int added = 0;
    while (added < edges) {
        int s = rand() % vertices;
        int e = rand() % vertices;
        int c = (rand() % 41) - 20;

        if (g.costs().count({ s, e })) continue;

        g.outEdges()[s].push_back(e);
        g.inEdges()[e].push_back(s);
        g.costs()[{s, e}] = c;

        f << s << " " << e << " " << c << "\n";
        added++;
    }
}

//saves modifications to a modif file 
void GraphRepo::saveModifications(const GraphData& g, const string& outFile) {
    ofstream f(outFile);
    f << g.nrVertices() << " " << g.nrEdges() << "\n";

    //writes frm cost dict : start v end v and cost 
    for (auto& kv : g.costs()) {
        f << kv.first.first << " " << kv.first.second << " " << kv.second << "\n";
    }
}
