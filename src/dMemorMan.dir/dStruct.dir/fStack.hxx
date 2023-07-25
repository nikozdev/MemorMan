#ifndef dMemorManHolderStackHxx
#define dMemorManHolderStackHxx
//headers
#include "fOwner.hxx"
#include "fHeapy.hxx"
//content
namespace nMemorMan
{
namespace nHolder
{
//typedef
/* tStack
 * stack allocator
 */
dTypeDefIline typedef class tStack final: public tOwner
{
public://typedef

	using tThis = tStack;
	using tBase = tOwner;

public://codetor

	tStack(tSizeM vSize = 0, tBase *pOwner = 0):
	{
	}

	tStack(const tThis &rCopy) = delete;
	tStack(tThis &&rCopy)	   = delete;

	~tStack();

public://actions

	[[]] virtual v1bit_t
	give(mdata_t &mdata, tSizeM msize, tSizeM malig) override;
	[[]] virtual v1bit_t
	take(mdata_t &mdata, tSizeM msize, tSizeM malig) override;
	[[maybe_unused]]
	inline void elog(void) const
	{
		_ELOG(
			"[memo::stack->elog]=("
			"[owner]=({:p})"
			"[mdata_head]=({:p})[mdata_tail]=({:p})[mdata_back]=({:p})"
			"[msize_full]=({:d})[msize_used]=({:d})[msize_umax]=({:d})"
			"[malig]=({:d}))",
			static_cast<mdata_t>(this->owner),
			this->mdata_head,
			this->mdata_tail,
			this->mdata_back,
			this->msize_full,
			this->msize_used,
			this->msize_umax,
			this->malig
		);
	}

protected://datadef

	owner_t *owner;
	udata_t	 mdata_head, mdata_tail, mdata_back;
	tSizeM	 msize_full, msize_used, msize_umax;
	tSizeM	 malig;

public://consdef

	static constexpr tSizeM MALIG = nums::get_aligned<mdata_t>();
	static constexpr tSizeM MSIZE = 1 << 20;

} tStack;

}//namespace nHolder
}//namespace nMemorMan
#endif//dMemorManHolderStackHxx
