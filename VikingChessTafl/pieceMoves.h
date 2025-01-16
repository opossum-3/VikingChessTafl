#define pieceMoves

bool isValidMoveFormat(const char* command, int boardSize);
bool tryMove(char player, const char* command, char** board, int boardSize, int moveCoords[4]);
void analyzeForTakenPieces(char player, char** board, int boardSize, int endRow, int endColumn, bool comment);
void movePiece(char** board, bool isKingFromCenterMove, int startRow, int startColumn, int endRow, int endColumn);