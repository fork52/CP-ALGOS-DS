#include <bits/stdc++.h>
#include "../Advanced Data Structures/Fenwick Trees/fenwick_PQRU.cpp"
#include "catch.hpp"
using namespace std;

TEST_CASE("Operations on entire array")
{
	const int n = 1000;
	vector<int> arr(n);
	iota(arr.begin(), arr.end(), 1);
	Fenwick_Tree_PQRU<int> ft(arr);

	SECTION("Increment +1")
	{
		ft.range_update(1, n, 1);
		for (int i = 0; i < n; i++)
		{
			REQUIRE(ft.point_query(i + 1) == arr[i] + 1);
		}
	}
	SECTION("Decrement -1")
	{
		ft.range_update(1, n, -1);
		for (int i = 0; i < n; i++)
		{
			REQUIRE(ft.point_query(i + 1) == arr[i] - 1);
		}
	}

	SECTION("No change")
	{
		ft.range_update(1, n, 0);
		for (int i = 0; i < n; i++)
		{
			REQUIRE(ft.point_query(i + 1) == arr[i]);
		}
	}

	SECTION("From -100 to 100")
	{
		int total = 0;
		for (int delta = -100; delta <= 100; delta++)
		{
			ft.range_update(1, n, delta);
			total += delta;
			for (int i = 0; i < n; i++)
			{
				REQUIRE(ft.point_query(i + 1) == arr[i] + total);
			}
		}
	}
}