
#include "histogram.h"



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
vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in)
{
    Input data;
    size_t number_count;


        cerr << "Enter number count: ";
        in >> number_count;
        cerr << "Enter numbers: ";
        cerr << "Enter bin count ";
        in >> data.bin_count;


    data.numbers = input_numbers(in, number_count);

    return data;
}

vector<double> make_histogram(Input data)
{

    double min, max;
    vector<double> bins(data.bin_count);
    find_minmax(data.numbers, min, max);
    size_t number_count = data.numbers.size();
    double bin_size = (max - min) / data.bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool flag = false;
        for (size_t j = 0; (j < data.bin_count - 1) && !flag; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= data.numbers[i]) && (hi > data.numbers[i]))
            {
                bins[j]++;
                flag = true;
            }

        }
        if (!flag)
        {
            bins[data.bin_count - 1]++;
        }
    }

    return bins;
}

void show_histogram_text(vector<size_t>bins)
{
   size_t bin_count = bins.size();
    size_t max_count = 0;
    for (size_t i = 0; i < bin_count; i++)
    {
        size_t count = bins[i];

        if (count > max_count)
        {
            max_count = count;
        }
    }
    double height;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
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
void svg_rect(double x, double y, double width, double height, string stroke , string fill )
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height
        << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void show_histogram_svg( const vector<double>& bins)
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
    double scaling_factor=0;
    size_t bin_count = bins.size();
    size_t max_count = 0,k;
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
