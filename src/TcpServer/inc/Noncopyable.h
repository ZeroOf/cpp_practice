#ifndef __WIZ_NONCOPYABLE_H__
#define __WIZ_NONCOPYABLE_H__

namespace wiz
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}
	Noncopyable(const Noncopyable & rhs) = delete;
	Noncopyable & operator=(const Noncopyable &) = delete;
};

}
#endif

