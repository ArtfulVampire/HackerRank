#include <bits/stdc++.h>
#include <QString>
#include <QFile>
#include <cstdio>
#include <header.h>

using namespace std;

vector<int> freqQuery(const std::vector<std::vector<int>> & queries)
{
#if 0
	std::unordered_map<int, int> mp{}; /// num, freq
	std::vector<int> res{};
	for(const auto & query : queries)
	{
		switch(query[0])
		{
		case 1: /// insert query[1]
		{
			mp[query[1]] += 1;
			break;
		}
		case 2: /// delete
		{
			if(mp.count(query[1]) != 0)
			{
				mp[query[1]] = std::max(mp[query[1]] - 1, 0);
			}
			break;
		}
		case 3: /// check
		{
			bool was{false};
			for(const auto & in : mp)
			{
				if(in.second == query[1])
				{
					was = true;
					res.push_back(1);
					break;
				}
			}
			if(!was)
			{
				res.push_back(0);
			}
			break;
		}
		default: { break;}
		}
	}
	return res;
#else
	std::unordered_map<int, std::unordered_set<int>> mp{}; /// freq, nums
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
#endif

}

int queries()
{
	const std::string fileNum = "08";

	std::ofstream fout(prePath + "queries" + fileNum + "out.txt");
	std::ifstream inStr(prePath + "queries" + fileNum + ".txt");

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

	std::cout << areEqualFiles(prePath + "queries" + fileNum + "out.txt",
							   prePath + "queries" + fileNum + "output.txt") << std::endl;

	return 0;
}

