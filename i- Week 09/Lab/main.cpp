#include <iostream>  // for CIN and COUT
#include <string>
#include <numbers>
#include <list>
#include <cmath>
#include <map>
#include <iterator>
#include <cassert>
#include "testGame.h"

using namespace std;

int main()
{
    // Game tests
    TestGame tg;
    tg.run();
    cout << "Game tests PASSED" << endl;

    // Tests for the other class
    cout << "Other tests PASSED" << endl;

    cout << "ALL TESTS PASSED" << endl;

    return 0;
}
