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

class TreeNode{
public:
    ll id;
    TreeNode *parent;
    vector<TreeNode*> children;
 
    /*
        Intializes the node_id and parentPtr for node
    */
    TreeNode(ll node_id = 0, TreeNode* parentPtr = nullptr)
        :id(node_id), parent(parentPtr)
    {
    }
 
    /*
        Roots the undirected tree `graph` with the root as the node 
        with id as `rootId.
        `graph` is a adjacency list.
        `rootId` is the id of the node you want as root.
    */
    static TreeNode *rootTree(vector<vector<ll>>& graph, ll rootId){
        TreeNode* root = new TreeNode(rootId);
        return __buildTree(graph, root, nullptr);
    }
    
    /*
        Utlity method for recurisve building the n-ary tree.
    */
    static TreeNode* __buildTree(vector<vector<ll>>& graph, TreeNode *node, TreeNode* parent){
        for(auto childId : graph[node -> id]){
            if(parent != nullptr && childId == parent -> id)
                continue;
 
            TreeNode* childPtr = new TreeNode(childId, node);
            node -> children.push_back(childPtr);
            __buildTree(graph, childPtr, node);
        }
        return node;
    }

    /*
        Utility function to find the centers of an undirected tree graph.
    */
    static vector<int> findCenters(int n, vector<vector<ll>>& graph) {
        vector<int> degree(n, 0);
        
        queue<int> q;
        for(int node = 0; node < n; node++){
            degree[node] = graph[node].size();
            if(degree[node] <= 1){
                q.push(node);
            }    
        }
        
        vector<int> candidate_centers;
        while(!q.empty()){
            candidate_centers.clear();
            int sz = q.size();
            
            for(int i = 0; i < sz; i++){
                int node = q.front(); q.pop();
                candidate_centers.push_back(node);
                
                for(auto nei : graph[node]){
                    degree[nei]--;
                    if(degree[nei] == 1){
                        q.push(nei);
                    }
                }
            }
        }
        return candidate_centers;
    }
};


int main(){
    vector<vector<ll>> graph = {
        {1},{0, 2},{1, 3}, {2}
    };

    // Root the tree with root node as node with `0`.
    TreeNode* root = TreeNode::rootTree(graph, 0ll);

    // Find the centers of a undirected graph which is a tree
    vector<int> centers = TreeNode::findCenters(graph.size(), graph);

    cout << "Centers are:";
    disp_vec(centers);
    return 0;
}