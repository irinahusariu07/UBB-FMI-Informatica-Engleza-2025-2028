#pragma once
#include <vector>
#include <algorithm>
#include "GraphRepo.h"

using namespace std;

class GraphService {
private:
    GraphRepo& repo;
    string modFile;

public:
    GraphService(GraphRepo& repo, const string& modFile);

    int getVerticesNumber() const;
    vector<int> iterateVertices() const;

    bool checkEdge(int start, int end) const;
    int getInDegree(int v) const;
    int getOutDegree(int v) const;

    vector<int> iterateOutbound(int v) const;
    vector<int> iterateInbound(int v) const;

    void normalizeVertices();

    void addVertex(int v);
    void addEdge(int s, int e, int c);
    void removeVertex(int v);
    void removeEdge(int s, int e);
    void changeCost(int s, int e, int c);
    int retrieveCost(int s, int e); 
    vector<int> lowestLengthPath(int start, int end) const;

    pair<vector<int>, int> lowestCostWalk(int start, int end) const;

    const unordered_map<int, vector<int>>& get_in_edges() const;
    const unordered_map<int, vector<int>>& get_out_edges() const;
    const map<pair<int, int>, int>& get_costs() const;
    


    GraphData copyGraph() const;
};
