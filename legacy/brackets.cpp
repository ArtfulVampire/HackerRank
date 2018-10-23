#include <bits/stdc++.h>
#include <header.h>

using namespace std;

// Complete the isBalanced function below.
string isBalanced(string s)
{
	static const std::vector<std::pair<char, char>> br{{'{', '}'}, {'(', ')'}, {'[', ']'}};
	std::stack<char> st{};
	for(char in : s)
	{
		for(const auto & b : br)
		{
			if(in == b.second)
			{
				if(st.empty() || st.top() != b.first) return "NO";
				st.pop();
			}
			else if(in == b.first)
			{
				st.push(in);
			}
		}
	}
	if(!st.empty()) return "NO";
	return "YES";
}

int brackets()
{
	const std::string project = "brackets"; //
	const std::string fileNum = "04";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int t;
	inStr >> t;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string s;
		getline(inStr, s);

		string result = isBalanced(s);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
