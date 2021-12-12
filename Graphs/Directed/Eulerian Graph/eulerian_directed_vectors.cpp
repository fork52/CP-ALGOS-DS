#include <bits/stdc++.h>
using namespace std;
  
using ll = long long;
const ll MOD = 1e9 + 7;


template<typename T> 
void disp_vec( vector<T> &arr){
    for(int i = 0; i < arr.size() ; i++){
        cout << arr[i] << " -> ";
    }
    cout << "END\n";
}

/*
    Reference: 
        https://cses.fi/problemset/task/1693
        https://youtu.be/xR4sGgwtR2I
        https://youtu.be/8MpoO2zA2l4
*/
template<typename T1>
class EulerianGraph{
    public:
    vector<vector<T1>> graph;
    vector<ll> indegree, outdegree;
    vector<ll> eulerianPath; // A eulerian Circuit is also an Eulerian Path.
    ll n, more_indegree_node, less_indegree_node;

    /*
        Initializes the EulerianGraph object with the adj_list.
        Calculates indegree and outdegree of all nodes.
    */
    EulerianGraph(vector<vector<T1>>& adj_list){
        n = adj_list.size();
        graph = adj_list;
        indegree.resize(n); outdegree.resize(n);
        for(int node = 0; node < n; node++){
            for(auto nei : graph[node]){
                indegree[nei]++;
                outdegree[node]++;
            }
        }
    }

    /*
        Check if an eulerainCycleExists in a Graph.
        Note that this check doesn't guarantee that a Eulerian cycle exists.
        The graph can be disconnected as well. Won't return false negative though.
    */
    bool eulerainCycleExists(){
        for(int node = 0; node < n; node++){
            if(indegree[node] != outdegree[node]) // All nodes should have equal indegree and outdegree.
                return false;
        }
        return true;
    }

    /*
        Check if an eulerainPathExists in a Graph. Also source and destination nodes if any.
        less_indegree_node - source. more_indegree_node - destination.
        Note that this check doesn't guarantee that a Eulerian path exists. The graph can be disconnected. 
        Won't return false negative though.
    */
    bool eulerainPathExists(){
        ll equals = 0, more_indegree_node_count = 0, less_indegree_node_count = 0;
        more_indegree_node = -1, less_indegree_node = -1;

        for(T1 node = 0; node < n; node++){
            if(indegree[node] == outdegree[node]){
                equals++;
            }
            else if(indegree[node] - outdegree[node] == 1){
                more_indegree_node_count++;
                more_indegree_node = node;
            }
            else if(indegree[node] - outdegree[node] == -1){
                less_indegree_node_count++;
                less_indegree_node = node;
            }
            else{
                return false;
            }
        }
        // All nodes should have equal indegree and outdegree Or exactly two nodes should have odd degree.
        // For one node: indegree[node] - outdegree[node] == 1. (dest)
        // For other node indegree[node] - outdegree[node] == -1 (src)
        return (equals == n) || (equals == n - 2 && more_indegree_node_count == 1 && less_indegree_node_count == 1);
    }


    /*
        Returns if the Eulerian Path/Cycle found visits all the edges in the graph or not.
    */
    bool isEulerianPathOrCycleValid(int total_edges){
        return total_edges == eulerianPath.size() - 1;
    }


    /*
        Uses Hierholzer's algorithm to find eulerian path or circuit.
        Stores the Eulerian path/circuit in the vector eulerianPath.
        Time Complexity: O(n)
    */
    void findEulerianPathOrCycle(T1 src_node){
        vector<vector<T1>> temp_graph = graph;
        eulerianPath.clear();
        _dfs(src_node, temp_graph);
        reverse(eulerianPath.begin(), eulerianPath.end());
    }


    /*
        Performs dfs for finding the eulerian path/cycle.
    */
    void _dfs(T1 node, vector<vector<T1>>& temp_graph){
        while( !temp_graph[node].empty() ){
            T1 nei = temp_graph[node].back(); temp_graph[node].pop_back();
            _dfs(nei, temp_graph);
        }
        eulerianPath.push_back(node);
    }
};


 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, u, v;
    
    n = 5;
    vector<vector<ll>> graph(n, vector<ll>());
    vector<pair<ll, ll>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 0}, {3, 1}};
    m = edges.size();

    for(int i = 0; i < m; i++){
        auto [u, v] = edges[i];
        graph[u].push_back(v);
    }
    
    EulerianGraph obj(graph);
    if(obj.eulerainPathExists() == false){
        cout << "There is no Eulerain Path in the graph\n";
        return 0;
    }
    else{
        cout << "There is a possibility that the graph has a Eulerian path.\n";
    }

    ll srcnode =  obj.less_indegree_node == -1 ? edges[0].first : obj.less_indegree_node;
    obj.findEulerianPathOrCycle(srcnode);
 
    if(!obj.isEulerianPathOrCycleValid(m)){
        cout << "The path/cycle found does not visit all the edges in the graph\n";
        return 0;
    }
    else{
        cout << "The path/cycle found does visit all the edges in the graph\n";
    }

    cout << "Eulerian Path/Cycle found:\n" << "\n";
    disp_vec(obj.eulerianPath);

}