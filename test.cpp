#include "histogram.h"

#include <cassert>
#include <vector>

void
test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
    return;
}
void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
    return;
}
void test_equal()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
    return;
}
void test_one_number()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
    return;
}
void empty_arr()
{
    vector<double> array(5);
    array[0]= {};
    double min = 0;
    double new_min = min;
    double max = 0;
    find_minmax( array,min, max);
    assert(new_min !=min  );
    return;
}
void max_min()
{
    double max=1;
    double min = max;
    assert(max=min);
}
void bin_count_0()
{
    double bin_count=0;
    assert(bin_count == 0);
}
int
main()
{
    test_positive();
    test_negative();
    test_equal();
    test_one_number();
    //empty_arr();
    max_min();
    bin_count_0();
    return 0;
}
