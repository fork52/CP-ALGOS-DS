#include <bits/stdc++.h>
#include "../Trees/UnionFind.cpp"
// #define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
using namespace std;
// Tested on https://binarysearch.com/problems/Friend-Groups
struct UnionFind_Truth
{
	vector<int> parent;
	int components;
	UnionFind_Truth(unsigned int size)
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
int rand_range(int l, int r)
{
	return l + rand() % (r - l + 1);
}
TEST_CASE("Random components")
{
	const int seed = 10;
	const int ARR_SIZE = 1e7;
	const int COMPONENTS = 1e6;
	const int UNION_OPERATIONS = 2 * COMPONENTS / 3;
	srand(seed);
	UnionFind uf(ARR_SIZE);
	UnionFind_Truth uf_truth(ARR_SIZE);
	for (int component = 0; component + COMPONENTS < ARR_SIZE; component += COMPONENTS)
		for (int i = 0; i < UNION_OPERATIONS; i++)
		{
			int a = rand_range(component, component + COMPONENTS), b = rand_range(component, component + COMPONENTS);
			uf.union_set(a, b);
			uf_truth.union_set(a, b);
		}
	REQUIRE(uf.number_of_components() == uf_truth.number_of_components());
}