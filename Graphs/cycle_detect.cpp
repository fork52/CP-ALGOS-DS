#include <bits/stdc++.h>
using namespace std;
// https://trykv.medium.com/algorithms-on-graphs-directed-graphs-and-cycle-detection-3982dfbd11f5
// https://binarysearch.com/problems/Course-Scheduling
struct Graph
{
	enum node_status
	{
		unvisited = 0,
		explore = 1,
		visited = 2
	};
	vector<vector<int>> graph;
	vector<node_status> status;
	Graph(vector<vector<int>> &adj_list)
	{
		graph = adj_list;
		status.assign(adj_list.size(), unvisited);
	}
	bool dfs(int node)
	{
		if (status[node] == visited)
			return false;
		if (status[node] == explore)
			return true;
		status[node] = explore;
		for (auto const &neigh : graph[node])
			if (dfs(neigh))
				return true;
		status[node] = visited;
		return false;
	}
	bool check_cycle()
	{
		for (int i = 0; i < graph.size(); i++)
			if (dfs(i))
				return true;
		return false;
	}
};
bool solve(vector<vector<int>> &courses)
{
	auto g = Graph(courses);
	return !g.check_cycle();
}