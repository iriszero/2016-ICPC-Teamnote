#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

template<typename type>
class Node {
public:
    int idx;
    type dist;
    Node(size_t idx, type dist) {
        this->idx = idx;
        this->dist = dist;
    }
    bool operator> (const Node &r) const {
        return this->dist > r.dist;
    }
};

template<typename type>
class Edge {
public:
    int src, dst;
    type weight;
    Edge(int src, int dst, type weight) {
        this->src = src;
        this->dst = dst;
        this->weight =weight;
    }
};
template<typename type>
vector<type> dijkstra(const vector<Node<type>> &graph, int src) {
    vector<type> dist;
    priority_queue<Node<type>> pq;
    pq.push({src, 0});
    
    while(!pq.empty()) {
        Node<type> now = pq.top();
        pq.pop();
        
        for (Node<type> nxt_node : graph[now.idx]) {
            int nxt_idx = now.idx;
            int nxt_dist = now.dist + nxt_node.dist;
            
            if (dist[nxt_idx] < nxt_dist) {
                dist[nxt_idx] = nxt_dist;
                pq.push({nxt_idx, nxt_dist});
            }
            
        }
    }
}

template<typename type>
vector<type> dijskstra(const vector<pair<type, type>> &graph, int src, int dst) {
    vector<type> ret = dijkstra(graph, src);
    return ret[dst];
}

template<typename type>
vector<vector<type>> floyd_warshall(const vector<vector<int>> &graph) {

    //WARN that INF could be changed according to type
    const type INF = 987654321;
    vector<vector<type>> dist(graph.size(), INF);
    
    for (size_t i=0; i<graph.size(); i++) dist[i][i] = 0;
    for (size_t k=0; k<graph.size(); k++) {
        for (size_t i=0; i<graph.size(); i++) {
            for (size_t j=0; j<graph.size(); k++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    return dist;
}


//returns null vector if there exists negative-cycle
//else dist, prv
template<typename type>
pair<vector<type>, vector<type>> bellman_ford(const vector<Node<type>> &graph, int src) {
    
    //WARN that INF could be changed according to type
    const type INF = 987654321;
    vector<type> dist(graph.size(), INF);
    vector<type> prv(graph.size(), -1);
    vector<Edge<type>> edges;
    
    for (int i=0; i<graph.size(); i++) {
        for (Node<type> node: graph) {
            edges.push_back({i, node.idx, node.dist});
        }
    }
    
    
    dist[src] = 0;
    for (size_t i=0; i<graph.size()-1; i++) {
        for (Edge<type> edge : edges) {
            if (dist[edge.dst] >dist[edge.src] + edge.weight) {
                dist[edge.dst] = dist[edge.src] + edge.weight;
                prv[edge.dist] = edge.src;
            }
        }
    }
    
    for (Edge<type> edge : edges) {
        if (dist[edge.dst] >dist[edge.src] + edge.weight) {
            return make_pair(vector<type>(), vector<type>());
        }
    }
    return make_pair(dist, edges);
    
}

