#include<crtdbg.h>
#include<Windows.h>
#include"Test.h"
#include"UI.h"
using namespace std;

#ifdef _DEBUG
#include "debugNew.h"
#endif

int main() {
	{
		Test t{};
		t.testAll();
		Repository* repo = nullptr;
		WatchList* wl = nullptr;
		Service s{ repo };
		UI u{ s , wl};
		u.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}