#ifndef dMemorManMainCxx
#define dMemorManMainCxx
#include <dMemorMan.dir/fHead.hxx>
//content
#ifdef dMemorManMakeExe
//actions
int main(int vArgC, const char **vArgV)
{
	return nMemorMan::nMain::fMain(vArgC, vArgV);
}//main
#endif//dMemorManMakeExe
#endif//dMemorManMainCxx
