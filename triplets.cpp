#include <bits/stdc++.h>
#include <header.h>

using namespace std;

// Complete the countTriplets function below.
long countTriplets(const vector<long> & arr, long r)
{
	long res{0};
	if(r == 1)
	{
		std::unordered_map<long, long> mp{};
		for(const auto & in : arr)
		{
			mp[in] += 1;
		}
		for(const auto & in : mp)
		{
			std::cout << in.first << "\t" << in.second << std::endl;
			res += in.second * (in.second - 1) * (in.second - 2) / 6;
		}
		return res;
	}

	/// O(n^3) toooooo long
#if 0
	for(int i = 0; i < arr.size(); ++i)
	{
		for(int j = i + 1; j < arr.size(); ++j)
		{
			if(arr[j] != arr[i] * r) { continue; }
			for(int k = j + 1; k < arr.size(); ++k)
			{
				if(arr[k] != arr[j] * r) { continue; }
				res += 1;
			}
		}
	}
	return res;
#endif

	std::unordered_map<long, std::set<int>> mp{};
	long maxVal = 0;
	for(int i = 0; i < arr.size(); ++i)
	{
		mp[arr[i]].emplace(i);
		maxVal = std::max(maxVal, arr[i]);
	}
	int thr = std::ceil(maxVal / (r*r));

	for(const auto & in : mp)
	{

		if(in.first > thr ||
		   mp.count(in.first * r) == 0 ||
		   mp.count(in.first * r * r) == 0)
		{ continue; }

		const auto & fir = in.second;
		const auto & sec = mp.at(in.first * r);
		const auto & thi = mp.at(in.first * r * r);

#if 01

		auto it2 = std::begin(sec);
		auto it1 = fir.upper_bound(*it2); int num1 = std::distance(std::begin(fir), it1);
		auto it3 = thi.lower_bound(*it2); int num2 = std::distance(it3, std::end(thi));
		++it2;
		res += num1 * num2;

		for(; it2 != std::end(sec); ++it2)
		{
			for(; it1 != std::end(fir) && *it1 < *it2; ++it1, ++num1) {}
			for(; it3 != std::end(thi) && *it3 < *it2; ++it3, --num2) {}
			res += num1 * num2;
		}
#else
		for(const auto & sc : sec)
		{
			auto f = fir.upper_bound(sc);
			auto t = thi.lower_bound(sc);
			res += std::distance(std::begin(fir), f) * std::distance(t, std::end(thi));
		}
#endif

	}
	return res;
}

int triplets()
{
	const std::string fileNum = "06";

	std::ofstream fout(prePath + "triplets" + fileNum + "out.txt");
	std::ifstream inStr(prePath + "triplets" + fileNum + ".txt");

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
//	long ans = countTriplets(std::vector<long>{1, 1, 3, 3, 9, 27, 4, 1, 1, 27, 9, 12, 3, 3, 1, 27, 1, 9, 3, 11}, 3);

	fout << ans << "\n";

	fout.close();

	std::cout << areEqualFiles(prePath + "triplets" + fileNum + "out.txt",
							   prePath + "triplets" + fileNum + "output.txt") << std::endl;

	return 0;
}

