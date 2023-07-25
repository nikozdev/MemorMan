#ifndef dMemorManHolderGiverHxx
#define dMemorManHolderGiverHxx
//headers
#include <dLibAsist.dir/fNums.hxx>
#include <dLibAsist.dir/fMemo.hxx>
//content
namespace nMemorMan
{
namespace nHolder
{
//typedef
dTypeDefIline typedef class tGiver
{
public://typedef

	using tThis = tGiver;

	using tDataM = ::nLibAsist::nMemo::tDataM;
	using tByteM = ::nLibAsist::nMemo::tByteM;
	using tSizeM = ::nLibAsist::nNums::tSizeM;
	using tAligM = ::nLibAsist::nNums::tSizeM;
	using tCount = ::nLibAsist::nNums::tCount;

public://codetor

	tGiver() = default;

	tGiver(const tThis &rCopy) = delete;
	tGiver(tThis &&rCopy)	   = delete;

	virtual ~tGiver() = default;

public://actions

	aHasReturned(
		"give address of raw memory block to caller"
		"using reference to pointer, required byte size and alignment"
	) virtual bool fGiveRaw(tDataM &rD, tSizeM vS, tAligM);
	template<typename tDataT>
	aHasReturned(
		"give address of raw memory block to caller"
		"using reference to pointer, required byte size and alignment"
	) dFuncDefConst bool fGiveRaw(tDataT *&rD, tSizeM vS, tAligM vA)
	{
		return this->fGiveRaw(reinterpret_cast<tDataM &>(rD), vS, vA);
	}//fGiveRaw
	template<typename tDataT>
	aHasReturned(
		"give address of memory block to caller"
		"using reference to pointer"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fGiveOne(tDataT &rD)
	{
		dDataDefConst tSizeM cS = sizeof(tDataT);
		dDataDefConst tAligM cA = alignof(tDataT);
		return this->fGiveRaw(reinterpret_cast<tDataM &>(rD), cS, cA);
	}//fGiveOne
	template<typename tDataT>
	aHasReturned(
		"give address of memory block to caller"
		"using reference to pointer and required count"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fGiveMul(tDataT &rD, tCount vC)
	{
		dDataDefConst tSizeM cS = sizeof(tDataT);
		dDataDefConst tAligM cA = alignof(tDataT);
		return this->fGiveRaw(reinterpret_cast<tDataM &>(rD), cS * vC, cA);
	}//fGiveMul

	template<typename tDataT, typename... tArgpT>
	aHasReturned(
		"give address of memory block with constructed object to caller"
		"using reference to pointer and construction arguments"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fMakeOne(tDataT &rD, tArgpT &&...vP)
	{
		rD = this->fGiveMul<tDataT>(1);
		new (rD) tDataT(std::forward<tArgpT>(vP)...);
		return rD;
	}//fMakeOne
	template<typename tDataT, typename... tArgpT>
	aHasReturned(
		"give address of memory block with constructed object to caller"
		"using reference to pointer and construction arguments"
		"with byte size and alignment of underlying pointer type"
	) dFuncDefConst bool fMakeMul(tDataT *&rD, tCount vC, tArgpT &&...vP)
	{
		this->fGiveMul<tDataT>(rD, vC);
		tDataT *pH = rD, *pI = pH, *pT = pI + vC;
		while(pI < pT)
		{
			new (pI++) tDataT(std::forward<tArgpT>(vP)...);
		}
		return rD;
	}//fMakeMul

public://operats

	auto operator=(const tThis &rCopy) = delete;
	auto operator=(tThis &&rCopy)	   = delete;

} tGiver;
}//namespace nHolder
}//namespace nMemorMan
#endif//dMemorManHolderGiverHxx
