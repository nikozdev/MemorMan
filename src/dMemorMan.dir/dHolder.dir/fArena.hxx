#ifndef LIBASIST_MEMO_ARENA_HXX
#define LIBASIST_MEMO_ARENA_HXX 1

#include "../head.hxx"

/* headers */

#include "owner.hxx"
#include "mlink.hxx"

namespace libasist
{
namespace memo
{ /* typedef */

/* arena allocator */
class arena_t: public owner_t
{
public: /* typedef */

	using this_t = arena_t;

public: /* codetor */

	arena_t(msize_t msize = ZERO, owner_t *owner = NULL);
	arena_t(const this_t &copy) = delete;
	arena_t(this_t &&copy)		= delete;
	~arena_t();

public: /* getters */

	[[nodiscard]]
	static this_t *get()
	{
		return basic;
	}
	[[nodiscard]]
	inline msize_t get_msize_full() const
	{
		return this->msize_full;
	}
	[[nodiscard]]
	inline msize_t get_msize_umax() const
	{
		return this->msize_umax;
	}
	[[nodiscard]]
	inline msize_t get_msize_used() const
	{
		return this->msize_used;
	}
	[[nodiscard]]
	inline msize_t get_msize_free() const
	{
		return this->msize_full - this->msize_used;
	}

public: /* vetters */

	[[nodiscard]]
	inline v1bit_t vet_mdata(mdata_t mdata) const
	{
		return (mdata >= this->mdata_head) && (mdata < this->mdata_back);
	}
	[[nodiscard]]
	inline v1bit_t vet_msize_used() const
	{
		return this->msize_used > 0;
	}
	[[nodiscard]]
	inline v1bit_t vet_msize_used(msize_t msize) const
	{
		return this->msize_used >= msize;
	}
	[[nodiscard]]
	inline v1bit_t vet_msize_free() const
	{
		return this->msize_used < this->msize_full;
	}
	[[nodiscard]]
	inline v1bit_t vet_msize_free(msize_t msize) const
	{
		return this->get_msize_free() >= msize;
	}
	[[nodiscard]]
	inline v1bit_t vet_msize_umax(msize_t msize) const
	{
		return this->msize_umax >= msize;
	}

public: /* actions */

	[[]] virtual v1bit_t
	give(mdata_t &mdata, msize_t msize, msize_t malig) override;
	[[]] virtual v1bit_t
	take(mdata_t &mdata, msize_t msize, msize_t malig) override;
	[[maybe_unused]]
	inline void elog(void) const
	{
		_ELOG(
			"[memo::arena->elog]=("
			"[owner]=({:p})"
			"[mdata_head]=({:p})[mdata_tail]=({:p})[mdata_back]=({:p})"
			"[msize_full]=({:d})[msize_used]=({:d})[msize_umax]=({:d})"
			"[mlink]=({:p})"
			"[malig]=({:d}))",
			static_cast<mdata_t>(this->owner),
			this->mdata_head,
			this->mdata_tail,
			this->mdata_back,
			this->msize_full,
			this->msize_used,
			this->msize_umax,
			static_cast<mdata_t>(this->mlink),
			this->malig
		);
	}

protected: /* datadef */

	owner_t *owner;
	udata_t	 mdata_head, mdata_tail, mdata_back;
	msize_t	 msize_full, msize_used, msize_umax;
	mlink_t *mlink;
	msize_t	 malig;

public: /* consdef */

	static constexpr msize_t MALIG = nums::get_aligned<mlink_t>();
	static constexpr msize_t MSIZE = 1 << 20;

public: /* datadef */

	static this_t *basic;
}; /* arena_t */

}//namespace memo
}//namespace libasist

#endif /*LIBASIST_MEMO_ARENA_HXX*/
#ifndef LIBASIST_MEMO_ARENA_CXX
#define LIBASIST_MEMO_ARENA_CXX 1

#include "../head.hxx"

/* headers */

#include "arena.hxx"
#include "heapy.hxx"

/* content */

