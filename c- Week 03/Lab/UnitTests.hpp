//
//  UnitTests.hpp
//  
//
//  Created by Jacob on 9/30/23.
//

#ifndef UnitTests_hpp
#define UnitTests_hpp

#include <stdio.h>
class UnitTests {
    void testKing() {
        KingTest KingTester;
        KingTest::testKingNormalHorizontalMove();
        KingTest::testKingNormalVerticalMove();
        KingTest::testKingNormalDiagonalMove();
        KingTest::testKingDoubleDiagonalMove();
        KingTest::testKingDoubleHorizontalMove();
        KingTest::testKingDoubleVerticalMove();
        KingTester.testKingHorizontalAttack();
        KingTester.testKingDiagonalAttack();
        KingTester.testKingVerticalAttack();
        KingTester.testKingAttackOwnColor();
        KingTester.testKingMoveIntoCheck();
        KingTester.testKingMoveOutOfCheck();
        KingTester.testKingFailureToMoveOutOfCheck();
        KingTester.testKingCastle();
        KingTester.testKingCastleFailure();
    }
}

#endif /* UnitTests_hpp */
