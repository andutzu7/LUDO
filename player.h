#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "piece.h"
class Player
{
private:
    int label;
    int nrOfPiecesHome=0;
    bool show=false;
public:
    Player()=default;
    Player(const std::vector<Piece>& nPieces,const int nLabel);
    int GetNrPiecesHome() const;
    void ShowPlayer();
    void AddPiece( Piece& p);


    std::vector<Piece> pieces;
};

#endif // PLAYER_H
