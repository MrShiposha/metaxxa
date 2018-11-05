//
//  Created by Daniel Shiposha on 14/07/2018.
//

#ifndef METAXXA_TEST_H
#define METAXXA_TEST_H

#include <iostream>
#include <cmath>

#define TEST(condition, message) \
    do { if(!(condition)) { std::cout << message << std::endl; return false; } } while(0)

#define TEST_FRACTION_NEAR(first_value, second_value, epsilon, message) \
    do { if((std::abs(first_value - second_value)) >= (epsilon)) { std::cout << message << std::endl; return false; } } while(0);


struct TestMetaxxa
{
    virtual bool test() = 0;
};

#endif // METAXXA_TEST_H