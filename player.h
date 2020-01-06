#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "piece.h"
class Player
{
private:
    int label;
    bool show=false;
public:

    int nrOfPiecesHome=0;
    Player()=default;
    Player(const std::vector<Piece>& nPieces,const int nLabel);
    int GetNrPiecesHome() const;
    void ShowPlayer();
    void AddPiece( Piece& p);
    int nrOfMoves=0;

    std::vector<Piece> pieces;
};

#endif // PLAYER_H
