#pragma once 
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<algorithm>
#include<io.h>
#include<math.h>

using namespace std;
using index = map<string, set<int>>;
using index_it = map<string, set<int>>::iterator;
using similpath_v = vector< pair<string, string>>;
using sum_m = map<string, int>;
using similpath_v_e = pair<string, string>;
using sum_m_e = pair<string, int>;
using path_s = set<string>;

bool judgenumber(char c);
bool judgeletter(char c);

void getDirectory(const string path,vector<string>& dir);
string finddir(const string filepath);
void sortid(const string path);

sum_m scanfile(const vector<string> dir);

void countsimil(const sum_m sum);
inline void initialize(sum_m& s_m);
inline int inttostring(const string ss);
inline void inster(const string n, int i, sum_m& path_v);
void slove_v(const string path, sum_m& path_v);
void wordsimil(const similpath_v path);

inline vector<double> readvector(const sum_m path_v);
inline double max_d(const double l, const double r);
double cos_simil(const sum_m path_v1, const sum_m path_v2);
double dist_simil(const sum_m path_v1, const sum_m path_v2);
double dist_2_simil(const sum_m path_v1, const sum_m path_v2);

ostream& print(const similpath_v_e path, ostream& os, const set<string> word);
void erasechar(string& str, const string e_str);
void display(const vector<string> text1, const vector<string> text2);