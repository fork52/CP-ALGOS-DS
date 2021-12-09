#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;

template<typename T> 
void disp_vec( vector<T> &arr){
    for(int i = 0; i < arr.size() ; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
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
    vector<ll> degree;
    vector<ll> eulerianPath; // A eulerian Circuit is also an Eulerian Path.
    ll n;

    /*
        Initializes the EulerianGraph object with the adj_list.
        Calculates degree of all nodes.
    */
    EulerianGraph(vector<vector<T1>>& adj_list){
        n = adj_list.size();
        graph = adj_list;
        degree.resize(n);
        for(int node = 0; node < n; node++)
            degree[node] = graph[node].size();
    }

    /*
        Check if an eulerainCycleExists in a Graph.
        Note that this check doesn't guarantee that a Eulerian cycle exists.
        The graph can be disconnected as well. Won't return false negative though.
    */
    bool eulerainCycleExists(){
        for(int node = 0; node < n; node++){
            if(degree[node] & 1) // all nodes should have even degree
                return false;
        }
        return true;
    }

    /*
        Check if an eulerainPathExists in a Graph.
        Note that this check doesn't guarantee that a Eulerian path exists.
        The graph can be disconnected. Won't return false negative though.
    */
    bool eulerainPathExists(){
        int odd_count = 0;
        for(int node = 0; node < n; node++){
            odd_count += degree[node] & 1;
        }
        // exactly two nodes or zero nodes should have odd degrees.   
        return (odd_count == 0 || odd_count == 2);
    }

    /*
        Finds a node in the graph which has odd degree.
        Returns -1 if such a node does not exist.
    */
    int getNodeWithOddDegree(){
        for(int node = 0; node < n; node++){
            if( degree[node] & 1) return node;
        }  
        return -1; 
    }

    /*
        Returns if the Eulerian Path/Cycle found visits all the edges in 
        the graph or not.
    */
    bool isEulerianPathOrCycleValid(int total_edges){
        return total_edges == eulerianPath.size() - 1;
    }

    /*
        Uses Hierholzer's algorithm to find eulerian path or circuit.
        Stores the Eulerian path/circuit in the vector eulerianPath.
        Time Complexity: O(n * log(n) )
        log(n) Factor is there because we are using set for making edges as visited.
    */
    void findEulerianPathOrCycle(T1 src_node){
        vector<vector<T1>> temp_graph = graph;
        eulerianPath.clear();
        set<pair<T1, T1>> vis;
        _dfs(src_node, temp_graph, vis);
        std :: reverse(eulerianPath.begin(), eulerianPath.end());
    }

    /*
        Performs dfs for finding the eulerian path/cycle.
    */
    void _dfs(T1 node, vector<vector<T1>>& temp_graph, set<pair<T1, T1>>& vis){
        while( !temp_graph[node].empty() ){
            T1 nei = temp_graph[node].back(); temp_graph[node].pop_back();
            T1 u = min(node, nei);
            T1 v = max(node, nei);

            if(vis.count({u, v}) == 0){
                vis.insert({u, v});
                _dfs(nei, temp_graph, vis);
            }

        }
        eulerianPath.push_back(node);
    }
};

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    
    vector<vector<ll>> graph = {
            {1}, {0}
    };

    EulerianGraph obj(graph);

    cout << "Eulerian Cycle exists: " << obj.eulerainCycleExists() << endl;
    cout << "Eulerian Path exists: " << obj.eulerainPathExists() << endl;

    cout << "Eulerian Path/Cycle:";
    obj.findEulerianPathOrCycle(0);
    disp_vec(obj.eulerianPath);
    cout << "\n";

    // perform this extra check to make sure that all the edges are being visisted.
    int total_edges = 1;
    if(obj.isEulerianPathOrCycleValid(total_edges)){
        cout << "The path found visits all the edges and is a valid Eulerian path.";
    }
    else{
        cout << "The path found does not visit all the edges and is an invalid Eulerian path.";
    }

}