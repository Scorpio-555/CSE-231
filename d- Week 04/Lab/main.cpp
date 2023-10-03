#include <iostream>  // for CIN and COUT
#include <string>
#include <numbers>
#include <list>
#include <cmath>
#include <map>
#include <iterator>
#include <cassert>
#include "testKing.h"
#include "testGame.h"

using namespace std;

int main()
{
    // Game tets
    TestGame tg;
    tg.run();
    cout << "Game tests PASSED" << endl;

    // King tests
    TestKing tk;
    tk.run();
    cout << "King tests PASSED" << endl;

    cout << "ALL TESTS PASSED" << endl;

    return 0;
}
