#ifndef dMemorManHolderDummyHxx
#define dMemorManHolderDummyHxx
//headers
#include "fOwner.hxx"
#include <dLibAsist.dir/fIpop.hxx>
//content
namespace nMemorMan
{
namespace nHolder
{
//typedef
/* tDummy
 * it does not do anything with given pointers
 * it can only log memory sizes
 * maybe needed in case if we don't wanna mess with memory directly
 * > but keep track of it
 * > for example: having a smart pointer bound to the stack address
 * so this is just a placeholder
 */
dTypeDefIline typedef class tDummy final: public tOwner
{
public://typedef

	using tThis = tDummy;
	using tBase = tOwner;

public://codetor

	tDummy(): vAlig(cAligM)
	{
	}

	tDummy(const tThis &rCopy) = delete;
	tDummy(tThis &&rCopy)	   = delete;

	virtual ~tDummy()
	{
	}

public://getters

	aUseReturned("get the maximal size in bytes used so far"
	) dFuncDefIline auto fGetSizeAtMax() const
	{
		return this->vSizeAtMax;
	}//fGetSizeAtMax
	aUseReturned("get the maximal size in bytes used so far"
	) dFuncDefIline auto fGetSizeInUse() const
	{
		return this->vSizeInUse;
	}//fGetSizeInUse

public://vetters

	aUseReturned("has byte size in use"
	) dFuncDefIline bool fVetSizeInUse() const
	{
		return this->vSizeInUse > 0;
	}//fVetSizeInUse
	aUseReturned("has byte size in use more than or equal to the given size"
	) dFuncDefIline bool fVetSizeInUse(tSizeM vSize) const
	{
		return this->vSizeInUse >= vSize;
	}//fVetSizeInUse
	aUseReturned("has byte size at max"
	) dFuncDefIline bool fVetSizeAtMax() const
	{
		return this->vSizeAtMax > 0;
	}//fVetSizeAtMax
	aUseReturned("has byte size at max more than or equal to the given size"
	) dFuncDefIline bool fVetSizeAtMax(tSizeM vSize) const
	{
		return this->vSizeAtMax >= vSize;
	}//fVetSizeAtMax

public://actions

	aHasReturned("update internal information about allocated memory"
	) dFuncDefIline virtual bool fGiveRaw(tDataM &rD, tSizeM vS, tAligM vA) override
	{
#if defined(dMemorManSizeVet)
		fEfnot(vS, return 0, "cannot give {0} bytes!", vS);
#endif//dMemorManSizeVet
		vA = nLibAsist::nNums::fGetAliUpper(vA, this->vAlig);
		vS = nLibAsist::nNums::fGetAliUpper(vS, vA);
#if defined(dMemorManSizeVet)
		this->vSizeInUse += vS;
		this->vSizeAtMax = nLibAsist::nNums::
			fGetMax(this->vSizeAtMax, this->vSizeInUse);
#endif//ifd(dMemorManSizeVet)
		return 1;
	}//fGiveRaw
	aHasReturned("update internal information about allocated memory"
	) dFuncDefIline virtual bool fTakeRaw(tDataM &rD, tSizeM vS, tAligM vA) override
	{
#if defined(dMemorManSizeVet)
		fEfnot(vS, return 0, "cannot take {0} bytes!", vS);
#endif//ifd(dMemorManSizeVet)
		vA = nLibAsist::nNums::fGetAliUpper(vA, this->vAlig);
		vS = nLibAsist::nNums::fGetAliUpper(vS, vA);
#if defined(dMemorManSizeVet)
		this->vSizeInUse -= vSize;
#endif//ifd(dMemorManSizeVet)
		return 1;
	}//fTakeRaw

	aMaybeUnused("output contents into stderr"
	) dFuncDefIline void fPrint() const
	{
		fElog(
			"[memo::dummy->elog]=("
			"[SizeInUse]=(%zu)[SizeAtMax]=(%zu)"
			"[vAlig]=(%zu))",
			this->vSizeInUse,
			this->vSizeAtMax,
			this->vAlig
		);
	}//fPrint

public://symbols

	aUseReturned("upcast this instance to reference of the base class"
	) dFuncDefIline
	operator tBase &()
	{
		return static_cast<tBase &>(*this);
	}//operator tBase&
	aUseReturned("upcast this instance to pointer of the base class"
	) dFuncDefIline
	operator tBase *()
	{
		return static_cast<tBase *>(this);
	}//operator tBase*

private://datadef

	tSizeM vSizeInUse;//current used space
	tSizeM vSizeAtMax;//maximal used space
	tSizeM vAlig;

public://consdef

	dDataDefInter dDataDefConst tAligM cAligM = sizeof(tDataM);

} tDummy;
}//namespace nHolder
}//namespace nMemorMan
#endif//dMemorManHolderDummyHxx
