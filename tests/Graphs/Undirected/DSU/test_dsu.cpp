#include "gtest/gtest.h"
#include "../../../../Graphs/Undirected/DSU/dsu.cpp"

struct UnionFind_Truth
{
	std::vector<int> parent;
	int components;
	UnionFind_Truth(unsigned int size)
	{
		parent = std::vector<int>(size, -1);
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
			std::swap(a, b);
			std::swap(size_a, size_b);
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


// Test UNION FIND
TEST(UnionFind, RandomizedTest) {
	const int seed = 10;
	const int ARR_SIZE = 1e7;
	const int COMPONENTS = 1e6;
	const int UNION_OPERATIONS = 2 * COMPONENTS / 3;
	srand(seed);
	DSU uf(ARR_SIZE);
	UnionFind_Truth uf_truth(ARR_SIZE);
	for (int component = 0; component + COMPONENTS < ARR_SIZE; component += COMPONENTS)
		for (int i = 0; i < UNION_OPERATIONS; i++)
		{
			int a = rand_range(component, component + COMPONENTS), b = rand_range(component, component + COMPONENTS);
			EXPECT_EQ(uf.union_set(a, b), uf_truth.union_set(a, b));			
		}

	EXPECT_EQ(uf.number_of_components(), uf_truth.number_of_components());
}
