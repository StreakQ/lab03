
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

Input read_input(istream& in, bool prompt)
{

    Input data;
    if (prompt)
    {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    if(prompt)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if(prompt)
    {
        cerr <<"Enter bin count:";
    }
    in>>data.bin_count;

    return data;

}
Input download(const string& address)
{
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);
        if(res)
        {
            cerr<< curl_easy_strerror(res)<<"("<<res<<")"<<endl;
            exit(1);
        }

        curl_easy_cleanup(curl);
    }
    return read_input(buffer,false);
}
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
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
double fun_sign(Input data)
{
    double min, max;
    find_minmax(data.numbers, min, max);
    double bin_size = (max - min) / data.bin_count;
    bin_size = round(bin_size * 100)/100;
    return bin_size;
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
void svg_rect(double x, double y, double width, double height, string stroke, string fill )
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height
         << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void show_histogram_svg( const vector<double>& bins,double bin_size)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0,top_sign=0;
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

    double val_sign =bin_size;
    string str;
    int i = 0;
    for (size_t bin : bins)
    {
        string str= to_string(val_sign);
        str.erase(4,4);
        const double bin_width = BLOCK_WIDTH * bin * scaling_factor;
        svg_text(2*TEXT_LEFT, top + TEXT_BASELINE+ top_sign, to_string(bin));
        svg_rect(TEXT_WIDTH, top+ top_sign, bin_width, BIN_HEIGHT, "blue", "#ffeeee");
        if (i < bin_count - 1)
        {
            svg_text(0, top + TEXT_BASELINE + top_sign + BIN_HEIGHT, str);
            i++;
        }
        top += BIN_HEIGHT;
        top_sign += BIN_HEIGHT;
        val_sign = val_sign + bin_size;

    }

    svg_end();
}
