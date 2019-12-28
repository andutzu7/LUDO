#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "piece.h"
class Player
{
private:
    std::vector<Piece> pieces;
    int label;
    int nrOfPiecesHome=0;
public:
    Player(const std::vector<Piece>& nPieces,const int nLabel);
    int GetNrPiecesHome() const;
};

#endif // PLAYER_H
