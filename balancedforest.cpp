#include <bits/stdc++.h>
#include <header.h>

using namespace std;

using adjType = std::unordered_map<int, std::list<int>>; /// std::unordered_set instead of std::list?
using weightType = long;

struct weight
{
	int vertex;
	int parent;
	weightType value;
	weightType getValue() const { return value; }
	weight(int ver, int par, weightType val) : vertex{ver}, parent{par}, value{val} {}
	weight()=default;
	weight(const weight & other)=default;
	weight(weight &&other)=default;
	weight & operator=(const weight&)=default;
	weight & operator=(weight&&)=default;

};

bool operator< (const weight & in1, const weight & in2)
{
	return in1.getValue() < in2.getValue();
}
bool operator< (const weight & in1, const weightType & in2)
{
	return in1.getValue() < in2;
}
bool operator< (const weightType & in1, const weight & in2)
{
	return in1 < in2.getValue();
}

bool operator== (const weight & in1, const weight & in2)
{
	return in1.value == in2.value;
}

using weightContainer = std::list<weight>;
weightContainer weightsOf(int vertex, int parent, const adjType & adj, const vector<weightType> & weights)
{
	if(adj.at(vertex).size() == 1) /// next is another leaf
	{
		return { weight(vertex, parent, weights[vertex - 1]) }; /// 1-based
	}

	weightContainer res{};
	weightType itsW{0};
	for(auto child : adj.at(vertex))
	{
		if(child == parent) continue;
		auto subW = weightsOf(child, vertex, adj, weights);
		itsW += subW.back().value;
//		res.insert(std::begin(res), std::begin(subW), std::end(subW)); /// vector
		res.splice(std::end(res), subW); /// list
//		res.insert(std::begin(subW), std::end(sub)W); /// set
	}
	itsW += weights[vertex - 1]; /// 1-based
	res.push_back(weight(vertex, parent, itsW));
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

bool checkAncestor(weight par, const adjType & adj, weight child)
{
	return checkAncestor(par.vertex, par.parent, adj, child.vertex);
}

weightType balancedForest(vector<weightType> weights, const vector<vector<int>> & edges)
{
	adjType adjacency{};
	for(auto edge : edges)
	{
		adjacency[edge[0]].push_back(edge[1]);
		adjacency[edge[1]].push_back(edge[0]);
	}

	const weightType sumWeight = std::accumulate(std::begin(weights), std::end(weights), 0l);

	int leaf{0}; /// some leaf number
	for(const auto & in : adjacency)
	{
		if(in.second.size() == 1)
		{
			leaf = in.first;
			break;
		}
	}
	int next = *std::begin(adjacency[leaf]);				/// next node number
	auto wtss = weightsOf(next, leaf, adjacency, weights);
	wtss.push_back(weight(leaf, -1, sumWeight));

//	std::cout << "leaf = " << leaf << std::endl;
//	std::cout << "weights" << std::endl;
//	for(auto in : wtss)
//	{
//		std::cout << in.value << " ";
//	}
//	std::cout << std::endl;


	std::multimap<weightType, weight> WTS{};
	for(const auto & in : wtss)
	{
		WTS.emplace(in.value, in);
	}

	const weightType rem = (2 * sumWeight) % 3;
	const weightType minEach = (sumWeight + rem) / 3;
	auto highIter = WTS.lower_bound(minEach);
	auto it = highIter; ++it;
	auto lowIter = WTS.lower_bound(minEach - rem);
	while (true)
	{
		const weightType each = highIter->first;
		const weightType addFromHigh = 3 * each - sumWeight;

		weightType eachMinVal{0};
		weightType addFromLow{0};
		++lowIter;
		do
		{
			--lowIter;
			eachMinVal = lowIter->first;
			weightType new2 = sumWeight - 3 * eachMinVal;
			if(new2 % 2 == 0) { addFromLow = new2 / 2; }
		} while(addFromLow == 0 && lowIter != std::begin(WTS));

		if(addFromHigh == addFromLow && addFromHigh != 0) return addFromHigh;
		else if(addFromHigh < addFromLow)
		{
			/// test second each
			if(it->first == each) return 3 * each - sumWeight;

			/// test 2 * each
			auto a = WTS.lower_bound(2 * each);
			if(a->first == 2 * each && checkAncestor(a->second, adjacency, highIter->second))
			{
				return  3 * each - sumWeight;
			}

			/// test 2 * each - newNode
			auto b = WTS.lower_bound(sumWeight - each);
			if(b->first == sumWeight - each && checkAncestor(b->second, adjacency, highIter->second))
			{
				return  3 * each - sumWeight;
			}

			/// test nonchild each - newNode
			auto c = WTS.lower_bound(sumWeight - 2 * each);
			if(b->first == sumWeight - 2 * each && !checkAncestor(highIter->second, adjacency, c->second))
			{
				return  3 * each - sumWeight;
			}
			if(highIter->first > sumWeight / 2) break;
			++highIter;
			++it;
		}
		else /// each - newVal as a candidate
		{
			/// test 2 * each - newVal
			auto b = WTS.lower_bound(sumWeight - each);
			if(b->first == sumWeight - each && checkAncestor(b->second, adjacency, lowIter->second))
			{
				return  3 * each - sumWeight;
			}
			/// test non parent each
			auto c = WTS.lower_bound(each);
			if(b->first == each && !checkAncestor(c->second, adjacency, lowIter->second))
			{
				return  3 * each - sumWeight;
			}
			if(lowIter == std::begin(WTS)) break;
			--lowIter;
		}
	}
	return -1;
}

int balance()
{
	const std::string project = "balanced"; //balanced
	const std::string fileNum = "02";

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

		weightType result = balancedForest(c, edges);
		std::cout << result << std::endl;

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
