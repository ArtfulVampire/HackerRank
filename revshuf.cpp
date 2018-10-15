#include <bits/stdc++.h>
#include <header.h>

using namespace std;

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s)
{
	std::reverse(std::begin(s), std::end(s));
	std::cout << s << std::endl;
	std::map<char, int> mp{};
	for(auto in : s)
	{
		++mp[in];
	}
	for(auto & in : mp)
	{
		in.second /= 2;
	}
	/// mp is set toFind
	///
	const auto canPass{mp};

	std::string res{""};

	auto minChar = 'z' + 1;
	auto minPos = -1;
	std::map<char, int> prevMin{}; /// what can be sent to shuffle backuped
	int lastAdded = -1;

	std::map<char, int> prevSet{}; /// what can be sent to shuffle

	int i = 0;

	auto addChar = [&](const int in) -> bool
	{
		res += s[in];
		mp[s[in]] -= 1;
		if(mp[s[in]] == 0)
		{
			 mp.erase(s[in]);
			 if(mp.empty()) { return false; }
		}
		for(int j = lastAdded + 1; j < in; ++j)
		{
			++prevMin[s[j]];
		}
		i = in + 1;
		if(i == s.size()) { return false; }

		lastAdded = in;
		prevSet = prevMin;
		minChar = 'z' + 1;
		minPos = -1;

		return true;
	};

	while(!mp.empty())
	{
		std::cout << std::endl;
		std::cout << "test = " << s[i] << " " << i << std::endl;
		std::cout << "curr re = " << res << std::endl;
		std::cout << "toFind:\t" << mp << std::endl;
		std::cout << "passed:\t" << prevSet << std::endl;


		if(s[i] == std::begin(mp)->first) /// best fit char
		{
			std::cout << "best fit add = " << s[i] << " " << i << std::endl;
			if(addChar(i)) { continue; }
			else { break; }
		}

		if(mp.count(s[i]) != 0 && prevSet[s[i]] >= canPass.at(s[i])) /// problem
		{
			if(s[i] < minChar)
			{
				minChar = s[i];
				minPos = i;
			}
			std::cout << "good fit add = " << s[minPos] << " " << minPos << std::endl;
			if(addChar(minPos)) { continue; }
			else { break; }
		}
		if(s[i] < minChar && mp.count(s[i]) != 0) // possible good fit
		{
			minChar = s[i];
			minPos = i;
			std::cout << "good fit set = " << s[minPos] << " " << minPos << std::endl;
		}
		++prevSet[s[i]];
		++i;
		if(i >= s.size()) break;
	}
	return res;
}

int revshuf()
{	const std::string project = "";
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	string s;
	getline(inStr, s);

	string result = reverseShuffleMerge(s);

	fout << result << "\n";

	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
