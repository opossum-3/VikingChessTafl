#define textFunctions

int stringLength(const char* text);
bool isPrefix(const char* prefix, const char* text);
bool areEqual(const char* text1, const char* text2);
void lower(char* text);
bool isDigit(char symbol);
bool isSmall(char symbol);
int indexOf(const char* text, char symbol);
int parseInt(const char* text);