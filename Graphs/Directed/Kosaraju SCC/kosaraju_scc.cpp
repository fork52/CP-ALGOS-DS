#include <bits\stdc++.h>

using namespace std;
using ll = long long;


template<typename T1>
void disp_vec(vector<T1> arr){
    int n = arr.size();
    for(auto a: arr){
        cout << a << " ";
    }
    cout << "\n";
}


template<typename T1>
class Kosaraju_SCC {
public:

    ll n;
    vector<vector<T1>> graph;
    stack<T1> st;
    vector<vector<T1>> components;
    vector<vector<T1>> rev_graph;
    vector<bool> vis;

    Kosaraju_SCC(vector<vector<T1>> &adj_list){
        n = adj_list.size();
        graph = adj_list;
    }

    // Step 1: DFS to populate the stack
    void _dfs1(T1 node){
        vis[node] = true;
        for(auto nei : graph[node]){
            if(vis[nei] == false){
                _dfs1(nei);
            }
        }

        st.push(node);
    }

    void _create_reverse_graph(){
        rev_graph = vector<vector<T1>>(n);

        for(T1 u = 0; u < n; u++){
            for(auto v : graph[u]){
                rev_graph[v].push_back(u);
            }
        }
    }

    // STEP 2: DFS for finding the components
    void _dfs2(T1 node, int comp_ind){
        vis[node] = true;
        components[comp_ind].push_back(node);

        for(auto nei : rev_graph[node]){
            if(vis[nei] == false){
                _dfs2(nei, comp_ind);
            }
        }
    }

    /*
        Finds the Strongly connected components in the directed graph.
        Stores the compenents in the 2D vector components
    */
    void find_SCCs(){
        
        vis = vector<bool>(n, false);
        // Random order dfs
        for(T1 node = 0; node < n; node++){
            if(vis[node] == false){
                _dfs1(node);
            }
        }

        // Reverse the graph
        _create_reverse_graph();
        fill(vis.begin(), vis.end(), false);

        // Perform dfs again in order present in stack to find SCCs
        int component_index = 0; 
        while(!st.empty()){
            T1 node = st.top(); st.pop();
            if(vis[node] == false){
                components.push_back(vector<T1>());
                _dfs2(node, component_index);
                component_index++;
            }
        }
    }
};

int main(){
    vector<vector<int>> graph = {
        {1},
        {2},
        {0, 4},
        {4},
        {5},
        {3},
        {7},
        {6}
    };

    Kosaraju_SCC<int> obj(graph);
    obj.find_SCCs();

    for(int c = 0; c < obj.components.size(); c++){
        disp_vec(obj.components[c]);
    }

}