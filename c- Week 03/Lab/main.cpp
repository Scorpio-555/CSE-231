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

    if (pawn.getColor() == Color::BLACK) {
        cout << "Color is black: true" << endl;
    }
    else {
        cout << "Color is black: false" << endl;
    }
    
    if (pawn.getName() == Name::PAWN) {
        cout << "Name is Pawn: true" << endl;
    }
    else {
        cout << "Name is Pawn: false" << endl;
    }

    if (pawn.isAlive() == true) {
        cout << "isAlive: true" << endl;
    }
    else {
        cout << "isAlive: false" << endl;
    }

    if (pawn.getPosition().getX() == 0 && pawn.getPosition().getY() == 0) {
        cout << "position is (0,0): true" << endl;
    }
    else {
        cout << "position is (0,0): false" << endl;
    }

    return 0;
}
