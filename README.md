# LUDO
Ludo is a very popular board game where the first player to put all his pieces in his base wins.
## Tools used
Qt creator for the graphic interface and Code::Blocks for the game server

## Implementation
I used the linux os for easier process manipulation. I created the game interface and all the game logic in QT framework using C++ and connected the game process with a TCP multi-threaded server that uses C for thread and process manipulation using QTCPSocket,a class included in the QT Framework. The server is concurrent, the client requests a dice value from the server everytime it wants to continue the game and make a new move. When the game is over, the client disconnects from the server.
