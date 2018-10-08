#include <bits/stdc++.h>
#include <header.h>

using namespace std;

// Complete the countTriplets function below.
long countTriplets(const vector<long> & arr, long r) {

	if(r == 1)
	{
		/// usual map
	}

	std::unordered_map<long, std::set<int>> mp{};
	long maxVal = 0;
	for(int i = 0; i < arr.size(); ++i)
	{
		mp[arr[i]].emplace(i);
		maxVal = std::max(maxVal, arr[i]);
	}

	int thr = std::ceil(maxVal / (r*r));

	long res{0};

	for(const auto & in : mp)
	{
		if(in.first >= thr ||
		   mp[in.first * r].empty() ||
		   mp[in.first * r * r].empty()) { continue; }
		const auto & sec = mp[in.first * r];
		const auto & thi = mp[in.first * r * r];

		for(auto i = std::begin(in.second); i != std::end(in.second); ++i)
		{
			auto j = sec.lower_bound(*i);
			auto k = thi.lower_bound(*j);
			/// minus 1 ??
			res += std::distance(j, std::end(sec)) *
				   std::distance(k, std::end(thi));
		}

	}

	return res;
}

int triplets()
{

	std::ofstream fout(prePath + "triplets06out.txt");
	std::ifstream inStr(prePath + "triplets06.txt");

	std::string nr_temp;
	getline(inStr, nr_temp);

	vector<std::string> nr = split(rtrim(nr_temp));

	int n = stoi(nr[0]);
	long r = stol(nr[1]);

	std::string arr_temp_temp;
	getline(inStr, arr_temp_temp);

	vector<std::string> arr_temp = split(rtrim(arr_temp_temp));

	vector<long> arr(n);

	for (int i = 0; i < n; i++) {
		long arr_item = stol(arr_temp[i]);

		arr[i] = arr_item;
	}

	long ans = countTriplets(arr, r);

	fout << ans << "\n";

	fout.close();

	std::cout << areEqualFiles(prePath + "triplets06out.txt",
							   prePath + "triplets06output.txt") << std::endl;

	return 0;
}

