#include <bits/stdc++.h>

#include <header.h>
using namespace std;

int lenOfAfter(const std::string & in, int from, char w)
{
	int res = 0;
	while(true)
	{
		if(from < in.size() - 1 && in[from + 1] == w){ ++res; ++from; }
		else break;
	}
	return res;
}

// Complete the substrCount function below.
long substrCount(int n, const std::string & s)
{
	std::valarray<char> chs(' ', 3);
	std::valarray<int> lns(3);
	int siz = 0;
	long res = 0;

	auto func = [](int l) -> int { return l * (l - 1) / 2; };
	auto print = [&]()
	{
		std::cout << chs[2] << " " << chs[1] << " " << chs[0] << std::endl;
		std::cout << lns[2] << " " << lns[1] << " " << lns[0] << std::endl;
		std::cout << "res = " << res << std::endl;
		std::cout << "siz = " << siz << std::endl << std::endl;
	};

	if(siz == n) { return func(siz); }

	chs[0] = s[siz];
	lns[0] = lenOfAfter(s, siz, chs[0]) + 1;
	siz += lns[0];
	if(siz == n) { return func(siz + 1); } /// only one symbol


	chs = chs.shift(-1);
	lns = lns.shift(-1);
	chs[0] = s[siz];
	lns[0] = lenOfAfter(s, siz, chs[0]) + 1;
	siz += lns[0];
	if(siz == n) { return func(lns[0] + 1) + func(lns[1] + 1); }

	/// siz < n now
	do
	{
		chs = chs.shift(-1);
		lns = lns.shift(-1);
		chs[0] = s[siz];
		lns[0] = lenOfAfter(s, siz, chs[0]) + 1;

		res += func(lns[2]); /// leftest
		if(lns[1] == 1 && chs[0] == chs[2]) { res += std::min(lns[0], lns[2]); } /// "mid"
		siz += lns[0];

//		print();
	} while(siz < n);

	res += func(lns[0]) + func(lns[1]); /// last "mid" and "right"
	res += s.size(); /// single letters
//	std::cout << res << std::endl;;
	return res;
}

int substrcont()
{
//	const std::string project = "";
	const std::string project = "substrcont";
	const std::string fileNum = "03";

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
