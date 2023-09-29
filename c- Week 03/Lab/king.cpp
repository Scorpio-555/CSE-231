//
//  king.cpp
//  
//
//  Created by Jacob on 9/28/23.
//

#include "king.hpp"
King::King(Color color, Point point) {
    name = Name::KING;
    alive = true;
    hasMoved = false;
    this->color = color;
    this->position = point;
    
}

list<Point> King:: getAttackSquares() {
    return list<Point>;
}

list<Point> King::getPossibleMoves() {
    return list<Point>;
}

bool King::getHasMoved() {
    return hasMoved;
}

bool King::move(Point point) {
    list<Point> possibleMoves = getPossibleMoves();
    for (int i = 0; i < possibleMoves.size(); i++) {
        if (possibleMoves[i] == point) {
            return true;
        }
    }
    return false;
}

void King::draw() {}
