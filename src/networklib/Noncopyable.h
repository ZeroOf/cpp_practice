
#ifndef __WILL_NONCOPYABLE_H__
#define __WILL_NONCOPYABLE_H__


namespace component
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}
	Noncopyable(const Noncopyable & rhs) = delete;
	Noncopyable & operator=(const Noncopyable &) = delete;
};

}//end of namespace net

#endif
