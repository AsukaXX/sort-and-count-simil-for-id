#include"id.h"

inline vector<double> readvector(const sum_m path_v) {
	vector<double> v;
	for (sum_m_e p : path_v) {
		//cout << p.first<<" "<<p.second << endl;
		v.push_back((double)p.second);
	}
	return v;
}

double cos_simil(const sum_m path_v1, const sum_m path_v2) {
	vector<double> v1, v2;
	double sum = 0.0, sum_v1 = 0.0, sum_v2 = 0.0;
	double c_result = 0.0;
	v1 = readvector(path_v1);
	v2 = readvector(path_v2);
	for (int i = 0; i < (int)v1.size(); i++) {
		sum += v1[i] * v2[i];
		sum_v1 += pow(v1[i], 2);
		sum_v2 += pow(v2[i], 2);
	}
	c_result = sum / (sqrt(sum_v1) * sqrt(sum_v2));
	return c_result;
}

double dist_simil(const sum_m path_v1, const sum_m path_v2) {
	vector<double> v1, v2;
	double sum = 0.0, d_result = 0.0;
	v1 = readvector(path_v1);
	v2 = readvector(path_v2);
	for (int i = 0; i < (int)v1.size(); i++) {
		sum += pow(v1[i] - v2[i], 2);
	}
	d_result = 1.0f / (1 + sqrt(sum));
	return d_result;
}

inline double max_d(const double l, const double r) {
	return l < r ? r : l;
}

double dist_2_simil(const sum_m path_v1, const sum_m path_v2) {
	vector<double> v1, v2;
	double dist = 0.0, dist1 = 0.0, dist2 = 0.0, sum = 0.0, sum1 = 0.0, sum2 = 0.0, d_2_result = 0.0;
	v1 = readvector(path_v1);
	v2 = readvector(path_v2);
	for (int i = 0; i < (int)v1.size(); i++) {
		sum += pow(v1[i] - v2[i], 2);
		sum1 += pow(v1[i] - 0, 2);
		sum2 += pow(v2[i] - 0, 2);
	}
	dist = sqrt(sum);
	dist1 = sqrt(sum1);
	dist2 = sqrt(sum2);
	d_2_result = (max_d(dist1, dist2) - dist) / max_d(dist1, dist2);
	return d_2_result;
}