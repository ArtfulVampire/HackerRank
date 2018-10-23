#include<header.h>
#include <bits/stdc++.h>

using namespace std;

struct Node
{
	std::array<Node *, 2> ch{nullptr, nullptr};
};

// Complete the maxXor function below.
vector<int> maxXor(vector<int> arr, vector<int> queries)
{
	Node * tree = new Node();
	for(auto in : arr)
	{
		std::bitset<32> b(in);
		Node * curr = tree;
		for(int i = 31; i >= 0; --i)
		{
			if(!curr->ch[b[i]])
			{
				curr->ch[b[i]] = new Node();
			}
			curr = curr->ch[b[i]];
		}
	}
	std::vector<int> res{};
	for(auto in : queries)
	{
		std::bitset<32> b(in);
		std::bitset<32> tmp{};
		Node * curr = tree;
		for(int i = 31; i >= 0; --i)
		{
			if(curr->ch[!b[i]])
			{
				tmp[i] = 1;
				curr = curr->ch[!b[i]];
			}
			else
			{
				tmp[i] = 0;
				curr = curr->ch[b[i]];
			}
		}
		res.push_back(static_cast<int>(tmp.to_ulong()));
	}
	return res;
}

int maxxor()
{
	const std::string project = ""; //
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int n;
	inStr >> n;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	string arr_temp_temp;
	getline(inStr, arr_temp_temp);

	vector<string> arr_temp = split_string(arr_temp_temp);

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		int arr_item = stoi(arr_temp[i]);

		arr[i] = arr_item;
	}

	int m;
	inStr >> m;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> queries(m);

	for (int i = 0; i < m; i++) {
		int queries_item;
		inStr >> queries_item;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');

		queries[i] = queries_item;
	}

	vector<int> result = maxXor(arr, queries);

	for (int i = 0; i < result.size(); i++) {
		fout << result[i];

		if (i != result.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
