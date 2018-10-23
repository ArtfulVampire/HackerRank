#include <bits/stdc++.h>
#include <header.h>

using namespace std;

void preprocess(std::vector<int> & in)
{
	std::set<int, std::greater<>> st{std::begin(in), std::end(in)};
	in.resize(st.size());
	std::copy(std::begin(st), std::end(st), std::begin(in));
}

// Complete the triplets function below.
long triplets(vector<int> a, vector<int> b, vector<int> c)
{
	preprocess(a);
	preprocess(b);
	preprocess(c);

	auto it1 = std::begin(a);
	auto it3 = std::begin(c);

	long res{0};
	int prevb{-100};
	for(auto in : b)
	{
		if(in == prevb) { continue; }
		it1 = std::lower_bound(it1, std::end(a), in, std::greater<int>());
		it3 = std::lower_bound(it3, std::end(c), in, std::greater<int>());


		auto m = std::distance(it1, std::end(a));
		auto n = std::distance(it3, std::end(c));
		if(m * n == 0) { break; }
//		std::cout << m << "\t" << n << std::endl;
		res += m * n;
		prevb = in;
	}
	return res;
}

int triplesum()
{
	const std::string project = "triple";
	const std::string fileNum = "02";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	string lenaLenbLenc_temp;
	getline(inStr, lenaLenbLenc_temp);

	vector<string> lenaLenbLenc = split(lenaLenbLenc_temp);

	int lena = stoi(lenaLenbLenc[0]);

	int lenb = stoi(lenaLenbLenc[1]);

	int lenc = stoi(lenaLenbLenc[2]);

	string arra_temp_temp;
	getline(inStr, arra_temp_temp);

	vector<string> arra_temp = split(arra_temp_temp);

	vector<int> arra(lena);

	for (int i = 0; i < lena; i++) {
		int arra_item = stoi(arra_temp[i]);

		arra[i] = arra_item;
	}

	string arrb_temp_temp;
	getline(inStr, arrb_temp_temp);

	vector<string> arrb_temp = split(arrb_temp_temp);

	vector<int> arrb(lenb);

	for (int i = 0; i < lenb; i++) {
		int arrb_item = stoi(arrb_temp[i]);

		arrb[i] = arrb_item;
	}

	string arrc_temp_temp;
	getline(inStr, arrc_temp_temp);

	vector<string> arrc_temp = split(arrc_temp_temp);

	vector<int> arrc(lenc);

	for (int i = 0; i < lenc; i++) {
		int arrc_item = stoi(arrc_temp[i]);

		arrc[i] = arrc_item;
	}

	long ans = triplets(arra, arrb, arrc);

	fout << ans << "\n";

	fout.close();

	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;
	return 0;
}
