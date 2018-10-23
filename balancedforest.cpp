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
	if(weights.size() == 1) return -1;
	if(weights.size() == 2 && weights[0] != weights[1]) return -1;

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
	auto high = WTS.lower_bound(minEach);
	auto low = WTS.upper_bound(minEach - rem);

	if(low != std::begin(WTS))
	{
		--low;
	}

	while(low->first == high->first)
	{
		++high;
	}

	std::vector<decltype(low)> itsLow{};
	std::vector<decltype(low)> itsHigh{};
	bool badLow{false};
	bool badHigh{false};
	while (true)
	{
		if(badLow && badHigh) return -1;

		/// low = each - newVal
		weightType newNodeLow{};
		weightType eachLow{-1};
		if(!badLow)
		{
			itsLow = {low};

			auto itLow = low;
			if(itLow != std::begin(WTS))
			{
				--itLow;
			}
			while(itLow->first == low->first)
			{
				itsLow.push_back(itLow);
				if(itLow != std::begin(WTS))
				{
					--itLow;
				}
				else
				{
					break;
				}
			}
			newNodeLow = (3 * low->first - sumWeight - rem) / (-2);
			eachLow = low->first + newNodeLow;
		}

		/// high = each
		weightType newNodeHigh{};
		weightType eachHigh{-1};
		if(!badHigh)
		{
			itsHigh = {high};
			auto itHigh = high; ++itHigh;
			while(itHigh->first == high->first) { itsHigh.push_back(itHigh); ++itHigh; }
			newNodeHigh = (3 * high->first - sumWeight - rem);
			eachHigh = high->first;
		}

		if(eachHigh == eachLow)
		{
			for(auto l : itsLow)
			{
				for(auto h : itsHigh)
				{
					if(!checkAncestor(h->second, adjacency, l->second))
					{
//						std::cout
//								<< "each-val & each:" << "\n"
//								<< "sumWeight = " << sumWeight << "\n"
//								<< "rem = " << rem << "\n"
//								<< "val = " << newNodeHigh << "\n"
//								<< "each = " << eachHigh << "\n"
//								<< "lowItem = "  << l->first << "\n"
//								<< "highItem = " << h->first << "\n"
//								   ;
						return newNodeHigh;
					}
				}
			}
		}

		if( !badHigh && ( (!badLow && (eachHigh < eachLow)) || badLow ) )
		{
			/// each & 2*each
			auto each2 = WTS.equal_range(2 * eachHigh);
			for(auto b = each2.first; b != each2.second; ++b)
			{
				for(auto a : itsHigh)
				{
					if(checkAncestor(b->second, adjacency, a->second))
					{
//						std::cout << "each & 2each: " << "\n"
//								  << "sumWeight = " << sumWeight << "\n"
//								  << "rem = " << rem << "\n"
//								  << "val = " << newNodeHigh << "\n"
//								  << "each = " << eachHigh << "\n"
//								  << "lowItem = "  << a->first << "\n"
//								  << "highItem = " << b->first << "\n"
//									 ;
						return newNodeHigh;
					}
				}
			}

			/// each & 2*each-val
			auto each2minusVal = WTS.equal_range(2 * eachHigh - newNodeHigh);
			for(auto b = each2minusVal.first; b != each2minusVal.second; ++b)
			{
				for(auto a : itsHigh)
				{
					if(checkAncestor(b->second, adjacency, a->second))
					{
//						std::cout << "each & 2each-val: " << "\n"
//								  << "sumWeight = " << sumWeight << "\n"
//								  << "rem = " << rem << "\n"
//								  << "val = " << newNodeHigh << "\n"
//								  << "each = " << eachHigh << "\n"
//								  << "lowItem = "  << a->first << "\n"
//								  << "highItem = " << b->first << "\n"
//									 ;
						return newNodeHigh;
					}
				}
			}
			high = itsHigh.back();
			if(high->first > sumWeight / 2) badHigh = true;
			++high;
		}

		if( !badLow && ( (!badHigh && (eachLow < eachHigh)) || badHigh ) )
		{

//			/// each-val & non-parenting each
//			auto eachList = WTS.equal_range(eachLow);
//			for(auto b = eachList.first; b != eachList.second; ++b)
//			{
//				for(auto a : itsLow)
//				{
//					if(!checkAncestor(b->second, adjacency, a->second))
//					{
//						std::cout << "each-val & each: " << "\n"
//								  << "sumWeight = " << sumWeight << "\n"
//								  << "rem = " << rem << "\n"
//								  << "val = " << newNodeLow << "\n"
//								  << "each = " << eachLow << "\n"
//								  << "lowItem = "  << a->first << "\n"
//								  << "highItem = " << b->first << "\n"
//									 ;
//						return newNodeLow;
//					}
//				}
//			}

			/// each-val &  2*each-val
			auto each2minusVal = WTS.equal_range(2 * eachLow - newNodeLow);
			for(auto b = each2minusVal.first; b != each2minusVal.second; ++b)
			{
				for(auto a : itsLow)
				{
					if(checkAncestor(b->second, adjacency, a->second))
					{
//						std::cout << "each-val & 2each-val: " << "\n"
//								  << "sumWeight = " << sumWeight << "\n"
//								  << "rem = " << rem << "\n"
//								  << "val = " << newNodeLow << "\n"
//								  << "each = " << eachLow << "\n"
//								  << "lowItem = "  << a->first << "\n"
//								  << "highItem = " << b->first << "\n"
//									 ;
						return newNodeLow;
					}
				}
			}
			low = itsLow.back();
			if(low == std::begin(WTS))
			{
				badLow = true;
			}
			/// else? - dont matter
			--low;
		}
	}
	return -1;
}

int balance()
{
	const std::string project = "balanced"; //balanced
	const std::string fileNum = "05_1";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++)
	{

		std::ofstream sub(prePath + project + fileNum + "_" + QString::number(q_itr).toStdString() + ".txt");

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
		sub.close();

		weightType result = balancedForest(c, edges);
//		std::cout << result << std::endl << std::endl;;

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
