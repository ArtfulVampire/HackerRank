#include <bits/stdc++.h>
#include <header.h>

using namespace std;

using adjType = std::unordered_map<int, std::unordered_set<int>>;
using weightType = long;

/// sum weight and a set (vector? list?) of children
std::pair<weightType, std::list<int>> weightOf(int vertex, int parent, const adjType & adj, const vector<weightType> & weights)
{
	weightType res = weights[vertex - 1]; /// 1-based
	std::list<int> outSet{vertex};
	for(auto child : adj.at(vertex))
	{
		if(child == parent) continue;

		auto pew = weightOf(child, vertex, adj, weights);
		res += pew.first;
		outSet.splice(std::end(outSet), pew.second);
	}
	return {res, outSet};
}

// Complete the balancedForest function below.
int balancedForest(vector<weightType> weights, const vector<vector<int>> & edges)
{
	adjType adjacency{};
	std::map<int, std::unordered_set<int>, greater<int>> degrees{}; /// degree, set of vertices
	for(auto edge : edges)
	{
		if(degrees.count(adjacency[edge[0]].size()) > 0)
		{
			degrees[adjacency[edge[0]].size()].erase(edge[0]);
		}
		if(degrees.count(adjacency[edge[1]].size()) > 0)
		{
			degrees[adjacency[edge[1]].size()].erase(edge[1]);
		}
		adjacency[edge[0]].emplace(edge[1]);
		adjacency[edge[1]].emplace(edge[0]);
		degrees[adjacency[edge[0]].size()].emplace(edge[0]);
		degrees[adjacency[edge[1]].size()].emplace(edge[1]);
	}

	auto printAdj = [&adjacency, &weights]()
	{
		std::cout << "adjacency:" << std::endl;
		for(const auto & in : adjacency)
		{
			std::cout << in.first << " -> ";
			for(auto in2 : in.second)
			{
				std::cout << in2 << " ";
			}
			std::cout << "\t\t" << weights[in.first - 1];
			std::cout << std::endl;
		}
		std::cout << std::endl;
	};

	auto printDeg = [&degrees]()
	{
		std::cout << "degrees:" << std::endl;
		for(const auto & in : degrees)
		{
			std::cout << in.first << " -> ";
			for(auto in2 : in.second)
			{
				std::cout << in2 << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	};

	printAdj();
	printDeg();

	const weightType sumWeight = std::accumulate(std::begin(weights), std::end(weights), 0);

	while(std::begin(degrees)->first > 2)
	{
		const int currVertex = *(std::begin(std::begin(degrees)->second)); /// some vertex with max dgree
		std::cout << currVertex << std::endl;
		std::vector<std::tuple<weightType, std::list<int>, int>> wts{}; /// weigths of children, is the third item needed?
		for(auto child : adjacency.at(currVertex))
		{
			auto pew = weightOf(child, currVertex, adjacency, weights);
			wts.push_back({pew.first, pew.second, child});
		}
		std::sort(std::begin(wts), std::end(wts), [](const auto & in1, const auto & in2)
		{ return std::get<0>(in1) > std::get<0>(in2); }); /// heavy first

		std::cout << std::get<0>(wts[0]) << " " << std::get<0>(wts[1]) << " " << std::get<0>(wts[2]) << std::endl;
		std::cout << std::get<1>(wts[0]) << "\n" << std::get<1>(wts[1]) << "\n" << std::get<1>(wts[2]) << std::endl;


		int numBranchLeft = wts.size(); /// nothing to add

		/// one very heavy branch
		if(std::get<0>(wts[0]) >= std::ceil(2 * sumWeight / 3)) { numBranchLeft = 1; }

		/// two quite heavy branches
		if(std::get<0>(wts[0]) >= std::ceil(sumWeight / 3)
		   && std::get<0>(wts[1]) >= std::ceil(sumWeight / 3))
		{
			numBranchLeft = 2;
		}

		/// what if only one quite heavy? ///////////


		   /// add weights to the currVertex, fix adjacecy and degrees

		   degrees[adjacency[currVertex].size()].erase(currVertex);
		for(int j = numBranchLeft; j < wts.size(); ++j) /// j < adjacency[currVertex].size()
		   {
			   weights[currVertex - 1] += std::get<0>(wts[j]); /// 1-based
			   adjacency[currVertex].erase(std::get<2>(wts[j]));
			   for(auto in : std::get<1>(wts[j]))
			   {
				   degrees[adjacency[in].size()].erase(in);
				   adjacency.erase(in);
			   }
		   }
		   degrees[numBranchLeft].insert(currVertex);

		/// the degrees were cahnged, maybe zeroed
		for(auto it = std::begin(degrees); it != std::end(degrees); ++it)
		{
			if(it->second.empty()) { degrees.erase(it); }
		}
	}

	/// Check:
	printAdj();
	printDeg();

	// now we have "a stick" - a single line
	// it has two "leaves" with degree = 1
	/// place
	/// make initial paths from leaves
	/// can be another func
	std::vector<int> vec{};
	vec.reserve(degrees[1].size() + degrees[2].size());
	int leaf = *std::begin(degrees[1]);
	if(adjacency[leaf].size() != 1) { std::cout << "wrong leaf adjacency" << std::endl; }
	int routePrev{leaf};
	int routeEnd{*(std::begin(adjacency[leaf]))}; /// not inclusive
	vec.push_back(weights[leaf - 1]); /// 1-based

	while(adjacency[routeEnd].size() == 2)
	{
		vec.push_back(weights[routeEnd - 1]); /// 1-based
		auto it = std::begin(adjacency[routeEnd]);
		int v1 = *it; ++it; int v2 = *it;
		int newEnd = (v1 == routePrev) ? v2 : v1;
		routePrev = routeEnd;
		routeEnd = newEnd;
	}
	/// final leaf
	vec.push_back(weights[routeEnd - 1]); /// 1-based

	std::cout << vec << std::endl;


	/// to other func
	/// (sumWeight + newNode) % 3 == 0
	const int rest = (2 * sumWeight) % 3; /// == newNode % 3
	/// it is enough that one side stick and one of the other will be exact weightEach
	std::array<int, 2> wts{vec.front(), vec.back()};
	std::array<int, 2> last{0, static_cast<int>(vec.size() - 1)};
	std::array<int, 2> sign{+1, -1};
	for(int newNode = rest; newNode <= std::floor(sumWeight / 2); newNode += 3)
	{
		const int weightEach = (sumWeight + newNode) / 3;
		for(int i : {0, 1})
		{
			while(wts[i] < weightEach)
			{
				wts[i] += vec[last[i] + sign[i]];
				last[i] += sign[i];
			}
		}
		int numGood = -1;
		if(wts[0] == wts[1]) return (wts[0]) * 3 - sumWeight;
		else if(wts[0] == weightEach) { numGood = 0; }
		else if(wts[1] == weightEach) { numGood = 1; }
		else { continue; }

		int midLast = last[numGood] + sign[numGood];
		int wtsMid = vec[midLast];
		while(wtsMid < weightEach)
		{
			wtsMid += vec[midLast + sign[numGood]];
			midLast += sign[numGood];
		}
		if(wtsMid == weightEach) return newNode;
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
