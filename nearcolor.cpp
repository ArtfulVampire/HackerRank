#include <bits/stdc++.h>
#include <header.h>

using namespace std;


// Complete the findShortest function below.

/*
 * For the unweighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] to <name>_to[i].
 *
 */
int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<long> ids, long val)
{
	std::unordered_map<int, std::list<int>> adjacency{};
	for(int i = 0; i < graph_from.size(); ++i)
	{
		adjacency[graph_from[i]].push_back(graph_to[i]);
		adjacency[graph_to[i]].push_back(graph_from[i]);
		for(const auto & in : adjacency)
		{
			std::cout << in.first << " -> ";
			for(auto in2 : in.second)
			{
				std::cout << in2 << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}


	/// nums
	std::unordered_set<int> prevLevel{};
	for(int i = 0; i < ids.size(); ++i)
	{
		if(ids[i] == val && adjacency.count(i + 1) > 0)
		{
			prevLevel.emplace(i + 1);
		}
	}
	std::cout << "prevLevel:" << std::endl;
	for(const auto & in : prevLevel)
	{
		std::cout << in << " ";
	}
	std::cout << std::endl;

	if(prevLevel.size() < 2)
	{
		return -1;
	}

	/// num, weight
	std::unordered_map<int, long> passed{};
	for(const auto & in : prevLevel)
	{
		passed[in] = 0l;
	}

	std::list<int> currLevel{};
	for(const auto & in : prevLevel)
	{
		currLevel.splice(std::begin(currLevel), adjacency.at(in));
	}
	std::cout << currLevel << std::endl;

	long curr = 0; /// weight
	while(true) /// condition inside
	{
		std::unordered_set<int> newPrev{}; /// nums
		std::list<int> newCurr{}; /// nums
		std::set<int> possible{};
		for(const auto & in : currLevel)
		{
			std::cout << in << ":" << std::endl;
			if(passed.count(in) > 0)
			{
				std::cout << passed.at(in) << " " << curr << std::endl;
				possible.emplace(passed.at(in) + curr + 1);
			}
			else
			{
				passed[in] = curr + 1;
			}
			newPrev.emplace(in);

			for(const auto & ch : adjacency.at(in))
			{
				if(prevLevel.count(ch) > 0) continue; /// parent
				newCurr.push_back(ch);
			}
		}
		if(!possible.empty())
		{
			for(const auto & in : possible)
			{
				std::cout << in << " ";
			}
			std::cout << std::endl;

			return *std::begin(possible);
		}
		prevLevel = newPrev;
		currLevel = newCurr;
		++curr;
	}
	return -1;
}

int near()
{
	const std::string project = ""; //
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int graph_nodes;
	int graph_edges;

	inStr >> graph_nodes >> graph_edges;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> graph_from(graph_edges);
	vector<int> graph_to(graph_edges);

	for (int i = 0; i < graph_edges; i++) {
		inStr >> graph_from[i] >> graph_to[i];
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	string ids_temp_temp;
	getline(inStr, ids_temp_temp);

	vector<string> ids_temp = split_string(ids_temp_temp);

	vector<long> ids(graph_nodes);

	for (int i = 0; i < graph_nodes; i++) {
		long ids_item = stol(ids_temp[i]);

		ids[i] = ids_item;
	}

	long val;
	inStr >> val;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	int ans = findShortest(graph_nodes, graph_from, graph_to, ids, val);

	fout << ans << "\n";

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
