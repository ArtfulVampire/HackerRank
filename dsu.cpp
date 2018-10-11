#include <bits/stdc++.h>
#include <header.h>

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

// Complete the maxCircle function below.
vector<int> maxCircle(const vector<vector<int>> & queries)
{
	std::unordered_map<int, node*> guys{};

	 std::vector<int> res{};
	 int mx = 1;

	 for(const auto & q : queries)
	 {
		 if(guys.count(q[0]) == 0 && guys.count(q[1]) == 0)
		 {
			 guys[q[1]] = new node();
			 guys[q[0]] = new node(guys[q[1]], 2);
			 guys[q[1]]->root = guys[q[0]];

			 mx = std::max(mx, 2);
			 res.push_back(mx);
			 continue;
		 }
		 else if(guys.count(q[0]) == 0)
		 {
			 guys[q[0]] = new node(guys[q[1]]->root);
			 guys[q[1]]->root->children.push_back(guys[q[0]]);
			 guys[q[1]]->root->num += 1;

			 mx = std::max(mx, guys[q[1]]->root->num);
			 res.push_back(mx);
			 continue;
		 }
		 else if(guys.count(q[1]) == 0)
		 {
			 guys[q[1]] = new node(guys[q[0]]->root);
			 guys[q[0]]->root->children.push_back(guys[q[1]]);
			 guys[q[0]]->root->num += 1;

			 mx = std::max(mx, guys[q[0]]->root->num);
			 res.push_back(mx);
			 continue;
		 }

		 if(guys[q[0]]->root == guys[q[1]]->root)
		 {
			 res.push_back(mx);
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
		 mx = std::max(mx, big->num);
		 res.push_back(mx);
	 }
	 return res;
}

int dsu()
{
	const std::string project = "dsu";
	const std::string fileNum = "10";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<vector<int>> queries(q);
	for (int i = 0; i < q; i++) {
		queries[i].resize(2);

		for (int j = 0; j < 2; j++) {
			inStr >> queries[i][j];
		}

		inStr.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	auto t0 = std::chrono::high_resolution_clock::now();

	vector<int> ans = maxCircle(queries);

	auto t1 = std::chrono::high_resolution_clock::now();

	std::cout
			<< ": time elapsed = "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()
			<< " msec" << std::endl;

	for (int i = 0; i < ans.size(); i++) {
		fout << ans[i];

		if (i != ans.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

	fout.close();

	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
