#include <bits/stdc++.h>
using namespace std;

/*
	References:
		https://trykv.medium.com/algorithms-on-graphs-directed-graphs-and-cycle-detection-3982dfbd11f5

	Related Problem: 
		https://binarysearch.com/problems/Course-Scheduling

*/


/*
	Assumptions:
		- Adjacency list is of size n where n is the number of nodes.
*/
template<typename T1>
struct Graph
{
	enum node_status
	{
		unvisited = 0,
		explore = 1,
		visited = 2
	};

	vector<vector<T1>> graph;
	vector<node_status> status;
	
	/*
		Initializes the graph with adjacency list passed.
		Intitializes the status array to unvisited for all nodes.
		Time: O(n)   
		Space: O(n)
	*/
	Graph(vector<vector<T1>> &adj_list)
	{
		graph = adj_list;
		status.assign(adj_list.size(), unvisited);
	}

	/*
		Performs DFS on the node to check back-edges.
	*/
	bool has_back_edge(int node)
	{
		if (status[node] == visited)
			return false;
		if (status[node] == explore)
			return true;
		status[node] = explore;
		for (auto const &neigh : graph[node])
			if (has_back_edge(neigh))
				return true;
		status[node] = visited;
		return false;
	}

	/*
		Returns whether the graph is cyclic.
	*/
	bool is_cyclic()
	{
		for (int node = 0; node < graph.size(); node++)
			if(has_back_edge(node))
				return true;
		return false;
	}
};



int main(){
	vector< vector<int> > adj = {{0}};
	Graph<int> g(adj);
	cout << g.is_cyclic();
}