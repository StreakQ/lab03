#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include<iomanip>


using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);
vector<double> input_numbers(size_t count);
vector<double> make_histogram(const vector<double>& numbers, size_t bin_count);
void show_histogram_text(vector<double>bins);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
double fun_sign(const vector<double> numbers, size_t bin_count);
void show_histogram_svg(const vector<double>& bins, double val_sign);

