#define pieceMoves

bool isValidMoveFormat(const char* command, int boardSize);
bool tryMove(char player, const char* command, char** board, int boardSize);