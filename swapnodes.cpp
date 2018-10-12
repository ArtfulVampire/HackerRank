#include <bits/stdc++.h>
#include <header.h>

using namespace std;

struct node
{
	int index{-1};
	int depth{0};
	node * left{nullptr};
	node * right{nullptr};

	node(){}

	void swap() { std::swap(left, right); }

	bool isLeaf() const
	{
		return  index == -1 && depth == 0 && !left && !right;
	}
	bool isNotLeaf() const
	{
		return !(this->isLeaf());
	}
};

node  * const leaf = new node();


std::list<int> inOrder(node * in)
{
	if(in == leaf) return {};

	std::list<int> res{};
	res.splice(std::end(res), inOrder(in->left));
	res.push_back(in->index);
	res.splice(std::end(res), inOrder(in->right));
	return res;
}

void swapTree(node * root, int k)
{
	std::list<node*> prevLevel{root};
	std::list<node*> currLevel{};

	int prevLev = 1;
	do
	{
		if(prevLev % k == 0)
		{
//			std::cout << "swap units: ";
			for(auto & in : prevLevel)
			{
//				std::cout << in->index << "\t";
				in->swap();
			}
//			std::cout << std::endl;
		}
		currLevel.clear();
		for(const auto & in : prevLevel)
		{
			if(in->left != leaf)
			{ currLevel.push_back(in->left); }

			if(in->right != leaf)
			{ currLevel.push_back(in->right); }
		}

//		std::cout << "currLevel: ";
//		for(auto & in : currLevel)
//		{
//			std::cout << in->index << "\t";
//		}
//		std::cout << std::endl;

		prevLevel = currLevel;
		++prevLev;
	} while (!currLevel.empty());
//	std::cout << "swap finished" << std::endl;
}

vector<vector<int>> swapNodes(const std::vector<std::vector<int>> & indexes, const std::vector<int> & queries)
{
	std::vector<node> nodes(indexes.size() + 1, node());
	nodes[1].depth = 1;
	for(auto i = 1; i <= indexes.size(); ++i)
	{
//		std::cout << i << std::endl;
//		std::cout << indexes[i-1][0] << "\t" << indexes[i-1][1] << std::endl;
		nodes[i].index = i;
		if(indexes[i-1][0] != -1)
		{
			nodes[i].left = &(nodes[indexes[i-1][0]]);
			nodes[i].left->depth = nodes[i].depth + 1;
		}
		else
		{
			nodes[i].left = leaf;
		}

		if(indexes[i-1][1] != -1)
		{
			nodes[i].right = &(nodes[indexes[i-1][1]]);
			nodes[i].right->depth = nodes[i].depth + 1;
		}
		else
		{
			nodes[i].right = leaf;
		}
	}

	std::vector<std::vector<int>> res{};
	for(auto q : queries)
	{
		swapTree(&nodes[1], q);
		auto a = inOrder(&nodes[1]);
//		std::cout << a << std::endl;
		res.push_back( std::vector<int>(std::begin(a), std::end(a)) );
	}
	return res;
}

int swapnodes()
{
	const std::string project = "";
	const std::string fileNum = "00";

	std::ifstream inStr(prePath + project + fileNum + ".txt");
	std::ofstream fout(prePath + project + fileNum + "out.txt");

	int n;
	inStr >> n;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<vector<int>> indexes(n);
	for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++) {
		indexes[indexes_row_itr].resize(2);

		for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++) {
			inStr >> indexes[indexes_row_itr][indexes_column_itr];
		}
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	int queries_count;
	inStr >> queries_count;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> queries(queries_count);

	for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
		int queries_item;
		inStr >> queries_item;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');

		queries[queries_itr] = queries_item;
	}

	vector<vector<int>> result = swapNodes(indexes, queries);

	for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++) {
		for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++) {
			fout << result[result_row_itr][result_column_itr];

			if (result_column_itr != result[result_row_itr].size() - 1) {
				fout << " ";
			}
		}

		if (result_row_itr != result.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

	fout.close();

	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
