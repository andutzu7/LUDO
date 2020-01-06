#ifndef SGAMEDATA_H
#define SGAMEDATA_H

//aici folosesc datele transmise de server
class SGameData
{
public:
    SGameData(int nrJuc,bool gO,int totalPl)
        :
     nrJucCurent(nrJuc),
     gameOver(gO),
     nrJucatori(totalPl)
       {};
    int nrJucCurent;
    bool gameOver;
    int nrJucatori;
};

#endif // SGAMEDATA_H
