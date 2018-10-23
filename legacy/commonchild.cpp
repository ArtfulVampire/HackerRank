#include <bits/stdc++.h>

#include <header.h>
using namespace std;

// Complete the commonChild function below.
int commonChild(const string & s1, const string & s2)
{


}

int commonchild()
{
	const std::string project = "comchild";
	const std::string fileNum = "03";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	string s1;
	getline(inStr, s1);

	string s2;
	getline(inStr, s2);

	int result = commonChild(s1, s2);

	fout << result << "\n";

	fout.close();


	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
