#include "GraphData.h"

//constructor - initalize empty dictionaries 
GraphData::GraphData(int nrVertices) : _nrVertices(nrVertices) {
    for (int v = 0; v < nrVertices; v++) {
        _inEdges[v] = {};
        _outEdges[v] = {};
    }
}

//getters of nrVertices and nrEdges 
int GraphData::nrVertices() const { return _nrVertices; }
int GraphData::nrEdges() const { return _costs.size(); }

//modifiable dictionaries
unordered_map<int, vector<int>>& GraphData::inEdges() { return _inEdges; }
unordered_map<int, vector<int>>& GraphData::outEdges() { return _outEdges; }
map<pair<int, int>, int>& GraphData::costs() { return _costs; }

//nonmodifiable dictionaries
const unordered_map<int, vector<int>>& GraphData::inEdges() const { return _inEdges; }
const unordered_map<int, vector<int>>& GraphData::outEdges() const { return _outEdges; }
const map<pair<int, int>, int>& GraphData::costs() const { return _costs; }

//copy of graph
GraphData GraphData::copy() const {
    GraphData g(_nrVertices);
    g._inEdges = _inEdges;
    g._outEdges = _outEdges;
    g._costs = _costs;
    return g;
}
