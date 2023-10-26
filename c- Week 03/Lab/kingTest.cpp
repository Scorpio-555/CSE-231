//
//  kingTest.cpp
//  
//
//  Created by Jacob on 9/28/23.
//

#include "kingTest.hpp"

class KingTest {
public:
    //Test 1 - One Space Horizontal Move
    void testKingNormalHorizontalMove() {
        King test1King = King(Color::BLACK, Point(4,0));
        bool result = test1King.move(Point(5,1)))
        assert (result);
        delete[] test1King;
        delete[] result;
    }
    
    //Test 2 - One Space Vertical Move
    void testKingNormalVerticalMove() {
        King test2King = King(Color::WHITE,Point(4,7));
        bool result = test2King.move(Point(3,7));
        assert(result);
        delete[] test2King;
        delete[] result;
    }
    
    //Test 3 - One Space Diagonal Move
    void testKingNormalDiagonalMove() {
        King test3King = King(Color::BLACK,Point(4,0));
        bool result = test3King.move(Point(3,1));
        assert(result);
        delete[] test3King;
        delete[] result;
    }
    
    //Test 4 - Two Space Diagonal Move
    void testKingDoubleDiagonalMove() {
        King test4King = King(Color::WHITE,Point(3,6));
        bool result = test4King.move(Point(1,4))
        assert(!result);
        delete[] test4King;
        delete[] result;
    }
    
    //Test 5 - Two Space Horizontal Move
    void testKingDoubleHorizontalMove() {
        King test5King = King(Color::BLACK, Point(6,3));
        bool result = test5King.move(Point(4,3))
        assert(!result);
        delete[] test5King;
        delete[] result;
    }
    
    //Test 6 - Two Space Vertical Move
    void testKingDoubleVerticalMove() {
        King test6King = King(Color::WHITE,Point(5,3));
        bool result = test6King.move(Point(5,1));
        assert(!result);
        delete[] test6King;
        delete[] result;
    }
    
    //Test 7 - Horizontal Attack Move
    void testKingHorizontalAttack() {
        King test7King = King(Color::BLACK,Point(3,3));
        Pawn test7Pawn = Pawn(Color::WHITE,Point(2,3));
        bool result = test7King.move(Point(2,3));
        assert(result);
        delete[] test7King;
        delete[] test7Pawn;
        delete[] result;
    }
   
    //Test 8 - Diagonal Attack Move
    void testKingDiagonalAttack() {
        King test8King = King(Color::WHITE,Point(5,4));
        Pawn test8Pawn = Pawn(Color::BLACK,Point(4,3));
        bool result = test8King.move(Point(4,3));
        assert(result);
        delete[] test8King;
        delete[] test8Pawn;
        delete[] result;
    }
    
    //Test 9 - Vertical Attack Move
    void testKingVerticalAttack() {
        King test9King = King(Color::BLACK,Point(5,3));
        Pawn test9Pawn = Pawn(Color::WHITE,Point(5,4));
        bool result = test9King.move(Point(5,4));
        assert(result);
        delete[] test9King;
        delete[] test9Pawn;
        delete[] result;
    }
    
    //Test 10 - Attacking Own Color
    void testKingAttackOwnColor() {
        King test10King = King(Color::BLACK,Point(3,3));
        Pawn test10Pawn = Pawn(Color::BLACK,Point(2,3));
        bool result = test10King.move(Point(2,3));
        assert(!result);
        delete[] test10King;
        delete[] test10Pawn;
        delete[] result;
    }
    
    //Test 11 - Moving Into Check
    void testKingMoveIntoCheck() {
        King test11King = King(Color::WHITE,Point(4,7))
        Bishop test11Bishop = Bishop(Color::BLACK,Point(7,3));
        bool result = test11King.move(Point(4,6));
        assert(!result);
        delete[] test11King;
        delete[] test11Bishop;
        delete[] result;
    }
    
    //Test 12 - Moving Out of Check
    void testKingMoveOutOfCheck() {
        King test12King = King(Color::BLACK,Point(6,7));
        Queen test12Queen = Queen(Color::WHITE,Point(6,2));
        bool result = test12King.move(Point(5,7));
        assert(result);
        delete[] test12King;
        delete[] test12Queen;
        delete[] result;
    }
    
    //Test 13 - Failure to Move Out of Check
    void testKingFailureToMoveOutOfCheck() {
        King test13King = King(Color::WHITE,Point(1,7));
        Rook test13Rook = Rook(Color::BLACK,Point(1,1));
        Knight test13Knight = Knight(Color::BLACK,Point(3,5));
        bool result = test13King.move(Point(2,7));
        assert(!result);
        delete[] test13King;
        delete[] test13Rook;
        delete[] test13Knight;
        delete[] result;
    }
    
    //Test 14 - Castling
    void testKingCastle() {
        King test14King = King(Color::BLACK, Point(4,0));
        Rook test14Rook = Rook(Color::BLACK,Point(7,0));
        bool result = test14King.move(Point(6,0));
        assert(result);
        delete[] test14King;
        delete[] test14Rook;
        delete[] result;
    }
    
    //Test 15 - Failed Castle Attempt
    void testKingCastleFailure() {
        King test15King = King(Color::WHITE,Point(4,6));
        Rook test15Rook = Rook(Color::WHITE,Point(7,7));
        test15King.move(4,7);
        bool result = test15King.move(Point(6,7));
        assert(!result);
        delete[] test15King;
        delete[] test15Rook;
        delete[] result;
    }
    
}

