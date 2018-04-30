#include"sort.h"

void createindex(index& index_m, const string word, const int line) {
	index_it it_in;
	set<int> set_t;
	it_in = index_m.find(word);
	if (it_in == index_m.end()) {
		set_t.insert(line);
		index_m.insert(make_pair(word, set_t));
	}
	else {
		it_in->second.insert(line);
	}
}

sum_m scanfile(const vector<string> dir) {
	ifstream c_f;
	ofstream i_f;
	string line, word, word_t;
	index index_m;
	index_it index_it;
	sum_m pathsum;
	for (string path : dir) {
		//path = "D:\\C++\\serach\\serach\\simil_fuction.cpp";
		cout << path << endl;
		Sort s;
		int line_s = 0;
		c_f.open(path);
		s.dirctory(finddir(path));
		while (getline(c_f, line)) {
			++line_s;
			for (int i = 0; i < (int)line.size(); ++i) {
				if (judgeletter(line[i])) {
					word.push_back(line[i]);
				}
				else if (judgenumber(line[i])) {
					word.push_back(line[i]);
				}
				else if (line[i] != ' ' && line[i] != '\t'&&line[i] != '\n') {
					if (word.size() != 0) {
						s.wordlist_p(word,line_s);
						//cout << word<<endl;
						createindex(index_m, word, line_s);
						word.clear();
					}
					word.push_back(line[i]);
					s.wordlist_p(word,line_s);
					//cout << word << endl;
					//createindex(index_m, word, line_s);
					word.clear();
				}
				else if (line[i] == '/'&&line[i + 1] == '/') {
					word_t = line.substr(i + 2);
					continue;
				}
				else if (word.size() != 0) {
					word_t = word;
					s.wordlist_p(word,line_s);
					//cout << word << endl;
					createindex(index_m, word, line_s);
					word.clear();
				}
			}
			if (word.size() != 0) {
				word_t = word;
				s.wordlist_p(word,line_s);
				//cout << word << endl;
				createindex(index_m, word, line_s);
				word.clear();
			}
		}
		c_f.close();
		i_f.open(s.getpath()+"\\index.txt", ios::ate);
		for (index_it = index_m.begin(); index_it != index_m.end(); ++index_it) {
			i_f << index_it->first << " ";
			for (int i : index_it->second)
				i_f << i << ",";
			i_f << endl;
		}
		i_f.close();
		index_m.clear();
		s.sortword();
		s.print();
		pathsum.insert(make_pair(path,s.getsum()));
	}
	return pathsum;
}