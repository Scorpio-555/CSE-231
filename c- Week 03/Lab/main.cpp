#include <iostream>  // for CIN and COUT
#include <string>
#include <cmath>
#include <numbers>
#include<list>
#include <cmath>
#include <map>
#include <iterator>
#include <cassert>

#include "pawn.h"
#include "point.h"
#include "enum.h"

using namespace std;

int main()
{
    Pawn pawn(Color::BLACK, Point());

    cout << (pawn.getColor() == Color::BLACK) << endl;

    return 0;
}
