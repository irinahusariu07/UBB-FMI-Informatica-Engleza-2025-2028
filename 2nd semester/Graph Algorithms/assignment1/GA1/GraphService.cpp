#include "GraphService.h"
#include <stdexcept>
#include <queue>

//constructor of services
GraphService::GraphService(GraphRepo& repo, const string& modFile)
    : repo(repo), modFile(modFile) {
}

//no vertices
int GraphService::getVerticesNumber() const {
    return repo.graph.nrVertices();
}

//iterate through all vertices 
vector<int> GraphService::iterateVertices() const {
    //create a vector for all vertices (copy)
    vector<int> v;
    v.reserve(repo.graph.nrVertices());

    //adds from out edges the keys -> all vertices 
    for (auto& kv : repo.graph.outEdges())
        v.push_back(kv.first);

    //sorts them and returns
    sort(v.begin(), v.end());
    return v;
}

//check if edge exists 
bool GraphService::checkEdge(int start, int end) const {
    return repo.graph.costs().count({ start, end });
}

//get in degree of vertex
int GraphService::getInDegree(int v) const {
    return repo.graph.inEdges().at(v).size();
}

//get out degree of vertex
int GraphService::getOutDegree(int v) const {
    return repo.graph.outEdges().at(v).size();
}

//iterate through outbound neighbours of a vertex
vector<int> GraphService::iterateOutbound(int v) const {
    //a new vector => copy
    vector<int> out = repo.graph.outEdges().at(v);
    sort(out.begin(), out.end());
    return out;
}

//iterate through inbound of a vertex
vector<int> GraphService::iterateInbound(int v) const {
    vector<int> in = repo.graph.inEdges().at(v);
    sort(in.begin(), in.end());
    return in;
}

void GraphService::normalizeVertices()
{
    //build mapping old -> new
    vector<int> vertices;
    vertices.reserve(repo.graph.nrVertices());

    for (auto& kv : repo.graph.outEdges())
        vertices.push_back(kv.first);

    sort(vertices.begin(), vertices.end());

    unordered_map<int, int> mapping;
    int newId = 0;
    for (int v : vertices)
        mapping[v] = newId++;

    //build new graph
    GraphData newG(newId);

    for (auto& kv : repo.graph.costs()) {
        int s = kv.first.first;
        int e = kv.first.second;
        int c = kv.second;

        int ns = mapping[s];
        int ne = mapping[e];

        newG.outEdges()[ns].push_back(ne);
        newG.inEdges()[ne].push_back(ns);
        newG.costs()[{ns, ne}] = c;
    }

    repo.graph = newG;
}

//change cost of an edge
void GraphService::changeCost(int s, int e, int c) {
    if (!checkEdge(s, e))
        throw runtime_error("The edge does not exist");

    repo.graph.costs()[{s, e}] = c;
    repo.saveModifications(repo.graph, modFile);
}

//get the cost of an edge 
int GraphService::retrieveCost(int s, int e)
{
    if (!checkEdge(s,e))
        throw runtime_error("The edge does not exist");
    int c; 
    c = repo.graph.costs()[{s, e}];
    return c; 
}


//add a vertex
void GraphService::addVertex(int v) {
    //checks if vertex number > no_vertices or already an existing one 
    if (v != repo.graph.nrVertices())
        throw runtime_error("Vertex must be the next available id");
    //new graph - copy
    GraphData newG(v + 1);
    //add to dict
    for (auto& kv : repo.graph.costs()) {
        int s = kv.first.first;
        int e = kv.first.second;
        int c = kv.second;

        newG.outEdges()[s].push_back(e);
        newG.inEdges()[e].push_back(s);
        newG.costs()[{s, e}] = c;
    }

    repo.graph = newG;
    repo.saveModifications(repo.graph, modFile);
}

//add a new edge 
void GraphService::addEdge(int s, int e, int c) {
    //repo function
    repo.addDict(repo.graph, s, e, c);
    repo.saveModifications(repo.graph, modFile);
}

