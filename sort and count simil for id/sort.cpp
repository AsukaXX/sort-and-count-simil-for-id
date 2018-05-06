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
	cout << "sort!"<< endl;
	f_sys.open("D:/C++/sort and count simil for id/sort and count simil for id/sys.txt");
	while (getline(f_sys, line)) {
		int i = line.find(" ");
		string l = line.substr(0, i);
		int r = stringtoint(line.substr(i + 1, line.size()));
		sysword.insert(id_lines(l, r));
	}
	f_sys.close();
	f_sys.open("D:/C++/sort and count simil for id/sort and count simil for id/sym.txt");
	while (getline(f_sys, line)) {
		int i = line.find(" ");
		string l = line.substr(0, i);
		int r = stringtoint(line.substr(i + 1, line.size()));
		f_map.insert(id_lines(l, r));
	}
	f_sys.close();
	flag["class"] = 0;
	flag["function"] = 0;
	flag["output"] = 0;
	flag["cycle"] = 0;
	flag["headfile"] = 0;
	flag["enum"] = 0;
}

void Sort::wordlist_p(string s,int i) {
	wordlist.push(id_lines(s,i));
}

void Sort::sortword() {
	if (wordlist.empty())
		return;
	r_w.first = wordlist.front().first;
	lines = wordlist.front().second;
	wordlist.pop();
	while (!r_w.first.empty()) {
		word = r_w.first;
		if (!wordlist.empty()) {
			r_w.first = wordlist.front().first;
			lines = wordlist.front().second;
			wordlist.pop();
		}
		else
			r_w.first.clear();
		if (judgef())
			continue;
		if (judgeou())
			continue;
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
			if (word[0] == ':'&&!fun_t.empty()) {
				fun_t.append("_co");
				fun.push_back(fun_t);
				if (!cla_n.empty())
					cl_fu.push_back(fun_t);
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
			if (word[0] == '>'&&l_w.second == 105 && flag["headfile"] == 0) {
				l_w.first = word;
				l_w.second = 105;
				return 1;
			}
			s = f_map.find(word);
			if (s != f_map.end()) {
				if ((word[0] == '"' || word[0] == '>') && flag["headfile"] == 1)
					flag["headfile"] = 0;
				if (word[0] == '(') {
					stack_f.push_back(word);
				}
				if (word[0] == ')') {
					if (!word_t.empty() && l_w.first[0] == '(') {
						stack_s.push_back("fu");
						flag["function"] += 1;
						fun.push_back(word_t);
						fun_t = word_t;
						if (!cla_n.empty())
							cl_fu.push_back(word_t);
						word_t.clear();
					}
					stack_f.pop_back();
				}
				if (word[0] == '{') {
					if (!cla_t.empty() && flag["enum"] == 0 && flag["cycle"] == 0) {
						cla_n = cla_t;
						cla_t.clear();
						file.open(dir + "/" + cla_n + "_c.txt", ios::ate);
						file.close();
					}
					if (!fun_t.empty() && flag["enum"] == 0 && flag["cycle"] == 0) {
						fun_n = fun_t;
						fun_t.clear();
						if (!cla_n.empty()) {
							if (fun_n == cla_n) {
								fun.push_back(fun_n);
								cl_fu.push_back(fun_n);
							}
							fun_n = cla_n + "_" + fun_n;
						}
						if (!cl_in.empty()) {
							fun_n = cl_in + "_" + fun_n;
							cl_in.clear();
						}
						file.open(dir + "/" + fun_n + "_f.txt", ios::ate);
						file.close();
					}
					stack_f.push_back(word);
				}
				if (word[0] == '}' && stack_f.size() != 0) {
					if (stack_s.size() != 0) {
						if (stack_s.back() == "en")
							flag["enum"] -= 1;
						if (stack_s.back() == "cl") {
							flag["class"] -= 1;
							file.open(dir + "/" + cla_n + "_c.txt", ios::app);
							for (string s : cl_fu)
								file << s << endl;
							file.close();
							cla_n.clear();
							cl_fu.clear();
						}
						if (stack_s.back() == "fu") {
							flag["function"] -= 1;
							file.open(dir + "/" + fun_n + "_f.txt", ios::app);
							for (id_lines s : fu_vr)
								file << s.first << " " << s.second << endl;
							file.close();
							fun_n.clear();
							fu_vr.clear();
						}
						if (stack_s.back() == "cy")
							flag["cycle"] -= 1;
						//cout << flag["class"] << flag["function"] << stack_f.back() << stack_s.back() << endl;
						stack_s.pop_back();
					}
					stack_f.pop_back();

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
					if (flag["class"] == 0)
						cla_t.clear();
					if (flag["function"] == 0)
						fun_t.clear();
				}
				if (word_t.size() != 0 && word[0] == ')') {
					fun.push_back(word_t);
					flag["function"] += 1;
					stack_s.push_back("fu");
					word_t.clear();
					return 1;
				}
					l_w.first = word;
					l_w.second = s->second;//����
					return 1;
			}
			else {
				l_w.first = word;
				l_w.second = 9;
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
			fun_t = l_w.first;
			if (!cla_n.empty())
				cl_fu.push_back(l_w.first);
			l_w.first = word;
			l_w.second = 4;//������
			flag["function"] += 1;
			stack_s.push_back("fu");
			//stack_f.push_back(" ");
			return 1;
		}
		if (r_w.first[0] == '(') {
			if (!cla_n.empty() && word == cla_n) {
				flag["function"] += 1;
				stack_s.push_back("fu");
				fun_t = word;
			}

			l_w.first = word;
			l_w.second = 4;//������
			//flag["function"] += 1;
			//stack_s.push_back("fu");
			//stack_f.push_back(" ");
			//word_t = word;
			//if (!cla_n.empty())
				//cl_fu.push_back(word);
			return 1;
		}
		if (r_w.first[0] == ':')
			cl_in = word;
		if (l_w.second == 104) {
			flag["class"] += 1;
			stack_s.push_back("cl");
			cla_t = word;
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
		cla_t = word;
		word.clear();
		return 1;
	}
	return 0;
}

bool Sort::judges() {
	if (flag["headfile"] != 0) {
		headfile.push_back(id_lines(word,lines));
		l_w.first = word;
		l_w.second = 101;
		return 1;
	}
	if (flag["enum"] != 0) {
		l_w.first = word;
		l_w.second = 5;
		return 1;
	}
	s = sysword.find(word);
	if (s != sysword.end() && flag["output"] == 0) {
		if (word_t.size() != 0 && l_w.second == 903) {
			fun.push_back(word_t);
			flag["function"] += 1;
			stack_s.push_back("fu");
			fun_t = word_t;
			if (!cla_n.empty())
				cl_fu.push_back(word_t);
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
			fun.push_back(word);
			fun_t = word;
			if (!cla_n.empty())
				cl_fu.push_back(word);
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
			fun_t = word;
			if (!cla_n.empty())
				cl_fu.push_back(word);
			word.clear();
			return 1;
		}
		if (l_w.second == 918 && !cl_in.empty() && fun_t.empty()) {
			l_w.first = word;
			l_w.second = 4;
			fun.push_back(word);
			flag["function"] += 1;
			stack_s.push_back("fu");
			fun_t = word;
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
			//fun.push_back(word);
			l_w.first = word;
			l_w.second = 4;//������
			flag["function"] += 1;
			stack_s.push_back("fu");
			//stack_f.push_back(" ");
			if (flag["function"] == 0) {
				//fun_t = word;
				if (!cla_n.empty())
					cl_fu.push_back(word);
				veri.push_back(word);
			}
			else {
				fu_vr.push_back(id_lines(word, lines));
				veri_c.push_back(word);
			}
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
	if ((l_w.second == 902 || l_w.second == 911) && r_w.first.size() > 0 && judgeletter(r_w.first[0])) {
		l_w.first = word;
		l_w.second = 105;
		return 1;
	}
	if (flag["headfile"] != 0) {
		//sys.push_back(word);
		l_w.first = word;
		l_w.second = 101;//ͷ�ļ�
		headfile.push_back(id_lines(word,lines));
		return 1;
	}
	if ((judgeletter(r_w.first[0]) || r_w.first[0] == '&' || r_w.first[0] == '*') && word_t.size() != 0 && l_w.second == 903) {
		l_w.first = word;
		l_w.second = 105;
		fun.push_back(word_t);
		flag["function"] += 1;
		fun_t = word_t;
		if (!cla_n.empty())
			cl_fu.push_back(word_t);
		word_t.clear();
		return 1;
	}
	if (flag["function"] != 0) {
		if (word_t.size() != 0) {
			veri_c.push_back(word_t);
			word_t.clear();
		}
		veri_c.push_back(word);
		l_w.first = word;
		l_w.second = 5;//����
		fu_vr.push_back(id_lines(word,lines));
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
	cout << "wirte" << endl;
	ofstream count_f;
	sum_m count_m;
	count_f.open(dir + "/system.txt", ios::ate);
	for (string s : sys)
		count_f << s << endl;
	count_m.insert(id_lines("system", sys.size()));
	count_f.close();
	count_f.open(dir + "/class.txt", ios::ate);
	for (string s : cla)
		count_f << s << endl;
	count_m.insert(id_lines("class", cla.size()));
	count_f.close();
	count_f.open(dir + "/fuction.txt", ios::ate);
	for (string s : fun)
		count_f << s << endl;
	count_m.insert(id_lines("fuction", fun.size()));
	count_f.close();
	count_f.open(dir + "/output.txt", ios::ate);
	for (string s : out)
		count_f << s << endl;
	count_m.insert(id_lines("output", out.size()));
	count_f.close();
	count_f.open(dir + "/veriable_l.txt", ios::ate);
	for (string s : veri_c)
		count_f << s << endl;
	count_m.insert(id_lines("veriable_l", veri_c.size()));
	count_f.close();
	count_f.open(dir + "/veriable_g.txt", ios::ate);
	for (string s : veri)
		count_f << s << endl;
	count_m.insert(id_lines("veriable_g", veri.size()));
	count_f.close();
	count_f.open(dir + "/headfile.txt", ios::ate);
	for (id_lines s : headfile)
		count_f << s.first <<" "<< s.second << endl;
	count_m.insert(id_lines("headfile", headfile.size()));
	count_f.close();
	count_f.open(dir + "/count.txt", ios::ate);
	for (id_lines sum : count_m)
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
