#include <header.h>
#include <bits/stdc++.h>

using namespace std;


struct node
{
	node * root{this};
	std::vector<node*> children{};
	int num{0};

	node(){}
	node(node * r) : root{r} {}
	node(node * ch, int num_) : children{{ch}}, num{num_} {}

	void reroot(node * const r)
	{
		root = r;
		for(node * in : children)
		{
			in->reroot(r);
		}
	}
};

long numOfComponents(long n, const std::vector<std::vector<int>> & cities)
{
	/// num of "root" city, its node*
	std::unordered_map<int, node*> guys{};
	 for(const auto & q : cities)
	 {
//		 std::cout << q[0] << " " << q[1] << std::endl;
		 if(guys.count(q[0]) == 0 && guys.count(q[1]) == 0)
		 {
			 guys[q[1]] = new node();
			 guys[q[0]] = new node(guys[q[1]], 2);
			 guys[q[1]]->root = guys[q[0]];
			 continue;
		 }
		 else if(guys.count(q[0]) == 0)
		 {
			 guys[q[0]] = new node(guys[q[1]]->root);
			 guys[q[1]]->root->children.push_back(guys[q[0]]);
			 guys[q[1]]->root->num += 1;
			 continue;
		 }
		 else if(guys.count(q[1]) == 0)
		 {
			 guys[q[1]] = new node(guys[q[0]]->root);
			 guys[q[0]]->root->children.push_back(guys[q[1]]);
			 guys[q[0]]->root->num += 1;
			 continue;
		 }

		 if(guys[q[0]]->root == guys[q[1]]->root)
		 {
			 continue;
		 }

		 node * big = guys[q[0]]->root;
		 node * lit = guys[q[1]]->root;
		 if(big->num < lit->num)
		 {
			 std::swap(big, lit);
		 }
		 big->num += lit->num;
		 lit->reroot(big);
		 big->children.push_back(lit);
	 }

	long res = 0;
	for(const auto & in : guys)
	{
//		std::cout << in.first << " " << in.second->num << " " << in.second->root->num << std::endl;
		if(in.second->root == in.second) ++res;
	}
	std::cout << "singles = " << n - guys.size() << std::endl;
	res += n - guys.size();
	return res;
}

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(long n, long c_lib, long c_road, vector<vector<int>> cities)
{
	if(c_lib <= c_road) return c_lib * n;
	/// else
	long num = numOfComponents(n, cities);
	std::cout << num << std::endl;
	return c_lib * num + c_road * (n - num);
}

int cities()
{
	const std::string project = "cities"; //cities
	const std::string fileNum = "03";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");
//	std::cin.rdbuf(inStr.rdbuf());

	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string nmC_libC_road_temp;
		getline(inStr, nmC_libC_road_temp);

		vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

		int n = stoi(nmC_libC_road[0]);

		int m = stoi(nmC_libC_road[1]);

		int c_lib = stoi(nmC_libC_road[2]);

		int c_road = stoi(nmC_libC_road[3]);

		vector<vector<int>> cities(m);
		for (int i = 0; i < m; i++) {
			cities[i].resize(2);

			for (int j = 0; j < 2; j++) {
				inStr >> cities[i][j];
			}

			inStr.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		long result = roadsAndLibraries(n, c_lib, c_road, cities);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
