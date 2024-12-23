#include <iostream>
#include "startBoard.h"
using namespace std;

void chooseBoardSize()
{
	int N = 0;
	while (true)
	{
		cout << "Board size NxN, input N (9, 11 or 13):" << endl;
		cin >> N;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (N == 9)
		{
			cout << "Board size 9x9 chosen" << endl;
			break;
		}
		if (N == 11)
		{
			cout << "Board size 11x11 chosen" << endl;
			break;
		}
		if (N == 13)
		{
			cout << "Board size 13x13 chosen" << endl;
			break;
		}
		cout << "Invalid input!" << endl;
	}
}