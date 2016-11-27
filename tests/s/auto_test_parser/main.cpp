#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "..\..\..\src\run\run.h"

using namespace std;

const int TESTS_NUMBER = 118;

bool compare_files(const char *file_name1, const char *file_name2) {
	FILE *f1 = fopen(file_name1, "r");
	FILE *f2 = fopen(file_name2, "r");
	if (!f1 || !f2)
		return false;
	bool res = true;
	while (1) {
		char ch1, ch2;
		int x1 = fscanf(f1, "%c", &ch1);
		int x2 = fscanf(f2, "%c", &ch2);
		if (x1 != EOF && x2 == EOF || x1 == EOF && x2 != EOF || ch1 != ch2)
			res = false;
		if (x1 == EOF || x2 == EOF)
			break;
	}
	fclose(f1);
	fclose(f2);
	return res;
}

int main()
{
	int ok_cnt = 0;
	for (int i = 1; i <= TESTS_NUMBER; ++i)
	{
		char s1[10];
		sprintf(s1, "%d", i);
		string s(s1);
		if (s.length() == 1)
			s = "0" + s;
		s = "..\\" + s;
		string input_file_name = s + ".tst";
		string output_file_name = s + ".out";
		string answer_file_name = s + ".ans";
		ofstream fout(output_file_name.c_str());
		RunParser(input_file_name.c_str(), fout);
		fout.close();
		bool res = compare_files(
			output_file_name.c_str(), answer_file_name.c_str());
		cout << "Test " << i << " ";
		if (res) {
			remove(output_file_name.c_str());
			cout << "OK";
			++ok_cnt;
		}
		else
			cout << "WA";
		cout << endl;
	}

	cout << '\n' << "Total: " << ok_cnt << " OK, " << TESTS_NUMBER-ok_cnt << " WA" << '\n';

	return 0;
}
