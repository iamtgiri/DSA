#include <bits/stdc++.h>
using namespace std;

const int A = 1e6 + 69;
int spf[A];

// --------------------------------------------------------------
// STEP 1 — Build SPF using modified sieve
// --------------------------------------------------------------
void build_spf()
{
	for (int i = 2; i < A; i++)
	{
		if (spf[i] == 0)
		{
			// i is prime
			spf[i] = i;
			if (i > A / i)
				continue;
			for (int j = i * i; j < A; j += i)
			{
				if (spf[j] == 0)
					spf[j] = i;
			}
		}
	}
}

// --------------------------------------------------------------
// Factorize x using SPF and return unique prime factors
// --------------------------------------------------------------
vector<int> get_prime_factors(int x)
{
	vector<int> primes;
	while (x > 1)
	{
		int p = spf[x];
		primes.push_back(p);
		while (x % p == 0)
			x /= p;
	}
	return primes;
}

// --------------------------------------------------------------
// STEP 3 — Build graph edges from prime-factor groups
// --------------------------------------------------------------
void build_graph(vector<vector<int>> &adj, vector<vector<int>> &at)
{
	for (int p = 1; p < A; p++)
	{
		if (!at[p].empty())
		{
			int sz = at[p].size();
			for (int j = 0; j < sz; j++)
			{
				int u = at[p][j];
				int v = at[p][(j + 1) % sz];
				adj[u].push_back(v);
				adj[v].push_back(u);
			}
		}
	}
}

// --------------------------------------------------------------
// BFS to compute component size and fill results
// --------------------------------------------------------------
void bfs_component(int start, vector<bool> &vis,
				   vector<vector<int>> &adj, vector<int> &ans)
{
	queue<int> q;
	vector<int> comp;

	q.push(start);
	vis[start] = true;

	int cnt = 0;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		comp.push_back(u);
		cnt++;

		for (int v : adj[u])
		{
			if (!vis[v])
			{
				vis[v] = true;
				q.push(v);
			}
		}
	}

	// assign component size
	for (int x : comp)
		ans[x] = cnt;
}

// --------------------------------------------------------------
// MAIN
// --------------------------------------------------------------
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	build_spf();

	int n;
	cin >> n;

	vector<vector<int>> at(A);		// prime → list of indices
	vector<vector<int>> adj(n + 1); // adjacency list

	// Read input and map indices by prime factors
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;

		vector<int> primes = get_prime_factors(x);
		for (int p : primes)
		{
			at[p].push_back(i);
		}
	}

	build_graph(adj, at);

	vector<bool> vis(n + 1, false);
	vector<int> ans(n + 1);

	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
			bfs_component(i, vis, adj, ans);
	}

	for (int i = 1; i <= n; i++)
	{
		cout << ans[i] << (i == n ? '\n' : ' ');
	}
}
