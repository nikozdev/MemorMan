#ifndef dMemorManMainHxx
#define dMemorManMainHxx
//headers
#include <dLibAsist.dir/fHead.hxx>
#include "dHolder.dir/fGiver.hxx"
#include "dHolder.dir/fTaker.hxx"
#include "dHolder.dir/fDummy.hxx"
#include "dHolder.dir/fHeapy.hxx"
//#include "dHolder.dir/fHeapy.hxx"
//#include "dHolder.dir/fStack.hxx"
//#include "dHolder.dir/fArena.hxx"
//#include "dHolder.dir/fPager.hxx"
//content
namespace nMemorMan
{
namespace nMain
{
using namespace ::nLibAsist;
using namespace ::nLibAsist::nMemo;
using namespace ::nLibAsist::nNums;
using namespace ::nLibAsist::nText;
using namespace ::nMemorMan::nHolder;
//using namespace ::nMemorMan::nHandle;
#ifdef dMemorManMakeExe
//actions
inline auto fMain(tIntSM vArgC, tCstr vArgV[])
{
#ifdef dMemorManTestExe
	fOlog("hello test");
#endif//dMemorManTestExe
	return 0;
}//fMain
#endif//dMemorManMakeExe
}//namespace nMain
}//namespace nMemorMan
#endif//dMemorManMainHxx
