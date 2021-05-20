#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include<iomanip>
#include <fstream>


using namespace std;
struct Input;
Input read_input(istream& in);
void find_minmax(const vector<double>& numbers, double& min, double& max);
vector<double> input_numbers(istream& in, size_t count);
vector<double> make_histogram(const vector<double>& numbers, size_t bin_count);
void show_histogram_text(vector<double>bins);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void show_histogram_svg(const vector<double>& bins);

