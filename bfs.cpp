#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <header.h>
#include <fstream>
using namespace std;

class Graph {
public:
	Graph(int n)
	{
		for(int i = 0; i < n; ++i)
		{
			adj[i] = {};
		}
	}
	void add_edge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int> shortest_reach(int start)
	{
		/// num, weight
		std::unordered_map<int, int> res{};
		/// set of prevLevel
		std::unordered_set<int> prevLevel{start};

		std::list<int> currLevel = adj.at(start);
		int curr = 0;
		while(!currLevel.empty())
		{
			++curr;
			std::unordered_set<int> newPrev{};
			std::list<int> newCurr{};

			for(auto in : currLevel)
			{
				if(res.count(in) == 0) { res[in] = curr * 6; }
				for(auto ch : adj.at(in))
				{
					if(prevLevel.count(ch) > 0) continue; /// parent
					newCurr.push_back(ch);
				}
				newPrev.emplace(in);
			}
			currLevel = newCurr;
			prevLevel = newPrev;
		}
		std::vector<int> ans(adj.size());
		for(int i = 0; i < ans.size(); ++i)
		{
			if(i == start)
			{
				ans[i] = 0;
			}
			else if(res.count(i) == 0)
			{
				ans[i] = -1;
			}
			else
			{
				ans[i] = res[i];
			}
		}
		return ans;
	}
private:
	std::unordered_map<int, std::list<int>> adj{};
};

int bfs()
{

	const std::string project = ""; //balanced
	const std::string fileNum = "00";

//	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int queries;
	inStr >> queries;

	for (int t = 0; t < queries; t++) {

		int n, m;
		inStr >> n;
		// Create a graph of size n where each edge weight is 6:
		Graph graph(n);
		inStr >> m;
		// read and set edges
		for (int i = 0; i < m; i++) {
			int u, v;
			inStr >> u >> v;
			u--; v--;
			// add each edge to the graph
			graph.add_edge(u, v);
		}
		int startId;
		inStr >> startId;
		startId--;
		// Find shortest reach from node s
		vector<int> distances = graph.shortest_reach(startId);

		for (int i = 0; i < distances.size(); i++) {
			if (i != startId) {
				cout << distances[i] << " ";
			}
		}
		cout << endl;
	}

	return 0;
}
