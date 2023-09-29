//
//  king.hpp
//  
//
//  Created by Jacob on 9/28/23.
//

#ifndef king_hpp
#define king_hpp

#include <stdio.h>

#endif /* king_hpp */

class King : public Piece
{
public:
    King(Color color, Point point)
    bool getHasMoved {};
    void draw();
    array<Point> getAttackSquares();
    array<Point> getPossibleMoves();
    bool move(Point point);
    
private:
    bool hasMoved;
    
}
