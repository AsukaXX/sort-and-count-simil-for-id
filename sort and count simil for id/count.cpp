#include"id.h"

void countsimil(const sum_m sum,similpath_v& similpath) {
	sum_m::const_iterator s_it1, s_it2;
	//similpath_v similpath;
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
				//cout << filepath1 << " " << filepath2 << endl;
				//cout << c_result << " " << d_result << " " << d_2_result << endl;
			}
			if (c_result > 0.99||d_result > 0.1||d_2_result > 0.5) {
				//cout << filepath1 << " " << filepath2 << endl;
				similpath.push_back(similpath_v_e(filepath1, filepath2));
			}
		}
	}
}

inline void initialize(sum_m& s_m) {
	s_m.clear();
	s_m.insert(id_lines("class", 0));
	s_m.insert(id_lines("fuction", 0));
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
	count_m["fuction"] = function;
	count_m["class"] = classn;
	count_f.open(path + "/count.txt");
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

