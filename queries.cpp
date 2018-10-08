#include <bits/stdc++.h>
#include <QString>
#include <QFile>
#include <cstdio>
#include <header.h>

using namespace std;

vector<int> freqQuery(const vector<vector<int>> & queries) {
	std::map<int, std::set<int>> mp{}; /// freq, nums
	std::vector<int> res{};
	for(const auto & query : queries)
	{
		switch(query[0])
		{
		case 1: /// insert query[1]
		{
			bool was{false};
			for(auto & in : mp)
			{
				if(in.second.count(query[1]) != 0)
				{
					was = true;
					in.second.erase(query[1]);
					mp[in.first + 1].emplace(query[1]);
					break;
				}
			}
			if(!was)
			{
				mp[1].emplace(query[1]);
			}
			break;
		}
		case 2: /// delete
		{
			for(auto & in : mp)
			{
				if(in.second.count(query[1]) != 0)
				{
					in.second.erase(query[1]);
					if(in.first - 1 > 0)
					{
						mp[in.first - 1].emplace(query[1]);
					}
					break;
				}
			}
			break;
		}
		case 3: /// check
		{
			if(mp[query[1]].size() != 0)
			{
				res.push_back(1);
			}
			else
			{
				res.push_back(0);
			}
			break;
		}
		default: { break;}
		}
	}
	return res;
}

int queries()
{
	std::ofstream fout(prePath + "queries08out.txt");

	std::ifstream inStr(prePath + "queries08.txt");

	std::string q_temp;
	getline(inStr, q_temp);

	int q = stoi(ltrim(rtrim(q_temp)));

	vector<vector<int>> queries(q);

	for (int i = 0; i < q; i++) {
		queries[i].resize(2);

		std::string queries_row_temp_temp;
		getline(inStr, queries_row_temp_temp);

		vector<std::string> queries_row_temp = split(rtrim(queries_row_temp_temp));

		for (int j = 0; j < 2; j++) {
			int queries_row_item = stoi(queries_row_temp[j]);

			queries[i][j] = queries_row_item;
		}
	}

	vector<int> ans = freqQuery(queries);

	for (int i = 0; i < ans.size(); i++) {
		fout << ans[i];

		if (i != ans.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

	std::cout << areEqualFiles(prePath + "queries08out.txt",
							   prePath + "queries08output.txt") << std::endl;

	return 0;
}

