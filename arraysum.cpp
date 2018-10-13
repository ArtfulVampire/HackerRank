#include <bits/stdc++.h>
#include <header.h>

using namespace std;


// Complete the maxSubsetSum function below.
int maxSubsetSum(const vector<int> &  arr)
{
	std::vector<int> res(arr.size());
	res[arr.size() - 1] = arr[arr.size() - 1];
	res[arr.size() - 2] = std::max(arr[arr.size() - 1], arr[arr.size() - 2]);
	for(int i = arr.size() - 3; i >= 0; --i)
	{
		res[i] = std::max(arr[i] + std::max(res[i+2], 0), res[i+2]);
	}
	return res[0];
}


int arraysum()
{

	const std::string project = "arrsum";
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int n;
	inStr >> n;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	string arr_temp_temp;
	getline(inStr, arr_temp_temp);

	vector<string> arr_temp = split(arr_temp_temp);

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		int arr_item = stoi(arr_temp[i]);

		arr[i] = arr_item;
	}


	int res = maxSubsetSum(arr);

	fout << res << "\n";

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
