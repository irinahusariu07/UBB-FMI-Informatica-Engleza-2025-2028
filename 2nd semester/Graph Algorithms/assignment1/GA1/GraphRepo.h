#pragma once
#include <string>
#include "GraphData.h"

using namespace std;

class GraphRepo {
private:
    string filename;
    void loadFile();

public:
    GraphData graph;

    GraphRepo(const string& filename);

    void addDict(GraphData& g, int start, int end, int cost);
    void removeDict(GraphData& g, int start, int end);

    static void writeRandom(const string& filename, int vertices, int edges = -1);
    void saveModifications(const GraphData& g, const string& filename);
};
