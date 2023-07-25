#ifndef dMemorManHolderOwnerHxx
#define dMemorManHolderOwnerHxx
//headers
#include "fGiver.hxx"
#include "fTaker.hxx"
//content
namespace nMemorMan
{
namespace nHolder
{
dTypeDefIline typedef class tOwner
	: public tGiver
	, public tTaker
{
public://typedef

	using tThis = tOwner;

public://codetor

	tOwner() = default;

	tOwner(const tThis &copy) = delete;
	tOwner(tThis &&copy)	  = delete;

	virtual ~tOwner() = default;

public://acitons

	aHasReturned(
		"give address of raw memory block to caller"
		"using reference to pointer"
		"with required byte size and alignment"
	) virtual bool fGiveRaw(tDataM &rD, tSizeM vS, tAligM);
	aHasReturned(
		"take address of raw memory block from caller"
		"using reference to pointer"
		"with required byte size and alignment"
	) virtual bool fTakeRaw(tDataM &rD, tSizeM vS, tAligM);

	aHasReturned(
		"edit address of raw memory block"
		"using reference to pointer"
		"with input and output byte sizes with alignment"
	) dFuncDefConst bool fEditRaw(tDataM &rD, tSizeM vSI, tSizeM vSO, tAligM vA)
	{
		tDataM pDI = rD;
		rD		   = NULL;
		if(vSO > 0)
		{
			this->fGiveRaw(rD, vSO, vA);
		}
		if(vSI > 0)
		{
			if(rD)
			{
				vSI = ::nLibAsist::nNums::fGetAliUpper(vSI, vA);
				vSO = ::nLibAsist::nNums::fGetAliUpper(vSO, vA);
				std::memmove(rD, pDI, vSO);
			}
			this->fTakeRaw(pDI, vSI, vA);
		}
		return 1;
	}//fEditRaw
	template<typename tDataT>
	aHasReturned(
		"edit address of raw memory block"
		"using reference to pointer of any type"
		"with input and output byte sizes with alignment"
	) dFuncDefConst bool fEditRaw(tDataT *&rD, tSizeM vSI, tSizeM vSO, tAligM vA)
	{
		return this->fEditRaw(reinterpret_cast<tDataM &>(rD), vSI, vSO, vA);
	}//fEditRaw

	template<typename tDataT>
	aHasReturned(
		"edit address of an array of typed objects"
		"using reference to pointer of any type"
		"with input and output byte sizes with alignment"
	) dFuncDefConst bool fEditMul(tDataT *&rD, tCount vCI, tCount vCO)
	{
		dDataDefConst tSizeM cS = sizeof(tDataT);
		dDataDefConst tSizeM cA = alignof(tDataT);
		return this->fEditRaw(rD, vCI * cS, vCO * cS, cA);
	}//fEditMul

public://operats

	auto operator=(const tThis &rCopy) = delete;
	auto operator=(tThis &&rCopy)	   = delete;

} tOwner;
}//namespace nHolder
}//namespace nMemorMan
#endif//dMemorManHolderOwnerHxx
