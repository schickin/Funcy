/*
 * seq_def.h
 *
 *  Created on: 03.07.2013
 *      Author: schickin
 */

#ifndef SEQ_DEF_H_
#define SEQ_DEF_H_

#include <functional>

template <typename SeqType>
class SeqDef
{
public:
  typedef std::function<SeqType()> DefiningFunc;

  SeqDef() :
    defFunc_()
  { }

  SeqDef(const DefiningFunc& defFunc) :
    defFunc_(defFunc)
  { }

  SeqDef& operator=(const DefiningFunc& defFunc)
  {
    defFunc_ = defFunc;
    return *this;
  }

  SeqType newInstance() const
  { return defFunc_(); }

private:
  DefiningFunc defFunc_;
};

//! @todo add factory function def_seq(Callable)

#endif /* SEQ_DEF_H_ */
