#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>

using namespace std;

class GraphData {
private:
    int _nrVertices;
    unordered_map<int, vector<int>> _inEdges;
    unordered_map<int, vector<int>> _outEdges;
    map<pair<int, int>, int> _costs;

public:
    GraphData(int nrVertices = 0);

    int nrVertices() const;
    int nrEdges() const;

    unordered_map<int, vector<int>>& inEdges();
    unordered_map<int, vector<int>>& outEdges();
    map<pair<int, int>, int>& costs();

    const unordered_map<int, vector<int>>& inEdges() const;
    const unordered_map<int, vector<int>>& outEdges() const;
    const map<pair<int, int>, int>& costs() const;

    GraphData copy() const;
};

