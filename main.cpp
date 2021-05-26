#include <curl/curl.h>
#include "histogram.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
   const auto input = read_input(cin);
   const auto bins = make_histogram(input);
   show_histogram_svg(bins);
   return 1;
}

