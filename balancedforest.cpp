#include <bits/stdc++.h>
#include <header.h>

using namespace std;

using adjType = std::unordered_map<int, std::unordered_set<int>>;
using weightType = long;

/// sum weight and a set (vector? list?) of children
struct weight
{
	int vertex;
	int parent;
	weightType value;
	weight(int ver, int par, weightType val) : vertex{ver}, parent{par}, value{val} {}
};

bool operator< (const weight & in1, const weight & in2)
{
	return in1.value < in2.value;
}
bool operator== (const weight & in1, const weight & in2)
{
	return in1.value == in2.value;
}

std::set<weight> weightsOf(int vertex, int parent, const adjType & adj, const vector<weightType> & weights)
{
	if(adj.at(vertex).size() == 1) /// next is another leaf
	{
		return { weight(vertex, parent, weights[vertex - 1]) }; /// 1-based
	}

	std::set<weight> res{};
	weightType itsW{0};
	for(auto child : adj.at(vertex))
	{
		if(child == parent) continue;

		auto subW = weightsOf(child, vertex, adj, weights);
		auto it = std::end(subW); --it;
		itsW += it->value;
		res.insert(std::begin(subW), std::end(subW));
	}
	itsW += weights[vertex - 1];
	res.emplace(weight(vertex, parent, itsW));
	return res;
}

bool checkAncestor(int vertex, int parent, const adjType & adj, int child)
{

	for(auto ch : adj.at(vertex))
	{
		if(ch == parent) continue;
		if(ch == child) return true;
		if(checkAncestor(ch, vertex, adj, child)) return true;
	}
	return false;
}

bool contains(const std::set<weight> & wts, weightType in)
{
	return std::find_if(std::begin(wts), std::end(wts),
						[in](const weight & a){ return a.value == in; }) != std::end(wts);
}

bool count(const std::set<weight> & wts, weightType in)
{
	return std::count_if(std::begin(wts), std::end(wts),
						 [in](const weight & a){ return a.value == in; });
}

weight get(const std::set<weight> & wts, weightType in)
{
	return *std::find_if(std::begin(wts), std::end(wts),
						[in](const weight & a){ return a.value == in; });
}

// Complete the balancedForest function below.
int balancedForest(vector<weightType> weights, const vector<vector<int>> & edges)
{
	adjType adjacency{};
	for(auto edge : edges)
	{
		adjacency[edge[0]].emplace(edge[1]);
		adjacency[edge[1]].emplace(edge[0]);
	}
	const weightType sumWeight = std::accumulate(std::begin(weights), std::end(weights), 0);

	int leaf{0}; /// some leaf
	for(const auto & in : adjacency)
	{
		if(in.second.size() == 1)
		{
			leaf = in.first;
			break;
		}
	}
	int next = *std::begin(adjacency[leaf]);
	const auto wtss = weightsOf(next, leaf, adjacency, weights);


	std::cout << "adjacency:" << std::endl;
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

	std::cout << "leaf = " << leaf << std::endl;
	std::cout << "next = " << next << std::endl;

	std::cout << "weights:" << std::endl;
	for(const auto & in : wtss)
	{
		std::cout << in.value << " ";
	}
	std::cout << std::endl;


	const int rem = (2 * sumWeight) % 3;
	std::cout << "sumWeight = " << sumWeight << std::endl;
	std::cout << "rem = " << rem << std::endl;
	for(int newVal = rem; newVal <= sumWeight / 2; newVal += 3)
	{
		const int each = (sumWeight + newVal) / 3;
		std::cout << "each = " << each << std::endl;

		if(count(wtss, each) == 2) return newVal; /// two different each

		if(contains(wtss, each)
		   && contains(wtss, each + each - newVal)
		   && checkAncestor(get(wtss, each + each - newVal).vertex,
							get(wtss, each + each - newVal).parent,
							adjacency,
							get(wtss, each).vertex)
		   ) return newVal;
		/// add for_each
		if(contains(wtss, each - newVal)
		   && contains(wtss, each + each - newVal)
		   && checkAncestor(get(wtss, each + each - newVal).vertex,
							get(wtss, each + each - newVal).parent,
							adjacency,
							get(wtss, each - newVal).vertex)
		   ) return newVal;

		/// add for_each
		if(contains(wtss, each)
		   && contains(wtss, each - newVal)
		   && !checkAncestor(get(wtss, each).vertex,
							 get(wtss, each).parent,
							 adjacency,
							 get(wtss, each - newVal).vertex)
		   ) return newVal;
	}
	return -1;

}

int balance()
{
	const std::string project = "";
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		int n;
		inStr >> n;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');

		string c_temp_temp;
		getline(inStr, c_temp_temp);

		vector<string> c_temp = split(c_temp_temp);

		vector<weightType> c(n);

		for (int i = 0; i < n; i++) {
			int c_item = stoi(c_temp[i]);

			c[i] = c_item;
		}

		vector<vector<int>> edges(n - 1);
		for (int i = 0; i < n - 1; i++) {
			edges[i].resize(2);

			for (int j = 0; j < 2; j++) {
				inStr >> edges[i][j];
			}

			inStr.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		int result = balancedForest(c, edges);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
