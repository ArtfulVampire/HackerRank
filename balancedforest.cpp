#include <bits/stdc++.h>
#include <header.h>

using namespace std;

using adjType = std::unordered_map<int, std::unordered_set<int>>;
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


using weightContainer = std::vector<weight>;
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
		res.insert(std::begin(res), std::begin(subW), std::end(subW)); /// vector
//		res.splice(std::end(res), subW); /// list
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

bool count(const weightContainer & wts, weightType in)
{
	auto low = std::lower_bound(std::begin(wts), std::end(wts), in);
	auto upp = std::upper_bound(std::begin(wts), std::end(wts), in);
	return std::distance(low, upp);
}

weightContainer get(const weightContainer & wts, weightType in)
{
	auto low = std::lower_bound(std::begin(wts), std::end(wts), in);
	auto upp = std::upper_bound(std::begin(wts), std::end(wts), in);
	return weightContainer(low, upp);
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
	auto wtss = weightsOf(next, leaf, adjacency, weights);
	wtss.push_back(weight(leaf, -1, sumWeight));
	std::sort(std::begin(wtss), std::end(wtss));
	if(sumWeight % 2 == 0 && count(wtss, sumWeight / 2) > 0) return sumWeight / 2;


//	std::cout << "adjacency:" << std::endl;
//	for(const auto & in : adjacency)
//	{
//		std::cout << in.first << " -> ";
//		for(auto in2 : in.second)
//		{
//			std::cout << in2 << " ";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;

//	std::cout << "leaf = " << leaf << std::endl;
//	std::cout << "next = " << next << std::endl;

//	std::cout << "weights:" << std::endl;
//	for(const auto & in : wtss)
//	{
//		std::cout << in.value << " ";
//	}
//	std::cout << std::endl;


	const int rem = (2 * sumWeight) % 3;
//	std::cout << "sumWeight = " << sumWeight << std::endl;
//	std::cout << "rem = " << rem << std::endl;
	for(int newVal = rem; newVal <= sumWeight / 2; newVal += 3)
	{
		const int each = (sumWeight + newVal) / 3;
//		std::cout << "newVal = " << newVal << "\t" << "each = " << each << std::endl;

		if(count(wtss, each) == 2) return newVal; /// two different each

		/// only one "each"
		/// only one "2each - newVal"
		{
			auto high = get(wtss, each + each - newVal);
			auto low = get(wtss, each);
			for(const auto & in1 : high)
			{
				for(const auto & in2 : low)
				{
					if(checkAncestor(in1.vertex,
									 in1.parent,
									 adjacency,
									 in2.vertex)) return newVal;
				}
			}
		}

		{
			auto high = get(wtss, each + each - newVal);
			auto low = get(wtss, each - newVal);
			for(const auto & in1 : high)
			{
				for(const auto & in2 : low)
				{
					if(checkAncestor(in1.vertex,
									 in1.parent,
									 adjacency,
									 in2.vertex)) return newVal;
				}
			}
		}
		{
			auto high = get(wtss, each + each);
			auto low = get(wtss, each);
			for(const auto & in1 : high)
			{
				for(const auto & in2 : low)
				{
					if(checkAncestor(in1.vertex,
									 in1.parent,
									 adjacency,
									 in2.vertex)) return newVal;
				}
			}
		}

		{
			auto high = get(wtss, each - newVal);
			auto low = get(wtss, each);
			for(const auto & in1 : high)
			{
				for(const auto & in2 : low)
				{
					if(!checkAncestor(in1.vertex,
									 in1.parent,
									 adjacency,
									 in2.vertex)) return newVal;
				}
			}
		}

	}
	return -1;
}

int balance()
{
	const std::string project = "balanced";
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

		int result = balancedForest(c, edges);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
