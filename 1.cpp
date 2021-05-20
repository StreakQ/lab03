
#include "histogram.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
};

int main()
{
    
    size_t number_count;
    size_t bin_count;   
   Input data = read_input(cin);
    const auto bins = make_histogram(data.numbers, data.bin_count);

    show_histogram_svg(bins);
    return 1;
}

