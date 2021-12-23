#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

using ll = long long;
const ll MOD = 1e9 + 7;

template<typename T>
vector<T> input_array( int n ){
    vector<T> arr;
    T t;
    for (int i = 0; i < n; i++){
        cin >> t;
        arr.push_back(t);
    }
    return arr;
}

template<typename T> 
void disp_vec( vector<T> &arr){
    for(int i=0; i<arr.size() ; i++){
        cout << ++arr[i] << " ";
    }
    cout << "\n";
}


template<typename T>
class Kahns_Algo{
    public:
    vector<T> order, indegree;
    vector<vector<T>> graph;
    T n, E;
    bool isCyclic;
    
    /*Input: Adjacency List and Number of edges in the graph*/
    Kahns_Algo(vector<vector<T>>& adj_list, T edges){
        graph = adj_list;
        n = adj_list.size();
        E = edges;                 // no of edges in the graph
    }
    

    /*
        Then function can detect cycles in the graph too.
    */
    void findTopOrder(){
        order.resize(n);            // The topological ordering of the graph
        indegree.resize(n);         // Indegree of nodes
        
        for(int u = 0; u < n; u++){
            for(auto v: graph[u])
                indegree[v]++;        
        }
        
        queue<int> q;
        for(int node = 0; node < n; node++){
            if(indegree[node] == 0){
                q.push(node);
            }
        }
        
        int ind = n - 1, visitedEdgeCount = 0;
        while(!q.empty()){
            T node = q.front(); q.pop();
            order[ind--] = node;

            for(auto nei: graph[node]){
                indegree[nei]--;
                visitedEdgeCount++;
                if(indegree[nei] == 0){
                    q.push(nei);
                }
            }
        }

        // Needs to be checked before outputing the topological ordering.
        // if isCyclic is True, then the topological ordering does not exist.
        isCyclic = (E == visitedEdgeCount); 
    }
};


int main(){
	int n, m, u1, v1;

}