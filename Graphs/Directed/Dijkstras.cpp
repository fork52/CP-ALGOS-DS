#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<pair<ll, ll>>;

template<typename T1>
void disp_vec(vector<T1> arr){
    for(auto a: arr){
        cout << a << " ";
    }
    cout << "\n";
}

/*
    Class for applying Dijkstras algorithm.
    Reference problem: https://cses.fi/problemset/task/1671
*/
class Dijkstras{
public:
    ll V;
    vector<vector<pair<ll, ll>>> graph;
    vector<bool> vis;
    vector<ll> dist;
    const ll INF = 1e17;

    /*
        V : Number of nodes in the graph
        graph : Adjaceny list with each vector of form 
                {(node1, weight1), (node1, weight1) ... }
    */
    Dijkstras(ll V, vector<vector<pair<ll, ll>>>& graph){
        this -> V = V;
        this -> graph = graph;

        vis = vector<bool>(V, false);
        dist = vector<ll>(V, INF);
    }

    /*
        Lazy implementation of Dijkstras algorithm.
        Time Complexity : O((E + V).log(E + V))
        The shortest distances are stored in the dist array.
    */
    void find_shortest_path(ll src){
        using p = pair<ll, ll>;  // Store (dist, node)
        priority_queue<p, vector<p>, greater<p>> pq;
        ll new_dist;

        pq.push({0, src});
        dist[src] = 0; 

        while(!pq.empty()){
            auto [cur_dist, node] = pq.top(); pq.pop();
            if(vis[node]) continue;
            vis[node] = 1;
            
            for(auto [nei, w] : graph[node]){
                if(vis[nei]) continue;
                new_dist = cur_dist + w;
                if(new_dist < dist[nei]){
                    dist[nei] = new_dist;
                    pq.push({new_dist, nei});
                }
            }
        }   
    }

};

int main(){
    ll V, E;
    cin >> V >> E;
    ll u, v, w;

    vector<vll> graph(V);
    for(int i = 0; i < E; i++){
        cin >> u >> v >> w;  // Read (u, v, w)
        u--; v--;
        graph[u].push_back({v, w});
    }

    Dijkstras obj(V, graph);
    obj.find_shortest_path(0);
    disp_vec(obj.dist);
}