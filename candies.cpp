#include <bits/stdc++.h>
#include <header.h>

using namespace std;

long prevNum = 0;
long res = 0;

void candiesRec(const vector<int> & arr, int sta)
{
	if(sta >= arr.size()) { return; }
	int stop = arr.size() - 1; /// for the last chunk
	for(int i = sta + 1; i < arr.size(); ++i)
	{
		if(arr[i] >= arr[i - 1])
		{
			stop = i - 1;
			break;
		}
	}

	long siz = stop - sta + 1;
	if(sta > 0 && arr[sta] == arr[sta - 1])
	{
		res += siz * (siz + 1) / 2;
		prevNum = 1;
	}
	else
	{
		if(siz > 1)
		{
			res += (siz - 1) * siz / 2;
			res += std::max(siz, prevNum + 1);
			prevNum = 1;
		}
		else
		{
			res += prevNum + 1;
			++prevNum;
		}
	}
	candiesRec(arr, stop + 1);
}

// Complete the candies function below.
long candies(int n, const vector<int> & arr)
{
	res = 0;
	prevNum = 0;
	if(arr.size() == 1) return 1;
	if(arr.size() == 2)
	{
		return 2 + (arr[0] != arr[1]);
	}
	candiesRec(arr, 0);
	return res;

}



int candies()
{
	const std::string project = "candies";
	const std::string fileNum = "11";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int n;
	inStr >> n;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		int arr_item;
		inStr >> arr_item;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');

		arr[i] = arr_item;
	}

	long result = candies(n, arr);

	fout << result << "\n";


	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
