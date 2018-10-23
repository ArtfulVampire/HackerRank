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

	weightType res{LONG_MAX};

	const weightType rem = (2 * sumWeight) % 3;
	const weightType minEach = (sumWeight + rem) / 3;
	auto it = std::begin(WTS);
	while (it->first < minEach) /// it means it is definitely each - newNode
	{
		std::vector<decltype(it)> its{it};
		auto it2 = it; ++it2;
		while(it2->first == it->first) { its.push_back(it2); ++it2; }

		/// find parenting 2 * each - newNode and 2 * each
		const weightType newNode = (3 * it->first - sumWeight - rem) / (-2);
		const weightType each = it->first + newNode;

		/// non-parenting each
		auto eachList = WTS.equal_range(each);
		for(auto b = eachList.first; b != eachList.second; ++b)
		{
			for(auto a : its)
			{
				if(!checkAncestor(b->second, adjacency, a->second)) res = std::min(res, newNode);
			}
		}

//		/// non-parenting 2 * each
//		auto each2 = WTS.equal_range(2 * each);
//		for(auto b = each2.first; b != each2.second; ++b)
//		{
//			for(auto a : its)
//			{
//				if(!checkAncestor(b->second, adjacency, a->second)) res = std::min(res, newNode);
//			}
//		}

		/// parenting 2 * each - newNode
		auto each2minusVal = WTS.equal_range(2 * each - newNode);
		for(auto b = each2minusVal.first; b != each2minusVal.second; ++b)
		{
			for(auto a : its)
			{
				if(checkAncestor(b->second, adjacency, a->second)) res = std::min(res, newNode);
			}
		}
		it = its.back();
		++it;
	}

	/// over minEach
	while (it->first <= sumWeight / 2) /// it means it is definitely each
	{
		std::vector<decltype(it)> its{it};
		auto it2 = it; ++it2;
		while(it2->first == it->first) { its.push_back(it2); ++it2; }


		const weightType newNode = (3 * it->first - sumWeight - rem);
		const weightType each = it->first;

		/// two different each
		if(its.size() > 1) { res = std::min(res, newNode); }

		/// each and parent 2*each
		auto each2 = WTS.equal_range(2 * each);
		for(auto b = each2.first; b != each2.second; ++b)
		{
			for(auto a : its)
			{
				if(checkAncestor(b->second, adjacency, a->second)) res = std::min(res, newNode);
			}
		}
		/// each  & 2*each-val
		auto each2minusVal = WTS.equal_range(2 * each - newNode);
		for(auto b = each2minusVal.first; b != each2minusVal.second; ++b)
		{
			for(auto a : its)
			{
				if(checkAncestor(b->second, adjacency, a->second)) res = std::min(res, newNode);
			}
		}
		it = its.back();
		++it;
	}
	return (res == LONG_MAX) ? -1 :res;
}

int balance()
{
	const std::string project = "balanced"; //balanced
	const std::string fileNum = "04_1";

	std::ofstream fout(prePath + project + "/" + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + "/" + project + fileNum + ".txt");

	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++)
	{

//		std::ofstream subb(prePath + project + "/" + project + fileNum + "_" + QString::number(q_itr).toStdString() + ".txt");
		std::ofstream subb("/dev/null");
		std::ostream & sub{subb};

		int n;
		inStr >> n;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');
		sub << 1 << "\n";
		sub << n << "\n";

		string c_temp_temp;
		getline(inStr, c_temp_temp);

		vector<string> c_temp = split(c_temp_temp);

		vector<weightType> c(n);

		for (int i = 0; i < n; i++) {
			int c_item = stoi(c_temp[i]);
			sub << c_item << " ";

			c[i] = c_item;
		}

		vector<vector<int>> edges(n - 1);
		for (int i = 0; i < n - 1; i++) {
			edges[i].resize(2);

			for (int j = 0; j < 2; j++) {
				inStr >> edges[i][j];
				sub << edges[i][j] << " ";
			}
			sub << "\n";

			inStr.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		subb.close();

		weightType result = balancedForest(c, edges);
//		std::cout << result << std::endl << std::endl;;

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + "/" + project + fileNum + "out.txt",
							   prePath + project + "/" + project + fileNum + "output.txt") << std::endl;

	return 0;
}
