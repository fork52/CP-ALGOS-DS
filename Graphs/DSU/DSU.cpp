#include <bits/stdc++.h>

using namespace std;

struct DSU{
private:
    vector<int> temp;

public:
    vector<int> parent;
    int n;

    DSU(){}

    DSU(int size){
        parent = vector<int>(size,-1);
        n = size;
    }

    int find_set(int v){
        if(parent[v] < 0){
            return v;
        }

        int cur = v;
        while( parent[cur] >= 0){
            temp.push_back(cur);
            cur = parent[cur];
        }

        while(temp.size()){
            parent[temp.back()] = cur;
            temp.pop_back();
        }
        return cur;
    }

    void union_set(int u, int v){
        int pu = find_set(u);
        int pv = find_set(v);

        if(pu != pv){
            if(parent[pu] > parent[pv])
                swap(pu , pv);

            parent[pu] += parent[pv];
            parent[pv] = pu;
        }
    }

};

int main(){
    int n = 6;
    vector<pair<int,int>> edges = { {1,2} , {2,3} , {4,5} };

    DSU d(n);

    for(auto [u,v] : edges){
        d.union_set(u , v);
    }

    for(int a : d.parent){
        cout << a << " ";
    }

}