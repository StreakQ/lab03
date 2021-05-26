#include <curl/curl.h>
#include "histogram.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc >1 )
    {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return 0;
    }



    const auto input = read_input(cin);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    return 1;
}

