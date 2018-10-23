#include <header.h>

#include <bits/stdc++.h>

using namespace std;

// Complete the maximumSum function below.
long maximumSum(const vector<long> & a, long m)
{
	std::set<long> lasts{m}; /// for empty prefix
	long tmp = a[0] % m;
	lasts.emplace(tmp);
	long res = tmp;
	for(int i = 1; i < a.size(); ++i)
	{
		tmp = (tmp + a[i] % m) % m;
		lasts.emplace(tmp);
		res = std::max(res, tmp - *lasts.upper_bound(tmp) + m);
	}
	return res;
}

int subarr()
{
	const std::string project = "maxsub"; //balanced
	const std::string fileNum = "01";

	std::ofstream fout(prePath + project + "/" + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + "/" + project + fileNum + ".txt");


	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string nm_temp;
		getline(inStr, nm_temp);

		vector<string> nm = split_string(nm_temp);

		int n = stoi(nm[0]);

		long m = stol(nm[1]);

		string a_temp_temp;
		getline(inStr, a_temp_temp);

		vector<string> a_temp = split_string(a_temp_temp);

		vector<long> a(n);

		for (int i = 0; i < n; i++) {
			long a_item = stol(a_temp[i]);

			a[i] = a_item;
		}

		long result = maximumSum(a, m);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + "/" + project + fileNum + "out.txt",
							   prePath + project + "/" + project + fileNum + "output.txt") << std::endl;

	return 0;
}
