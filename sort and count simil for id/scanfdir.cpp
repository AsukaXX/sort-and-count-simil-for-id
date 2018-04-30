#include"id.h"

void getDirectory(const string path,vector<string>& dir) {
	long hfile;
	static _finddata_t fileinfo;
	string p;
	if ((hfile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
				if (fileinfo.attrib == _A_SUBDIR) {
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						getDirectory(path + "\\" + fileinfo.name,dir);
					}
				}
				if (fileinfo.attrib != _A_SUBDIR) {
					string cp = fileinfo.name;
					if(cp.find(".cpp")!=string::npos)
						dir.push_back(path + "\\" + fileinfo.name);
				}
		} while (_findnext(hfile, &fileinfo) == 0);
	}
	_findclose(hfile);
}

string finddir(const string filepath) {
	return filepath.substr(0, filepath.rfind("\\"));
}

void sortid(const string path) {
	vector<string> filedir;
	sum_m path_s;
	getDirectory(path, filedir);
	for (string p : filedir)
		cout << p << endl;
	path_s=scanfile(filedir);
	countsimil(path_s);
}
