#include"sort.h"
bool judgeletter(char c) {
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c == '_')
		return 1;
	else
		return 0;
}

bool judgenumber(char c) {
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}
inline int stringtoint(const string s) {
	int i = 0;
	istringstream ss(s);
	ss >> i;
	return i;
}

Sort::Sort() {
	ifstream f_sys;
	string line;
	f_sys.open("sys.txt");
	while (getline(f_sys, line)) {
		int i = line.find(" ");
		string l = line.substr(0, i);
		int r = stringtoint(line.substr(i + 1, line.size()));
		sysword.insert(pair<string, int>(l, r));
	}
	f_sys.close();
	f_sys.open("sym.txt");
	while (getline(f_sys, line)) {
		int i = line.find(" ");
		string l = line.substr(0, i);
		int r = stringtoint(line.substr(i + 1, line.size()));
		f_map.insert(pair<string, int>(l, r));
	}
	f_sys.close();
	flag["class"] = 0;
	flag["function"] = 0;
	flag["output"] = 0;
	flag["cycle"] = 0;
	flag["headfile"] = 0;
	flag["enum"] = 0;
}

void Sort::wordlist_p(string s) {
	wordlist.push(s);
}

void Sort::sortword() {
	r_w.first = wordlist.front();
	wordlist.pop();
	while (!wordlist.empty()) {
		word = r_w.first;
		r_w.first = wordlist.front();
		wordlist.pop();
		if (judgef())
			continue;
		if (judgeou())
			continue;
		/*for (char w : word) {
		if (judgenumber(w)) {
		if (word_t.size() != 0 && l_w.second == 903) {
		if (flag["function"] != 0)
		veri_c.push_back(word_t);
		else
		veri.push_back(word_t);
		word_t.clear();
		}
		l_w.first = word;
		l_w.second = 5;//����
		if (flag["function"] != 0) {
		veri_c.push_back(word);
		}
		else
		veri.push_back(word);
		word.clear();
		break;
		}
		}*/
		if (word.empty())
			continue;
		if (judges())
			continue;
		if (judgecl())
			continue;
		if (judgefu())
			continue;
		if (judgel())
			continue;
		if (judgev())
			continue;
	}
}

bool Sort::judgef() {
	if (word.size() == 1) {
		if (!judgeletter(word[0]) && !judgenumber(word[0])) {
			if (flag["output"] == 1) {
				if (word[0] == '"'&&l_w.second != '\\')
					flag["output"] = 0;
				l_w.first = word;
				l_w.second = 8;//���
				return 1;
			}
			if ((word[0] == '"' || word[0] == '<') && l_w.second == 101 && flag["headfile"] == 0) {
				l_w.first = word;
				l_w.second = 101;
				flag["headfile"] = 1;
				return 1;
			}
			if (word[0] == '"'&&flag["headfile"] == 0) {
				flag["output"] = 1;
				l_w.first = word;
				l_w.second = 8;
				return 1;
			}
			if (word[0] == '&'&&l_w.second == 105) {
				l_w.first = word;
				l_w.second = 105;
				return 1;
			}
			if (word[0] == '>'&&l_w.second == 105&&flag["headfile"]==0) {
				l_w.first = word;
				l_w.second = 105;
				return 1;
			}
			s = f_map.find(word);
			if (s != f_map.end()) {
				l_w.first = word;
				l_w.second = s->second;//����
				if ((word[0] == '"' || word[0] == '>') && flag["headfile"] == 1)
					flag["headfile"] = 0;
				if (word[0] == '(') {
					stack_f.push_back(word);
				}
				if (word[0] == ')') {
					stack_f.pop_back();
				}
				if (word[0] == '{') {
					stack_f.push_back(word);
				}
				if (word[0] == '}'&&stack_f.size() != 0) {
					if (stack_s.back() == "en")
						flag["enum"] -= 1;
					if (stack_s.back() == "cl")
						flag["class"] -= 1;
					if (stack_s.back() == "fu")
						flag["function"] -= 1;
					if (stack_s.back() == "cy")
						flag["cycle"] -= 1;
					//cout << flag["class"] << flag["function"] << stack_f.back() << stack_s.back() << endl;
					stack_f.pop_back();
					stack_s.pop_back();
					/*if (flag["class"] == 0) {
					flag["function"] = 0;
					stack_s.clear();
					stack_f.clear();
					}*/

				}
				if (word[0] == ';'&&stack_f.size() != 0) {
					//if(stack_f.back()!="("){
					while (stack_f.size() < stack_s.size()) {
						if (stack_s.back() == "cl")
							flag["class"] -= 1;
						if (stack_s.back() == "fu")
							flag["function"] -= 1;
						if (stack_s.back() == "cy")
							flag["cycle"] -= 1;
						stack_s.pop_back();
					}
					//stack_f.pop_back();
					//}
				}
				if (word_t.size() != 0 && word[0] == ')') {
					fun.push_back(word_t);
					flag["function"] += 1;
					stack_s.push_back("fu");

					word_t.clear();
				}
				return 1;
			}
			else {
				l_w.first = word;
				l_w.second = 9;//����
				return 1;
			}
		}
	}
	return 0;
}

