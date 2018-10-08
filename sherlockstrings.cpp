#include <bits/stdc++.h>
#include <header.h>

using namespace std;

// Complete the isValid function below.
string isValid(string s)
{
	std::unordered_map<char, int> mp{};
	 std::map<int, int> fr{}; /// freq, num of such chars
	 for(auto ch : s) { ++mp[ch]; }
	 for(const auto & in : mp)
	 {
		 ++fr[in.second];
	 }
	 if(fr.size() > 2) return "NO";
	 if(fr.size() == 2)
	 {

		 auto it1 = std::begin(fr);
		 auto it2 = std::begin(fr); ++it2;
		 std::cout << it1->first << "\t" << it1->second << std::endl;
		 std::cout << it2->first << "\t" << it2->second << std::endl;
		 if(it1->first == 1 && it1->second == 1) { return "YES"; }
		 if(std::abs(it1->first - it2->first) != 1)
		 {
			 return "NO";
		 }
		 if(it1->second != 1 && it2->second != 1) { return "NO"; }
	 }
	 return "YES";
}

int sherstr()
{
	const std::string fileNum = "13";
	std::ofstream fout(prePath + "sherstr" + fileNum + "out.txt");
	std::ifstream inStr(prePath + "sherstr" + fileNum + ".txt");

	string s;
	getline(inStr, s);

	string result = isValid(s);

	fout << result << "\n";

	fout.close();

	std::cout << areEqualFiles(prePath + "sherstr" + fileNum + "out.txt",
							   prePath + "sherstr" + fileNum + "output.txt") << std::endl;

	return 0;
}