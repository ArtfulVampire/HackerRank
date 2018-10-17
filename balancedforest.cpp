#include <bits/stdc++.h>
#include <header.h>

using namespace std;

using adjType = std::unordered_map<int, std::unordered_set<int>>;
using degType = std::map<int, std::unordered_set<int>, greater<int>>;
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

std::vector<weightType> routeToLeaf(const adjType & adjacency,
									const vector<weightType> & weights,
									int start,
									int prev = -1)
{
	if((prev == -1 && adjacency.at(start).size() != 1))
	{
		std::cout << "cant know the direction" << std::endl;
		return {};
	}

	std::vector<weightType> res{};

	int routeLast{};	/// inclusive last
	int routeEnd{};		/// not inclusive next-over-last
	if(prev == -1)
	{
		routeLast = start;
		routeEnd = *(std::begin(adjacency.at(start)));
		res.push_back(weights[start - 1]); /// 1-based
	}
	else
	{
		routeLast = prev;
		routeEnd = start;
	}

	while(adjacency.at(routeEnd).size() >= 2)
	{
		if(adjacency.at(routeEnd).size() > 2)
		{
			std::cout << "cant know the direction2" << std::endl;
			return {};
		}
		res.push_back(weights[routeEnd - 1]); /// 1-based
		auto it = std::begin(adjacency.at(routeEnd));
		int v1 = *it; ++it; int v2 = *it;
		int newEnd = (v1 == routeLast) ? v2 : v1;
		routeLast = routeEnd;
		routeEnd = newEnd;
	}
	/// final leaf
	res.push_back(weights[routeEnd - 1]); /// 1-based
	return res;
}


int solveStick(const adjType & adjacency, const degType & degrees, const vector<weightType> & weights)
{
	const weightType sumWeight = std::accumulate(std::begin(weights), std::end(weights), 0);

	/// make initial path from a leaf
	std::vector<weightType> vec = routeToLeaf(adjacency, weights, *std::begin(degrees.at(1)), -1);

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

		/// memoize not to recalculate each time ?
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

int solveStar(const adjType & adjacency,
			  const degType & degrees,
			  const vector<weightType> & weights,
			  int heaviestChild)
{

	const int center = *std::begin(std::begin(degrees)->second); /// center vertex

	/// make vectors for light childs
	std::vector<std::vector<weightType>> wtsVec(adjacency.at(center).size() - 1);
	int branchNum = 0;
	for(auto child : adjacency.at(center))
	{
		if(child == heaviestChild) { continue; }
		wtsVec[branchNum] = routeToLeaf(adjacency, weights, child, center);
		std::reverse(std::begin(wtsVec[branchNum]), std::end(wtsVec[branchNum])); /// start from a leaf
		++branchNum;
	}

	std::vector<int> lastIndex(branchNum, 0);
	std::vector<weightType> wts(branchNum, 0);
	const weightType sumWeight = std::accumulate(std::begin(weights), std::end(weights), 0);
	const int rest = (2 * sumWeight) % 3; /// == newNode % 3

	std::vector<weightType> heavyWts = routeToLeaf(adjacency, weights, heaviestChild, center);
	std::reverse(std::begin(heavyWts), std::end(heavyWts));
	weightType heavy{0};
	int lastHeavy{0};
	for(int newNode = rest; newNode <= std::floor(sumWeight / 2); newNode += 3)
	{
		const int weightEach = (sumWeight + newNode) / 3;

		/// heavy branch
		while(heavy < weightEach)
		{
			heavy += heavyWts[lastHeavy];
			++lastHeavy;
			if(lastHeavy >= heavyWts.size()) { return -1; }
		}
		if(heavy != weightEach) { continue; }

		/// light branches
		for(int branch = 0; branch < branchNum; ++branch)
		{
			if(lastIndex[branch] >= wtsVec[branch].size()) { continue; }

			while(wts[branch] < weightEach - newNode && lastIndex[branch] < wtsVec[branch].size())
			{
				wts[branch] += wtsVec[branch][lastIndex[branch]];
				++lastIndex[branch];
			}
			if(wts[branch] == weightEach - newNode) return newNode;
		}
	}
	return -1;
}

// Complete the balancedForest function below.
int balancedForest(vector<weightType> weights, const vector<vector<int>> & edges)
{
	adjType adjacency{};
	degType degrees{}; /// degree, set of vertices
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


	int starHeaviestChild{};
	while(true) /// break condition in the end
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

//		std::cout << std::get<0>(wts[0]) << " " << std::get<0>(wts[1]) << " " << std::get<0>(wts[2]) << std::endl;
//		std::cout << std::get<1>(wts[0]) << "\n" << std::get<1>(wts[1]) << "\n" << std::get<1>(wts[2]) << std::endl;


		int numBranchLeft = wts.size(); /// nothing to add

		/// no even quite heavy branches
		if(std::get<0>(wts[0]) < std::ceil(sumWeight / 3.)) { return -1; } /// danger

		/// one very heavy branch
		if(std::get<0>(wts[0]) >= std::ceil(2 * sumWeight / 3.))
		{
			numBranchLeft = 1;
		}
		/// two quite heavy branches
		else if(std::get<0>(wts[0]) >= std::ceil(sumWeight / 3.)
		   && std::get<0>(wts[1]) >= std::ceil(sumWeight / 3.))
		{
			numBranchLeft = 2;
		}
		/// only one quite heavy branch - only one such vertex can exist
		else
		{
			starHeaviestChild = std::get<2>(wts[0]);
		}


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

		/// break condition
		auto it = std::begin(degrees);
		if(it->first <= 2) break; /// "a stick"
		if(it->first > 2 && it->second.size() == 1) /// "a star"
		{
			++it;
			if(it->first <= 2) break;
		}

	}

	/// Check:
	printAdj();
	printDeg();

	// now we have "a stick" - a single line or "a star" with only one "quite heavy" branch
	// it has two "leaves" with degree = 1

	if(std::begin(degrees)->first == 2)
	{
		std::cout << "stick" << std::endl;
		return solveStick(adjacency, degrees, weights);
	}
	std::cout << "star" << std::endl;
	return solveStar(adjacency, degrees, weights, starHeaviestChild);
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
