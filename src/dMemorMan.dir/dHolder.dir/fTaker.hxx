#ifndef dMemorManHolderTakerHxx
#define dMemorManHolderTakerHxx
//headers
#include <dLibAsist.dir/fNums.hxx>
#include <dLibAsist.dir/fMemo.hxx>
//content
namespace nMemorMan
{
namespace nHolder
{
//typedef
dTypeDefIline typedef class tTaker
{
public://typedef

	using tThis = tTaker;

	using tDataM = ::nLibAsist::nMemo::tDataM;
	using tByteM = ::nLibAsist::nMemo::tByteM;
	using tSizeM = ::nLibAsist::nNums::tSizeM;
	using tAligM = ::nLibAsist::nNums::tSizeM;
	using tCount = ::nLibAsist::nNums::tCount;

public://codetor

	tTaker() = default;

	tTaker(const tThis &rCopy) = delete;
	tTaker(tThis &&rCopy)	   = delete;

	virtual ~tTaker() = default;

public://actions

	aHasReturned(
		"take address of raw memory block from caller"
		"using reference to pointer, required byte size and alignment"
	) virtual bool fTakeRaw(tDataM &rD, tSizeM vS, tAligM);
	template<typename tDataT>
	aHasReturned(
		"take address of raw memory block from caller"
		"using reference to pointer, required byte size and alignment"
	) dFuncDefConst bool fTakeRaw(tDataT *&rD, tSizeM vS, tAligM vA)
	{
		return this->fTakeRaw(reinterpret_cast<tDataM &>(rD), vS, vA);
	}//fTakeRaw
	template<typename tDataT>
	aHasReturned(
		"take address of memory block from caller"
		"using reference to pointer"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fTakeOne(tDataT &rD)
	{
		dDataDefConst tSizeM cS = sizeof(tDataT);
		dDataDefConst tAligM cA = alignof(tDataT);
		return this->fTakeRaw(reinterpret_cast<tDataM &>(rD), cS, cA);
	}//fTakeOne
	template<typename tDataT>
	aHasReturned(
		"take address of memory block from caller"
		"using reference to pointer and required count"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fTakeMul(tDataT &rD, tCount vC)
	{
		dDataDefConst tSizeM cS = sizeof(tDataT);
		dDataDefConst tAligM cA = alignof(tDataT);
		return this->fTakeRaw(reinterpret_cast<tDataM &>(rD), cS * vC, cA);
	}//fTakeMul

	template<typename tDataT, typename... tArgsT>
	aHasReturned(
		"take address of memory block with constructed object from caller"
		"using reference to pointer and construction arguments"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fKillOne(tDataT &rD)
	{
		rD = this->fTakeMul<tDataT>(1);
		rD->~tDataT();
		return rD;
	}//fKillOne
	template<typename tDataT, typename... tArgsT>
	aHasReturned(
		"take address of memory block with constructed object from caller"
		"using reference to pointer and construction arguments"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fKillMul(tDataT *&rD, tCount vC)
	{
		this->fTakeMul<tDataT>(rD, vC);
		tDataT *pH = rD, *pI = pH, *pT = pI + vC;
		while(pI < pT)
		{
			(pI++)->~tDataT();
		}
		return rD;
	}//fKillMul

public://operats

	auto operator=(const tThis &rCopy) = delete;
	auto operator=(tThis &&rCopy)	   = delete;

} fTaker;
}//namespace nHolder
}//namespace nMemorMan
#endif//dMemorManHolderTakerHxx
