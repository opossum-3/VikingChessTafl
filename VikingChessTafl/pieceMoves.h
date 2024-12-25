#define pieceMoves

bool isValidMoveFormat(const char* command, int boardSize);
bool tryMove(char player, const char* command, char** board, int boardSize);

bool isMovingThroughPieces(int startRow, int endRow, int startColumn, int endColumn, char** board, bool& retFlag);