namespace libasist
{
namespace memo
{ /* codetor */

arena_t::arena_t(msize_t msize, owner_t *owner)
	: owner_t()
	, owner(owner ? owner : heapy_t::basic)
	, mdata_head(NULL)
	, mdata_tail(NULL)
	, mdata_back(NULL)
	, msize_full(msize)
	, msize_umax(ZERO)
	, msize_used(ZERO)
	, malig(MALIG)
	, mlink(NULL)
{
	this->msize_full = nums::get_aligned(this->msize_full, this->malig);
	static_cast<giver_t *>(this->owner)
		->give(this->mdata_head, this->msize_full, this->malig);
	this->mdata_back = this->mdata_head;
	this->mdata_tail = this->mdata_head + this->msize_full;
}
arena_t::~arena_t()
{
	static_cast<taker_t *>(this->owner)
		->take(this->mdata_head, this->msize_full, this->malig);
}

}//namespace memo
}//namespace libasist

namespace libasist
{
namespace memo
{ /* actions */

v1bit_t arena_t::give(mdata_t &mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
	_EFNOT(msize > ZERO, return FALSE, "cannot give %zu bytes!", msize);
#endif /*ifd(LIBASIST_MEMO_MSIZE_VET)*/
	mdata = NULL;
	malig = nums::get_aligned(malig, this->malig);
	msize = nums::get_aligned(msize, malig);
#if defined(LIBASIST_MEMO_MSIZE_VET)
	_EFNOT(
		this->vet_msize_free(msize),
		{
			this->elog();
			return FALSE;
		},
		"vet_msize_free error!"
	);
#endif /*ifd(LIBASIST_MEMO_MSIZE_VET)*/
	mlink_t *plink = NULL;
	mlink_t *nlink = this->mlink;
	while(nlink)
	{
		if(nlink->has_msize(msize))
		{
			if(plink)
			{
				plink->nlink = nlink->nlink;
			}
			else
			{
				this->mlink = nlink->nlink;
			}
			mdata = nlink;
#if defined(LIBASIST_MEMO_MSIZE_SET)
			this->msize_used += msize;
#endif /*ifd(LIBASIST_MEMO_MSIZE_SET)*/
			return TRUTH;
		}
		plink = nlink;
		nlink = nlink->nlink;
	}
	/* failed to get a free-list block, advance the back */
	mdata = this->mdata_back;
	this->mdata_back += msize;
#if defined(LIBASIST_MEMO_MSIZE_SET)
	this->msize_umax += msize;
	this->msize_used += msize;
#endif /*ifd(LIBASIST_MEMO_MSIZE_SET)*/
	return TRUTH;
}

v1bit_t arena_t::take(mdata_t &mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
	_EFNOT(mdata != NULL, return FALSE, "cannot deallocate by null!");
	_EFNOT(msize != ZERO, return FALSE, "cannot deallocate %zu bytes!", msize);
#endif /*ifd(LIBASIST_MEMO_MSIZE_VET)*/
#if defined(LIBASIST_MEMO_MDATA_VET)
	_EFNOT(
		this->vet_mdata(mdata), return FALSE, "mdata does not belong this arena!"
	);
#endif /*ifd(LIBASIST_MEMO_MDATA_VET)*/
	malig = nums::get_aligned(malig, this->malig);
	msize = nums::get_aligned(msize, malig);
#if defined(LIBASIST_MEMO_MSIZE_VET)
	_EFNOT(
		this->vet_msize_used(msize), return FALSE, "too many bytes to delete!"
	);
#endif /*ifd(LIBASIST_MEMO_MSIZE_VET)*/
	mlink_t *mlink = new (mdata) mlink_t();
	mlink->nlink   = this->mlink;
	mlink->msize   = msize;
	this->mlink	   = mlink;
	/* mdata_back and msize_umax should not be changed back! */
#if defined(LIBASIST_MEMO_MSIZE_SET)
	this->msize_used -= msize;
#endif /*ifd(LIBASIST_MEMO_MSIZE_SET)*/
	return TRUTH;
}

}//namespace memo
}//namespace libasist

namespace libasist
{
namespace memo
{ /* datadef */

arena_t *arena_t::basic = NULL;
;

}//namespace memo
}//namespace libasist

#endif /*LIBASIST_MEMO_ARENA_CXX*/