//remove vertex
void GraphService::removeVertex(int v) {
    //removes all occurences of tha vertex
    for (int out : repo.graph.outEdges()[v])
        repo.graph.costs().erase({ v, out });

    for (int in : repo.graph.inEdges()[v])
        repo.graph.costs().erase({ in, v });

    repo.graph.outEdges().erase(v);
    repo.graph.inEdges().erase(v);

    normalizeVertices();
    repo.saveModifications(repo.graph, modFile);
}

//remove edge 
void GraphService::removeEdge(int s, int e) {
    //repo function remove 
    repo.removeDict(repo.graph, s, e);
    repo.saveModifications(repo.graph, modFile);
}

GraphData GraphService::copyGraph() const {
    //save the current graph state into the modification file
    repo.saveModifications(repo.graph, modFile);

    //return a deep copy of the graph
    return repo.graph.copy();
}

//lowest length path using reverse BFS
vector<int> GraphService::lowestLengthPath(int start, int end) const
{
    int n = repo.graph.nrVertices();
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(end);
    visited[end] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (v == start)
            break;

        for (int u : repo.graph.inEdges().at(v)) {
            if (!visited[u]) {
                visited[u] = true;
                parent[u] = v;
                q.push(u);
            }
        }
    }

    if (!visited[start])
        throw runtime_error("No path exists");

    vector<int> path;
    for (int v = start; v != -1; v = parent[v])
        path.push_back(v);

    return path; // already from start → end
}

//lowest cost walk 
pair<vector<int>, int> GraphService::lowestCostWalk(int start, int end) const {
    int n = repo.graph.nrVertices();
    const long long INF = 1e15;

    // d[v][k] = min cost to reach v using exactly k edges
    vector<vector<long long>> d(n, vector<long long>(n + 1, INF));
    vector<vector<int>> parent(n, vector<int>(n + 1, -1));

    d[start][0] = 0;

    // Relax edges for walks of length 1..n-1
    for (int k = 1; k < n; k++) {
        for (auto& kv : repo.graph.costs()) {
            int u = kv.first.first;
            int v = kv.first.second;
            long long cost = kv.second;

            if (d[u][k - 1] != INF && d[u][k - 1] + cost < d[v][k]) {
                d[v][k] = d[u][k - 1] + cost;
                parent[v][k] = u;
            }
        }
    }

    // Compute min_costs[v] = best cost to reach v using < n edges
    vector<long long> min_costs(n, INF);
    for (int v = 0; v < n; v++) {
        for (int k = 0; k < n; k++) {
            min_costs[v] = min(min_costs[v], d[v][k]);
        }
    }

    // Negative cycle detection:
    // If any edge can still improve min_costs[v], a negative cycle is reachable.
    for (auto& kv : repo.graph.costs()) {
        int u = kv.first.first;
        int v = kv.first.second;
        long long cost = kv.second;

        for (int k_prev = 0; k_prev < n; k_prev++) {
            if (d[u][k_prev] != INF && d[u][k_prev] + cost < min_costs[v]) {
                throw runtime_error("Negative cost cycle reachable from start vertex");
            }
        }
    }

    // Find best k for reaching 'end'
    long long best_cost = INF;
    int best_k = -1;

    for (int k = 0; k < n; k++) {
        if (d[end][k] < best_cost) {
            best_cost = d[end][k];
            best_k = k;
        }
    }

    if (best_cost == INF) {
        throw runtime_error("No walk exists from start to end");
    }

    // Reconstruct path
    vector<int> path;
    int curr = end;
    int curr_k = best_k;

    while (curr_k >= 0) {
        path.push_back(curr);
        curr = parent[curr][curr_k];
        curr_k--;
    }

    reverse(path.begin(), path.end());
    return { path, (int)best_cost };
}


//getters for dict 
const unordered_map<int, vector<int>>& GraphService::get_in_edges() const {
    return repo.graph.inEdges();
}

const unordered_map<int, vector<int>>& GraphService::get_out_edges() const {
    return repo.graph.outEdges();
}

const map<pair<int, int>, int>& GraphService::get_costs() const {
    return repo.graph.costs();
}

