﻿#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;
extern const size_t SCREEN_WIDTH = 80;
extern const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];

    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] < min)
        {
            min = numbers[i];
        }
        if (numbers[i] > max)
        {
            max = numbers[i];
        }
    }

    return;
}

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    double min, max;
    vector<size_t> bins(bin_count);
    find_minmax(numbers, min, max);
    int number_count = numbers.size();
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool flag = false;
        for (size_t j = 0; (j < bin_count - 1) && !flag; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (hi > numbers[i]))
            {
                bins[j]++;
                flag = true;
            }

        }
        if (!flag)
        {
            bins[bin_count - 1]++;
        }
    }

    return bins;
}
void show_histogram_text(vector<size_t>bins)
{
    int bin_count = bins.size();
    int max_count = 0;
    for (size_t i = 0; i < bin_count; i++)
    {
        size_t count = bins[i];

        if (count > max_count)
        {
            max_count = count;
        }
    }
    double height;
    if (max_count > MAX_ASTERISK)
    {
        height = (static_cast<double>(MAX_ASTERISK) / max_count);;
    }
    else
    {
        height = 1;
    }
    for (size_t i = 0; i < bin_count; i++)
    {
        size_t k = bins[i];
        cout << "   ";
        if (k < 100)
        {
            cout << " ";
        }
        if (k < 10)
        {
            cout << " ";
        }
        cout << k << "|";
        for (size_t j = 0; j < k * height; j++)
        {
            cout << "*";
        }
        cout << "\n";


    }
    return;
}
void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}
void
svg_text(double left, double baseline, string text)
{

    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height
        << "' stroke='" << stroke << "' fill='" << fill << "'/>";                                 //ПРАВИЛЬНЫЙ КОНЕЦ "'/>"
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    double scaling_factor,k;
    size_t bin_count = bins.size();
    size_t max_count = 0;
    const auto MAX_WIDTH = IMAGE_WIDTH - TEXT_WIDTH;
    for (size_t i = 0; i < bin_count; i++)
    {
        k = bins[i] * BLOCK_WIDTH;
        if (k > MAX_WIDTH)
        {
            max_count = k;
        }
    }
    for (size_t i = 0; i < bin_count; i++)
    {        
        if (max_count > MAX_WIDTH)
        {
            scaling_factor = (static_cast<double>(MAX_WIDTH) / max_count);
        }
        else
        {
            scaling_factor = 1;
        }
    }
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin * scaling_factor;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#ffeeee");
        top += BIN_HEIGHT;
    }
    svg_end();
}


int main()
{


    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    const auto numbers = input_numbers(number_count);
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);
    return 1;
}

