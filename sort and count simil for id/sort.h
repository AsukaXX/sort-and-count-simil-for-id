#pragma once
#include"id.h"

class Sort {
public:
	Sort();
	~Sort() {};
	int getsum();
	string getpath();
	void dirctory(string path);
	void wordlist_p(string s);
	void sortword();
	bool judgef();
	bool judges();
	bool judgel();
	bool judgecl();
	bool judgefu();
	bool judgeou();
	bool judgev();
	void print();
private:
	int sum = 0;
	map<string, int> sysword, f_map, flag;
	queue<string> wordlist;
	string word, word_t, dir;
	pair<string, int> l_w, r_w;
	vector<string> fun, veri, sys, cla, out, veri_c, stack_s, stack_f;
	map<string, int>::iterator s;
	vector<string>::iterator s_v;
};