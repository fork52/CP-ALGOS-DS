#include <bits/stdc++.h>
using namespace std;

struct UnionFind
{
	vector<int> parent;
	int components;
	UnionFind(unsigned int size)
	{
		parent = vector<int>(size, -1);
		components = size;
	}

	int find_set(int x)
	{
		int root = x;
		while (parent[root] >= 0)
		{
			root = parent[root];
		}

		while (x != root)
		{
			int tmp = parent[x];
			parent[x] = root;
			x = tmp;
		}
		return root;
	}
	int component_size(int a)
	{
		return -parent[find_set(a)];
	}
	int number_of_components()
	{
		return components;
	}
	bool union_set(int a, int b)
	{
		a = find_set(a);
		b = find_set(b);
		if (a == b)
			return false;
		int size_a = -parent[a], size_b = -parent[b];
		if (size_a < size_b)
		{
			swap(a, b);
			swap(size_a, size_b);
		}
		components--;
		parent[b] = a;
		parent[a] -= size_b;
		return true;
	}
};