bool Sort::judgecl() {
	s_v = find(cla.begin(), cla.end(), word);
	if (s_v != cla.end() && flag["output"] == 0) {
		if (l_w.second == 917) {
			fun.push_back(l_w.first.append(word));
			l_w.first = word;
			l_w.second = 4;//������
			flag["function"] += 1;
			stack_s.push_back("fu");
			//stack_f.push_back(" ");
			return 1;
		}
		if (r_w.first[0] == '(') {
			fun.push_back(word);
			l_w.first = word;
			l_w.second = 4;//������
			flag["function"] += 1;
			stack_s.push_back("fu");
			//stack_f.push_back(" ");
			return 1;
		}
		if (l_w.second == 104) {
			flag["class"] += 1;
			stack_s.push_back("cl");
		}
		l_w.first = word;
		l_w.second = 105;//����
		return 1;
	}
	if (l_w.second == 104) {
		cla.push_back(word);
		l_w.first = word;
		l_w.second = 105;//����
		flag["class"] += 1;
		stack_s.push_back("cl");
		//stack_f.push_back(" ");
		word.clear();
		return 1;
	}
	return 0;
}

bool Sort::judges() {
	s = sysword.find(word);
	if (s != sysword.end() && flag["output"] == 0) {
		if (word_t.size() != 0 && l_w.second == 903) {
			fun.push_back(word_t);
			flag["function"] += 1;
			stack_s.push_back("fu");
			word_t.clear();
		}
		l_w.first = word;
		l_w.second = s->second;//ϵͳ������
		sys.push_back(word);
		if (s->second == 106) {
			//stack_f.push_back(" ");
			stack_s.push_back("cy");
			flag["cycle"] += 1;
		}
		if (s->second == 109) {
			//stack_f.push_back(" ");
			stack_s.push_back("fu");
			flag["function"] += 1;
		}
		if (s->first == "enum") {
			stack_s.push_back("en");
			flag["enum"] += 1;
		}
		return 1;
	}
	return 0;
}

bool Sort::judgefu() {
	if (flag["output"] == 0) {
		s_v = find(fun.begin(), fun.end(), word);
		if (s_v != fun.end()) {
			l_w.first = word;
			l_w.second = 4;//������
			fun.push_back(word);
			flag["function"] += 1;
			stack_s.push_back("fu");
			//stack_f.push_back(" ");
			word.clear();
			return 1;
		}
		if (l_w.second == 105 && r_w.first[0] == '(') {
			l_w.first = word;
			l_w.second = 20;//�������������
							//stack_s.push_back("fu");
							//fun.push_back(word);
			word_t = word;
			//stack_f.push_back(" ");
			return 1;
		}
		if ((l_w.second == 913 || l_w.second == 911 || l_w.second == 902) && r_w.first[0] == '(') {
			fun.push_back(word);
			l_w.first = word;
			l_w.second = 4;//������
			flag["function"] += 1;
			stack_s.push_back("fu");
			//stack_f.push_back(" ");
			word.clear();
			return 1;
		}
	}
	return 0;
}

