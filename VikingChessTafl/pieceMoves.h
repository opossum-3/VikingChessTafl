#define pieceMoves

bool isValidMoveFormat(const char* command, int boardSize);
bool tryMove(char player, const char* command, char** board, int boardSize);
bool isKingSurrounded(char** board, int boardSize);
bool hasKingEscaped(char** board, int boardSize);