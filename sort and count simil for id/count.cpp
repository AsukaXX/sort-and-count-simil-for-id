#include"id.h"

void countsimil(const sum_m sum) {
	sum_m::const_iterator s_it1, s_it2;
	similpath_v similpath;
	sum_m path_v1, path_v2;
	string dirpath1, filepath1, filepath2, dirpath2;
	int sum1 = 0, sum2 = 0;
	double c_result = 0.0, d_result = 0.0, d_2_result = 0.0;
	s_it1 = sum.begin();
	for (; s_it1 != sum.end(); ) {
		initialize(path_v1);
		filepath1 = s_it1->first;
		dirpath1 = finddir(filepath1);
		sum1 = s_it1->second;
		slove_v(dirpath1, path_v1);
		path_v1.insert(id_lines("sum", sum1));
		for (s_it2 = ++s_it1; s_it2 != sum.end(); s_it2++) {
			filepath2 = s_it2->first;
			dirpath2 = finddir(filepath2);
			sum2 = s_it2->second;
			if ((sum1 > sum2 ? (double)sum1 / sum2 : (double)sum2 / sum1) > 0.7) {
				initialize(path_v2);
				slove_v(dirpath2, path_v2);
				path_v2.insert(id_lines("sum", sum2));
				c_result = cos_simil(path_v1, path_v2);
				d_result = dist_simil(path_v1, path_v2);
				d_2_result = dist_2_simil(path_v1, path_v2);
				cout << filepath1 << " " << filepath2 << endl;
				cout << c_result << " " << d_result << " " << d_2_result << endl;
			}
			if (c_result > 0.99||d_result > 0.1||d_2_result > 0.5) {
				cout << filepath1 << " " << filepath2 << endl;
				similpath.push_back(similpath_v_e(filepath1, filepath2));
			}
		}
	}
	wordsimil(similpath);
}

inline void initialize(sum_m& s_m) {
	s_m.clear();
	s_m.insert(id_lines("classn", 0));
	s_m.insert(id_lines("function", 0));
	s_m.insert(id_lines("output", 0));
	s_m.insert(id_lines("system", 0));
	s_m.insert(id_lines("headfile", 0));
	s_m.insert(id_lines("gol", 0));
	s_m.insert(id_lines("loc", 0));
}

inline int inttostring(const string ss) {
	stringstream str_m(ss);
	int i = 0;
	str_m >> i;
	return i;
}

