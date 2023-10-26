//
//  kingTest.hpp
//  
//
//  Created by Jacob on 9/28/23.
//

#ifndef kingTest_hpp
#define kingTest_hpp

#include <stdio.h>
class KingTest {
public:
    void testKingNormalHorizontalMove() {}
    void testKingNormalVerticalMove() {}
    void testKingNormalDiagonalMove() {}
    void testKingDoubleDiagonalMove() {}
    void testKingDoubleHorizontalMove() {}
    void testKingDoubleVerticalMove() {}
    void testKingHorizontalAttack() {}
    void testKingDiagonalAttack() {}
    void testKingVerticalAttack() {}
    void testKingAttackOwnColor() {}
    void testKingMoveIntoCheck() {}
    void testKingMoveOutOfCheck() {}
    void testKingFailureToMoveOutOfCheck() {}
    void testKingCastle() {}
    void testKingCastleFailure() {}
}

#include "kingTest.hpp"


//Test 1 - One Space Horizontal Move
King test1King = King(Color::BLACK, Point(4,0));
assert (test1King.move(Point(5,1)));
delete[] test1King;

//Test 2 - One Space Vertical Move
King test2King = King(Color::WHITE,Point(4,7));
assert(test2King.move(Point(3,7)));
delete[] test2King;

//Test 3 - One Space Diagonal Move
King test3King = King(Color::BLACK,Point(4,0));
assert(test3King.move(Point(3,1)));
delete[] test3King;

//Test 4 - Two Space Diagonal Move
King test4King = King(Color::WHITE,Point(3,6));
assert(!test4King.move(Point(1,4)));
delete[] test4King;

//Test 5 - Two Space Horizontal Move
King test5King = King(Color::BLACK, Point(6,3));
assert(!test5King.move(Point(4,3)));
delete[] test5King;

//Test 6 - Two Space Vertical Move
King test6King = King(Color::WHITE,Point(5,3));
assert(!test6King.move(Point(5,1)));
delete[] test6King;

//Test 7 - Horizontal Attack Move
King test7King = King(Color::BLACK,Point(3,3));
Pawn test7Pawn = Pawn(Color::WHITE,Point(2,3));
assert(test7King.move(Point(2,3)));
delete[] test7King;
delete[] test7Pawn;

//Test 8 - Diagonal Attack Move
King test8King = King(Color::WHITE,Point(5,4));
Pawn test8Pawn = Pawn(Color::BLACK,Point(4,3));
assert(test8King.move(Point(4,3)));
delete[] test8King;
delete[] test8Pawn;

//Test 9 - Vertical Attack Move
King test9King = King(Color::BLACK,Point(5,3));
Pawn test9Pawn = Pawn(Color::WHITE,Point(5,4));
assert(test9King.move(Point(5,4)));
delete[] test9King;
delete[] test9Pawn;

//Test 10 - Attacking Own Color
King test10King = King(Color::BLACK,Point(3,3));
Pawn test10Pawn = Pawn(Color::BLACK,Point(2,3));
assert(!test10King.move(Point(2,3)));
delete[] test10King;
delete[] test10Pawn;

//Test 11 - Moving Into Check
King test11King = King(Color::WHITE,Point(4,7))
Bishop test11Bishop = Bishop(Color::BLACK,Point(7,3));
assert(!test11King.move(Point(4,6)));
delete[] test11King;
delete[] test11Bishop;

//Test 12 - Moving Out of Check
King test12King = King(Color::BLACK,Point(6,7));
Queen test12Queen = Queen(Color::WHITE,Point(6,2));
assert(test12King.move(Point(5,7)));
delete[] test12King;
delete[] test12Queen;

//Test 13 - Failure to Move Out of Check
King test13King = King(Color::WHITE,Point(1,7));
Rook test13Rook = Rook(Color::BLACK,Point(1,1));
Knight test13Knight = Knight(Color::BLACK,Point(3,5));
assert(!test13King.move(Point(2,7)));
delete[] test13King;
delete[] test13Rook;
delete[] test13Knight;

//Test 14 - Castling
King test14King = King(Color::BLACK, Point(4,0));
Rook test14Rook = Rook(Color::BLACK,Point(7,0));
assert(test14King.move(Point6,0));
delete[] test14King;
delete[] test14Rook;

//Test 15 - Failed Castle Attempt
King test15King = King(Color::WHITE,Point(4,6));
Rook test15Rook = Rook(Color::WHITE,Point(7,7));
test15King.move(4,7);
assert(!test15King.move(6,7));
delete[] test15King;
delete[] test15Rook;

}
#endif /* kingTest_hpp */
