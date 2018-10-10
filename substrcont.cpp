#include <bits/stdc++.h>

#include <header.h>
using namespace std;

// Complete the substrCount function below.
long substrCount(int n, string s)
{
	int res = s.size(); /// one letter
	for(int i = 0; i < s.size(); ++i)
	{
		char curr = s[i];
		for(int j = i + 1; j < s.size(); ++j)
		{
			int len = j - i;
			if(s[j] != curr)
			{
				res += len * (len - 1) / 2; /// left part

				int lenR{0};
				for(int k = j + 1; k < s.size() && k <= j + len + 1; ++k)
				{
					if(s[k] != curr)
					{
						lenR = k - (j + 1);
						break;
					}
					if(k == s.size() - 1)
					{
						lenR = k - j;
						break;
					}
				}
				res += lenR; /// "mid" part
				i = j - 1;
				break;
			}
			if(j == s.size() - 1)
			{
				res += len * (len + 1) / 2;
				i = s.size();
				break;
			}
		}
	}
	return res;
}

int substrcont()
{
	const std::string project = "substrcont";
	const std::string fileNum = "02";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int n;
	inStr >> n;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	string s;
	getline(inStr, s);

	long result = substrCount(n, s);

	fout << result << "\n";

	fout.close();


	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}