void slove_v(const string path, sum_m& path_v) {
	ifstream count_f;
	enum golb {
		begin,
		system,
		headfile,
		output,
		function,
		classn,
		end,
	};
	map<string, golb> count_m;
	count_m["system"] = system;
	count_m["headfile"] = headfile;
	count_m["output"] = output;
	count_m["function"] = function;
	count_m["classn"] = classn;
	count_f.open(path + "\\count.txt");
	string line, c_name, c_sum;
	while (getline(count_f, line)) {
		int i = line.rfind(" ");
		c_name = line.substr(0, i);
		c_sum = line.substr(i + 1, line.size());
		switch (count_m[c_name]) {
		case system:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		case headfile:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		case output:
			inster("loc", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		case function:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		case classn:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		default:
			inster("loc", inttostring(c_sum), path_v);
			break;
		}
	}
}

inline void inster(const string n, int i, sum_m& path_v) {
	sum_m::iterator s;
	s = path_v.find(n);
	if (s == path_v.end())
		path_v.insert(id_lines(n, i));
	else
		s->second += i;
}

path_s readfilename(const string p) {
	ifstream f_c;
	path_s f_n;
	string line;
	f_c.open(p + "\\count.txt");
	while (getline(f_c, line)) {
		int i = line.find(" ");
		if(inttostring(line.substr(i+1,line.size()))!=0)
			f_n.insert(line.substr(0, i));
	}
	return f_n;
}

void wordsimil(const similpath_v path) {
	ifstream c_fs;
	string id,dirpath1,dirpath2,filepath1,filepath2,line;
	int d_v = 0, s_w = 0, s_f = 0,d_f=0;
	double	c_f = 0.0;
	path_s st1, p1, p2, sameword;
	set<string>::iterator s;
	path_s::const_iterator p_n;
	cout << "start" << endl;
	for (similpath_v_e p : path) {
		d_v = 0;
		s_f = 0;
		d_f = 0;
		filepath1 = p.first;
		filepath2 = p.second;
		dirpath1 = finddir(filepath1);
		dirpath2 = finddir(filepath2);
		cout << filepath1 << " " << filepath2 << endl;
		if (fileempty(dirpath1 + "\\class.txt") && fileempty(dirpath2 + "\\class.txt")) {
			text_v cla_s, fun_s;
			text_l_v ver_s1, ver_s2;
			if (comparetext(dirpath1 + "\\class.txt", dirpath2 + "\\class.txt",cla_s)) {
				for (string c : cla_s) {
					if (comparetext(dirpath1 + "\\" + c + "_c.txt", dirpath2 + "\\" + c + "_c.txt", fun_s)) {
						for (string f : fun_s) {
							if (comparetext(dirpath1 + "\\" + c + "_" + f + "_f.txt", dirpath1 + "\\" + c + "_" + f + "_f.txt", ver_s1,ver_s2)) {
								cout << c << ":" << f << ":" << endl;
								print(p, cout, ver_s1,ver_s2);
								ver_s1.clear();
								ver_s2.clear();
								//cout << c << " " << f << endl;
							//else
								//cout << c << " " << f << endl;
							}
						}
						fun_s.clear();
					}
				}
				cla_s.clear();
			}
		}
		else {
			text_v fun_s;
			text_l_v ver_s1, ver_s2;
			if (comparetext(dirpath1 + "\\fuction.txt", dirpath2 + "\\fuction.txt", fun_s)) {
				for (string f : fun_s) {
					if (comparetext(dirpath1 + "\\" + f + "_f.txt", dirpath1 + "\\" + f + "_f.txt", ver_s1,ver_s2)) {
						cout << f << ":" << endl;
						print(p, cout, ver_s1,ver_s2);
						ver_s1.clear();
						ver_s2.clear();
						//cout << f << endl;
					}
				}
				fun_s.clear();
			}
		}
		

		/*p1 = readfilename(dirpath1);
		p2 = readfilename(dirpath2);
		for (string sf_p : p1) {
			p_n = p2.find(sf_p);
			if (p_n != p2.end()) {
				if (comparetext(dirpath1 + "\\" + sf_p + ".txt", dirpath2 + "\\" + sf_p + ".txt")) {
					text_v f_l, f_r;
					f_l = readetext(dirpath1 + "\\" + sf_p + ".txt");
					f_r = readetext(dirpath2 + "\\" + sf_p + ".txt");

				}
				c_fs.open(dirpath1 + "\\" + sf_p + ".txt");
				while (getline(c_fs, id)) {
					st1.insert(id);
				}
				c_fs.close();
				c_fs.open(dirpath2 + "\\" + sf_p + ".txt");
				while (getline(c_fs, id)) {
					s = find(st1.begin(), st1.end(), id);
					if (s != st1.end()) {
						sameword.insert(id);
						++c_s;
					}
					//++s_f;
				}
				c_fs.close();
				if (c_s ==0) {
					d_f = 1;
					st1.clear();
					break;
				}
			}
			st1.clear();
		}
		
		//for (string s : sameword)
		//	cout << s << endl;
		if(d_f==0)
			print(p, cout, sameword);
		sameword.clear();*/
	}
}

inline text_l_v readetext(const string file) {
	ifstream fs;
	text_l_v text;
	id_lines text_l;
	string line;
	fs.open(file);
	while (getline(fs, line)) {
		int i = line.find(" ");
		text_l.first = line.substr(0, i);
		text_l.second = inttostring(line.substr(i+1, line.size()));
		text.push_back(text_l);
	}
	fs.close();
	return text;
}

inline text_v readtext(const string file) {
	ifstream fs;
	text_v text;
	string line;
	fs.open(file);
	while (getline(fs, line)) 
		text.push_back(line);
	return text;
}

inline int fileempty(const string path1) {
	ifstream fs;
	fs.open(path1);
	fs.seekg(0, ios::end);
	streampos ps = fs.tellg();
	if ((int)ps==0)
		return 0;
	else
		return 1;
}


int comparetext(const string file_l, const string file_r,text_l_v& same1,text_l_v& same2) {
	ifstream fs;
	text_l_v text_l, text_r;
	id_lines it_t;
	text_l = readetext(file_l);
	text_r = readetext(file_r);
	int dif_n = 0;
	for (id_lines t : text_l) {
		it_t = find_t(text_r.begin(), text_r.end(), t.first);
		if (it_t==id_lines(" ",-1))
			dif_n++;
		else {
			same1.push_back(t);
			same2.push_back(it_t);
		}
	}
	if ((double)dif_n / (text_l.size() > text_l.size() ? text_l.size() : text_r.size()) > 0.5)
		return 0;
	else
		return 1;
}

int comparetext(const string file_l, const string file_r, text_v& same) {
	ifstream fs;
	text_v text_l, text_r;
	text_v::iterator it_t;
	text_l = readtext(file_l);
	text_r = readtext(file_r);
	int dif_n = 0;
	for (string t : text_l) {
		it_t = find(text_r.begin(), text_r.end(), t);
		if (it_t == text_l.end())
			dif_n++;
		else
			same.push_back(*it_t);
	}
	if ((double)dif_n / (text_l.size() > text_l.size() ? text_l.size() : text_r.size()) > 0.5)
		return 0;
	else
		return 1;
}

inline id_lines find_t(text_l_v::iterator begin, text_l_v::iterator end, const string s) {
	text_l_v::iterator it;
	for (it = begin; it != end; it++) {
		if (it->first == s)
			return *it;
	}
	return id_lines(" ",-1);
}