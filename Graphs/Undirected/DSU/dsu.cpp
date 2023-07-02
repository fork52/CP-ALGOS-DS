#include <vector>
#include <utility>

struct DSU{
private:
    std::vector<int> temp;

public:
    std::vector<int> parent;
    int n;
    int components;

    DSU(){}

    DSU(int size){
        parent = std::vector<int>(size,-1);
        n = components = size;
    }

    int find_set(int v){
        if(parent[v] < 0){
            return v;
        }

        int cur = v;
        while(parent[cur] >= 0){
            temp.push_back(cur);
            cur = parent[cur];
        }

        while(temp.size()){
            parent[temp.back()] = cur;
            temp.pop_back();
        }
        return cur;
    }

    bool union_set(int u, int v){
        int pu = find_set(u);
        int pv = find_set(v);

        if(pu != pv){
            if(parent[pu] > parent[pv])
                std::swap(pu , pv);

            parent[pu] += parent[pv];
            parent[pv] = pu;

            components--;
            return true;
        }
        return false;
    }

    int component_size(int a){
		return -parent[find_set(a)];
	}

    int number_of_components(){
		return components;
	}
};

// int main(){
//     int n = 6;
//     std::vector<pair<int,int>> edges = { {1,2} , {2,3} , {4,5} };

//     DSU d(n);

//     for(auto [u,v] : edges){
//         d.union_set(u , v);
//     }

//     for(int a : d.parent){
//         cout << a << " ";
//     }

// }