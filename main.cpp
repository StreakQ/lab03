#include <curl/curl.h>
#include "histogram.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

int
main(int argc, char* argv[])
{
    Input input;
    if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin,false);
    }

    const auto bins = make_histogram(input);
    auto bin_size = fun_sign(input);
    show_histogram_svg(bins,bin_size);


    return 1;
}