bool Sort::judgeou() {
	/*if (l_w.second == 8) {
	out.push_back(word);
	l_w.first = word;
	l_w.second = 8;//���
	word.clear();
	return 1;
	}*/
	if (flag["output"] == 1) {
		out.push_back(word);
		l_w.first = word;
		l_w.second = 8;//���
		word.clear();
		return 1;
	}
	return 0;
}

bool Sort::judgel() {
	if (r_w.first[0] == ';'&&l_w.second == 103) {
		l_w.first = word;
		l_w.second = 120;//�����ռ�
		sys.push_back(word);
		word.clear();
		return 1;
	}
	return 0;
}

bool Sort::judgev() {
	if (flag["headfile"] != 0) {
		sys.push_back(word);
		l_w.first = word;
		l_w.second = 101;//ͷ�ļ�
		return 1;
	}
	if ((judgeletter(r_w.first[0]) || r_w.first[0] == '&' || r_w.first[0] == '*') && word_t.size() != 0 && l_w.second == 903) {
		fun.push_back(word_t);
		flag["function"] += 1;
		word_t.clear();
	}
	if (flag["function"] != 0) {
		if (word_t.size() != 0) {
			veri_c.push_back(word_t);
			word_t.clear();
		}
		veri_c.push_back(word);
		l_w.first = word;
		l_w.second = 5;//����
		word.clear();
		return 1;
	}
	else {
		if (word_t.size() != 0) {
			veri.push_back(word_t);
			word_t.clear();
		}
		veri.push_back(word);
		l_w.first = word;
		l_w.second = 5;//����
		word.clear();
		return 1;
	}
	return 0;
}

void Sort::print() {
	/*cout << "sys:" << endl;
	for (string s : sys)
	cout << s << endl;
	cout << "fun:" << endl;
	for (string s : fun)
	cout << s << endl;
	cout << "ver:" << endl;
	for (string s : veri)
	cout << s << endl;
	cout << "cla:" << endl;
	for (string s : cla)
	cout << s << endl;
	cout << "out:" << endl;
	for (string s : out)
	cout << s << endl;
	cout << "ver_c:" << endl;
	for (string s : veri_c)
	cout << s << endl;*/
	cout << "wirte" << endl;
	ofstream count_f;
	sum_m count_m;
	count_f.open(dir + "\\system.txt", ios::ate);
	for (string s : sys)
		count_f << s << endl;
	count_m.insert(sum_m_e("system", sys.size()));
	count_f.close();
	count_f.open(dir + "\\class.txt", ios::ate);
	for (string s : cla)
		count_f << s << endl;
	count_m.insert(sum_m_e("class", cla.size()));
	count_f.close();
	count_f.open(dir + "\\fuction.txt", ios::ate);
	for (string s : fun)
		count_f << s << endl;
	count_m.insert(sum_m_e("fuction", fun.size()));
	count_f.close();
	count_f.open(dir + "\\output.txt", ios::ate);
	for (string s : out)
		count_f << s << endl;
	count_m.insert(sum_m_e("output", out.size()));
	count_f.close();
	count_f.open(dir + "\\veriable_l.txt", ios::ate);
	for (string s : veri_c)
		count_f << s << endl;
	count_m.insert(sum_m_e("veriable_l", veri_c.size()));
	count_f.close();
	count_f.open(dir + "\\veriable_g.txt", ios::ate);
	for (string s : veri)
		count_f << s << endl;
	count_m.insert(sum_m_e("veriable_g", veri.size()));
	count_f.close();
	count_f.open(dir + "\\count.txt", ios::ate);
	for (sum_m_e sum : count_m)
		count_f << sum.first << " " << sum.second << endl;
	cout << "finish" << endl;
	sum = sys.size() + cla.size() + out.size() + fun.size() + veri_c.size() + veri.size();
	//cout << flag["class"] << flag["function"] << stack_f.back() << stack_s.back() << endl;
}

void Sort::dirctory(string path) {
	dir = path;
}

int Sort::getsum() {
	return sum;
}

string Sort::getpath() {
	return dir;
}
