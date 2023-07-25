#ifndef dMemorManHolderHeapyHxx
#define dMemorManHolderHeapyHxx
//headers
#include "fOwner.hxx"
#include <dLibAsist.dir/fIpop.hxx>
//content
namespace nMemorMan
{
namespace nHolder
{
/* tHeapy
 * default heap allocator
 */
dTypeDefIline typedef class tHeapy final: public tOwner
{
public://typedef

	using tThis = tHeapy;
	using tBase = tOwner;

public://codetor

	dFuncDefConst tHeapy(): vSizeAtMax(0), vSizeInUse(0), vAlig(cAligM)
	{
	}

	dFuncDefConst tHeapy(const tThis &rCopy) = delete;
	dFuncDefConst tHeapy(tThis &&rCopy)		 = delete;

	dFuncDefConst virtual ~tHeapy()
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

	aHasReturned("has byte size in use"
	) dFuncDefIline bool fVetSizeInUse() const
	{
		return this->vSizeInUse > 0;
	}//fVetSizeInUse
	aHasReturned("has byte size in use more than or equal to the given size"
	) dFuncDefIline bool fVetSizeInUse(tSizeM vSize) const
	{
		return this->vSizeInUse >= vSize;
	}//fVetSizeInUse
	aHasReturned("has byte size at max"
	) dFuncDefIline bool fVetSizeAtMax() const
	{
		return this->vSizeAtMax > 0;
	}//fVetSizeAtMax
	aHasReturned("has byte size at max more than or equal to the given size"
	) dFuncDefIline bool fVetSizeAtMax(tSizeM vSize) const
	{
		return this->vSizeAtMax >= vSize;
	}//fVetSizeAtMax

public://actions

	aHasReturned("heap-allocate memory block and assign the given pointer"
	) dFuncDefIline virtual bool fGiveRaw(tDataM &rD, tSizeM vS, tAligM vA) override
	{
#if defined(dMemorManSizeVet)
		fEfnot(vS, return 0, "cannot give {0} bytes!", vS);
#endif//dMemorManSizeVet
		vA = ::nLibAsist::nNums::fGetAliUpper(vA, this->vAlig);
		vS = ::nLibAsist::nNums::fGetAliUpper(vS, vA);
#if dMemorManNewDelDef
		rD = std::malloc(vS);
#else
		rD = new tByteM[vS];
#endif
#if defined(dMemorManSizeSet)
		this->vSizeInUse += vS;
		this->vSizeAtMax = nLibAsist::nNums::
			fGetMax(this->vSizeAtMax, this->vSizeInUse);
#endif//ifd(dMemorManSizeSet)
		return 1;
	}//fGiveRaw
	aHasReturned("heap-allocate memory block from the given pointer"
	) dFuncDefIline virtual bool fTakeRaw(tDataM &rD, tSizeM vS, tAligM vA) override
	{
#if defined(dMemorManSizeVet)
		fEfnot(vS, return 0, "cannot take {0} bytes!", vS);
#endif//ifd(dMemorManSizeVet)
		vA = ::nLibAsist::nNums::fGetAliUpper(vA, this->vAlig);
		vS = ::nLibAsist::nNums::fGetAliUpper(vS, vAlig);
#if dMemorManNewDelDef
		std::free(rD);
#else
		delete[] rD;
#endif
#if defined(dMemorManSizeSet)
		this->vSizeInUse -= vSize;
#endif//ifd(dMemorManSizeSet)
		return 1;
	}//fTakeRaw
	aMaybeUnused("output contents into stderr"
	) dFuncDefIline void fPrint() const
	{
		fElog(
			"[memo::heapy->elog]=("
			"[SizeInUse]=({:d})[SizeAtMax]=({:d})"
			"[malig]=({:d}))",
			this->vSizeInUse,
			this->vSizeAtMax,
			this->vAlig
		);
	}//fPrint

public://operats

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

protected://datadef

	tSizeM vSizeInUse;//current used space
	tSizeM vSizeAtMax;//maximal used space

	tSizeM vAlig;//default memory alignment

public://consdef

	dDataDefInter dDataDefConst tAligM cAligM = sizeof(tDataM);

} tHeapy;
}//namespace nHolder
}//namespace nMemorMan
#endif//dMemorManHolderHeapyHxx
