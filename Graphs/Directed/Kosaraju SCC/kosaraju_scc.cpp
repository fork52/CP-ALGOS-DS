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

/*
References:
    https://cp-algorithms.com/graph/strongly-connected-components.html
    https://youtu.be/QtdE7QPsWiU
*/

template<typename T1>
class Kosaraju_SCC {
public:

    ll n;
    vector<vector<T1>> graph, rev_graph;
    stack<T1> st;
    vector<vector<T1>> components;
    vector<bool> vis;

    vector<T1> node_to_sccRoot;             // For mapping to node to scc Reperesntative.
    vector<vector<T1>> condensation_graph;

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

    // Step 2: Create the rev copy of the graph
    void _create_reverse_graph(){
        rev_graph = vector<vector<T1>>(n);

        for(T1 u = 0; u < n; u++){
            for(auto v : graph[u]){
                rev_graph[v].push_back(u);
            }
        }
    }

    // Step 3: DFS for finding the components
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
        Stores the components in the 2D vector `components`.
    */
    void find_SCCs(){
        
        vis = vector<bool>(n, false);

        // Random order dfs on the graph
        for(T1 node = 0; node < n; node++){
            if(vis[node] == false){
                _dfs1(node);
            }
        }

        // Create a reversed/transposed copy the graph `rev_graph`
        _create_reverse_graph();
        fill(vis.begin(), vis.end(), false);

        // Perform dfs again in the order present in stack to find SCCs
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
    
    /*
        Call find_SCCs first before generating the condensation graph.
        It is guaranteed that the condensation graph will be a DAG.
    */
    void generate_condensation_graph(){
        int no_of_components = components.size();
        node_to_sccRoot = vector<T1>(n);

        condensation_graph = vector<vector<T1>>(no_of_components);

        for(int c = 0; c < no_of_components; c++){
            for(auto node : components[c]){
                node_to_sccRoot[node] = c;
            }
        }

        for(int node = 0; node < n; node++){
            int sccRoot1 = node_to_sccRoot[node];
            for(auto nei : graph[node]){
                int sccRoot2 = node_to_sccRoot[nei];
                if(sccRoot1 != sccRoot2){
                    condensation_graph[sccRoot1].push_back(sccRoot2);
                }
            }
        }
    }

};

int main(){

    vector<vector<int>> sample_graph = {
        {1},
        {2},
        {0, 4},
        {4},
        {5, 6},
        {3},
        {7},
        {6}
    };

    Kosaraju_SCC<int> obj(sample_graph);

    // Findin the SCCs
    obj.find_SCCs();

    // Generating the condensation graph
    obj.generate_condensation_graph();

    // Printing out the components in each SCC of the graph
    cout << "No of components: " << obj.components.size() << "\n";
    for(int c = 0; c < obj.components.size(); c++){
        disp_vec(obj.components[c]);
    }

    // Printing out the condensation graph. It is guaranteeed to be a DAG.
    cout << "\nCondensation graph : \n";
    for(int c = 0; c < obj.condensation_graph.size(); c++){
        cout << c << " : "; disp_vec(obj.condensation_graph[c]);
    }   


}