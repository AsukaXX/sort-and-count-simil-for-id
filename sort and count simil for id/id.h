#pragma once 
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<list>
#include<algorithm>
#include<io.h>
#include<math.h>

using namespace std;
using index = map<string, set<int>>;
using index_it = map<string, set<int>>::iterator;
using similpath_v = vector< pair<string, string>>;
using sum_m = map<string, int>;
using similpath_v_e = pair<string, string>;
using path_s = set<string>;
using text_l_v = vector<pair<string,int>>;
using text_v = vector<string>;
using id_lines = pair<string, int>;
using result = list<pair<string, text_l_v>>;

bool judgenumber(char c);
bool judgeletter(char c);

void getDirectory(const string path,vector<string>& dir);
string finddir(const string filepath);
similpath_v sortid(const string path);

sum_m scanfile(const vector<string> dir);

void countsimil(const sum_m sum,similpath_v& similpath);
inline void initialize(sum_m& s_m);
inline int inttostring(const string ss);
inline void inster(const string n, int i, sum_m& path_v);
void slove_v(const string path, sum_m& path_v);
//void wordsimil(const similpath_v path,result& similresult);
inline text_v readetext(const string file, const string path);
inline text_l_v readetext(const string file);
inline int fileempty(const string path1);
int comparetext(const string file_l, const string file_r, text_v& same);
//int comparetext(const string file_l, const string file_r, text_l_v& same1, text_l_v& same2);
inline text_l_v::iterator find_t(text_l_v::iterator begin, text_l_v::iterator end, const string s);

inline vector<double> readvector(const sum_m path_v);
inline double max_d(const double l, const double r);
double cos_simil(const sum_m path_v1, const sum_m path_v2);
double dist_simil(const sum_m path_v1, const sum_m path_v2);
double dist_2_simil(const sum_m path_v1, const sum_m path_v2);

//ostream& print(const similpath_v_e path, ostream& os, const text_l_v word1,const text_l_v word2);
void erasechar(string& str, const string e_str);
void display(const vector<string> text1, const vector<string> text2);

void setresult(similpath_v_e p, text_l_v text_l, text_l_v text_r);