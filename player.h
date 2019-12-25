#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "piece.h"
class Player
{
private:
    std::vector<Piece> pieces;
    int label;
public:
    Player(const std::vector<Piece>& nPieces,const int nLabel);

};

#endif // PLAYER_H
