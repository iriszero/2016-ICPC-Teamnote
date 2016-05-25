#pragma once
#include <vector>

using namespace std;

bool dfs(size_t now, const vector<vector<int>> &graph,
        vector<bool> &visited, vector<size_t> &back_match) {
    if (visited[now]) return false;
    visited[now] = true;
    
    for (int nxt: graph[now]) {
        if (back_match[nxt] == -1 || dfs(back_match[nxt], graph, visited, back_match)) {
            back_match[nxt] = now;
            return true;
        }
    }
    return false;
}

int bipartite_match(const vector<vector<int>> &graph) {
    
    
    int matched = 0;
    vector<bool> visited(graph.size(), false);
    vector<size_t> back_match(graph.size(), -1);
    
    for (size_t i =0; i<graph.size(); i++) {
        if (dfs(i, graph, visited, back_match)) {
            matched++;
        }
    }
    return matched;
}