#ifndef dMemorManMainCxx
#define dMemorManMainCxx
#include <dMemorMan.dir/fMain.hxx>
//content
#ifdef dMemorManMakeExe
//actions
int main(int vArgC, char *vArgV[])
{
#ifdef dMemorManTestExe
	if constexpr(1)
	{
		std::cout << "hello test" << std::endl;
	}
#endif//dMemorManTestExe
	return nMemorMan::fMain(vArgC, vArgV);
}//main
#endif//dMemorManMakeExe
#endif//dMemorManMainCxx
