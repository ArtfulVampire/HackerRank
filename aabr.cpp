#include <bits/stdc++.h>
#include <header.h>

using namespace std;


// Complete the abbreviation function below.
string abbreviation(string a, string b)
{
	auto toUpper = [](char in) -> char
	{
		if(in >= 49 && in <= 90) return in;
		return char(in-32);
	};

	auto isUpper = [](char in) -> bool
	{
		return (in >= 49 && in <= 90);
	};

	int sta = -1;
	for(char in : b)
	{
		++sta;
		if(sta == a.size())
		{
			return "NO";
		}
		while(toUpper(a[sta]) != in)
		{
			if(isUpper(a[sta]))
			{
				return "NO";
			}
			std::cout << toUpper(a[sta]) << " ";
			++sta;
			if(sta == a.size())
			{
				return "NO";
			}
		}
	}
	for(int i = sta + 1; i < a.size(); ++i)
	{
		if(isUpper(a[i])) return "NO";
	}
	return "YES";
}

int abbr()
{
	const std::string project = "";
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string a;
		getline(inStr, a);

		string b;
		getline(inStr, b);

		string result = abbreviation(a, b);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
