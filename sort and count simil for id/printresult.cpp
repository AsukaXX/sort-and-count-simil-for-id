#include"id.h"

ostream& print(const similpath_v_e path, ostream& os, const text_v word) {
	ifstream f_c1, f_c2;
	set<int> index_f1, index_f2;
	set<string> text1, text2;
	string line, dirpath1, dirpath2;
	dirpath1 = finddir(path.first);
	dirpath2 = finddir(path.second);
	f_c1.open(dirpath1 + "\\index.txt");
	f_c2.open(dirpath2 + "\\index.txt");
	for (string s : word) {
		while (getline(f_c1, line)) {
			int i = line.find(" "), j = 0;
			if (i != string::npos)
				if (line.substr(0, i) == s) {
					j = i + 1;
					while ((i = line.find(",", i)) != string::npos) {
						string num1 = line.substr(j, i - j);
						int n1 = inttostring(num1);
						index_f1.insert(n1);
						j = ++i;
					}
					break;
				}
		}
		while (getline(f_c2, line)) {
			int i = line.find(" "), j = 0;
			if (i != string::npos)
				if (line.substr(0, i) == s) {
					j = i + 1;
					while ((i = line.find(",", i)) != string::npos) {
						string num2 = line.substr(j, i - j);
						int n2 = inttostring(num2);
						index_f2.insert(n2);
						j = ++i;
					}
					break;
				}
		}
	}
	f_c1.close();
	f_c2.close();
	f_c1.open(path.first);
	int line_no = 0;
	while (getline(f_c1, line)) {
		++line_no;
		if (index_f1.find(line_no) != index_f1.end()) {
			erasechar(line, "\t");
			text1.insert(line);
		}
	}
	f_c1.close();
	f_c2.open(path.second);
	line_no = 0;
	while (getline(f_c2, line)) {
		++line_no;
		if (index_f2.find(line_no) != index_f2.end()) {
			erasechar(line, "\t");
			//text2.push_back(line);
			if (text1.find(line) != text1.end())
				cout << line << endl;
		}
	}
	f_c2.close();
	/*if (text1.size() > text2.size())
		cout << path.first << "                  " << path.second << endl;
	else 
		cout << path.second << "                  " << path.first << endl;*/
	//display(text1, text2);
	return os;
}

void erasechar(string& str, const string e_str) {
	int i = str.find_first_not_of(e_str);
	if (i != string::npos)
		str.erase(0, i);
}

/*void display(const vector<string> text1, const vector<string> text2) {
	vector<string>::const_iterator it1, it2;
	it1 = text1.begin();
	it2 = text2.begin();
	while(it1 != text1.end() || it2 != text2.end()) {
		if (it1 == text1.end() && it2 != text2.end())
			cout << *it2 << "    |     " << " " << endl;
		if (it1 != text1.end() && it2 == text2.end())
			cout << *it1 << "    |     " << " " << endl;
		if (it1 != text1.end() && it2 != text2.end()) {
			if (text1.size() > text2.size())
				cout << *it1 << "     |     " << *it2 << endl;
			else
				cout << *it2 << "     |     " << *it1 << endl;
		}
		if (it1 != text1.end())
			++it1;
		if (it2 != text2.end())
			++it2;
	}
}*/