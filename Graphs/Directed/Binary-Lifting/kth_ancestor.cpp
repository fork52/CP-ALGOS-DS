#include <vector>
#include <utility>
#include <algorithm>
#include <queue>


/**
 * Reference problem: 
 *  https://cses.fi/problemset/task/1687/
 * 
*/


/*
* Class for finding kth ancestor of a node in a directed graph.
* Assumption: All nodes are labelled between [0, N - 1].
* The 1st ancestor of a node is its direct parent.
*/
class KthAncestorOfNode{
private:
 int N, ROOT;

 // up[node][h] denotes the (2 ^ h)th ancestor of node.
 int **up;

 // The log2 of the maximum depth of the directed tree.
 int LOG_DEPTH;

 // The max Depth of the tree.
 int maxDepth;



public:
    // Stores the depths of the nodes
    std::vector<int> depth;

    /*
    * Constructor
    * @param tree An adjacency list of size N where for each node 
    *       we store its list of children.
    */
    KthAncestorOfNode(const int N, const std::vector<std::vector<int>>& tree){
        this->N = N;
        this->ROOT = findRoot(tree);

        this->depth.resize(N);
        // Calculate depth for all nodes
        this->calculateDepths(ROOT, tree);

        // Calculate max depth
        this->maxDepth = *(std::max_element(depth.begin(), depth.end()));

        // Calculate log depth
        this->LOG_DEPTH = std::max(1, getBinarySize(maxDepth));

        // Create `up` 2D array
        this->up = new int*[N];
        for(int i = 0; i < N; i++){
            this->up[i] = new int[LOG_DEPTH];
        }

        // First Ancestor of ROOT is root itself.
        up[ROOT][0] = ROOT; 

        // Initialize first ancestors
        for(int parent = 0; parent < N; parent++){
            for(auto child: tree[parent]){
                up[child][0] = parent;
            }
        }

        // Populate the up array.
        for(int log_jump = 1; log_jump < LOG_DEPTH; log_jump++){
            for(int node = 0; node < N; node++){
                up[node][log_jump] = up[up[node][log_jump - 1]][log_jump - 1];
            }
        }
    }

    /*
    * Finds the kth ancestor of a node. 
    * Returns -1 if kth ancestor is not available.
    * @param node Node whose kth ancestor needs to be found.
    * @param k Edge distance of the ancestor from node.
    * @returns kth ancestor.
    */
    int findKthAncestor(int node, int k){
        // There is no kth ancestor of node. 
        // The top most ancestor will be root.
        if(depth[node] < k)
            return -1;
        
        int ancestor = node;
        for(int i = 0; i < LOG_DEPTH; i++){
            if((1 << i) & k){
                ancestor = up[ancestor][i];
            }
        }
        return ancestor;
    }   


private:   
    /*
    * Finds the root of the tree. Returns -1 if there is no root.
    * @param tree An adjacency list of size N where for each node 
    *       we store its list of children.
    * @returns Root of the tree
    */
    int findRoot(const std::vector<std::vector<int>>& tree){
        std::vector<int> inDegree(N, 0);
        for(int node = 0; node < N; node++){
            for(auto child: tree[node]){
                inDegree[child]++;
            }
        }

        for(int node = 0; node < N; node++){
            if(inDegree[node] == 0){
                return 0;
            }
        }
        return -1;
    }

    /*
    * Calculates the depth of each node in the tree.
    * Saves the result in depth vector.
    * @param tree An adjacency list of size N where for each node 
    *       we store its list of children.
    */
    void calculateDepths(int root, const std::vector<std::vector<int>>& tree){
        std::queue<std::pair<int, int>> q;
        q.push({ROOT, 0});
        while(!q.empty()){
            auto [node, node_depth] = q.front(); q.pop();
            depth[node] = node_depth;
            for(auto child: tree[node]){
                q.push({child, node_depth + 1});
            }
        }
    }

    /*
    * Returns the binary size of x.
    * Ex: Binary size of 7(0b111) is 3.
    * @param x Integer number.
    */
    int getBinarySize(int x){
        int binarySize = 0;
        while(x){
            binarySize++;
            x >>= 1;
        }
        return binarySize;
    }
};