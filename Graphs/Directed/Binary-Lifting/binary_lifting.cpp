#include "kth_ancestor.cpp"

/*
* Class for find the LCA of two nodes  in a directed tree 
* using binary lifting.
* Assumption: All nodes are labelled between [0, N - 1].
*/
class BinaryLifting{
private:
    int N;
    KthAncestorOfNode* obj;

public:
    BinaryLifting(const int n, const std::vector<std::vector<int>>& tree)
    {
        obj = new KthAncestorOfNode(n, tree);
    }

    int lowestCommonAncestor(int u, int v){
        int depthU = obj->depth[u];
        int depthV = obj->depth[v];

        if(depthU > depthV){
            std::swap(u, v);
            std::swap(depthU, depthV);
        }

        int depthDifference = depthV - depthU;
        v = obj->findKthAncestor(v, depthDifference);

        if(u == v) return u;

        for(int log_depth = 21; log_depth >= 0; log_depth--){
            int ancestorU = obj->findKthAncestor(u, 1 << log_depth);
            int ancestorV = obj->findKthAncestor(v, 1 << log_depth);
            if(ancestorU == ancestorV) continue;

            u = ancestorU, v = ancestorV;
        }

        return obj->findKthAncestor(u, 1);
    }
};