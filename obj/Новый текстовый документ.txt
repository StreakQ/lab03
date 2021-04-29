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
    double max = 0;
    find_minmax( array,min, max);
    assert(min != 0 );
    return;
}

int
main()
{
    test_positive();
    test_negative();
    test_equal();
    test_one_number();
   // empty_arr();
    return 0;
}
