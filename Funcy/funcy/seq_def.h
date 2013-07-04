/*
 * seq_def.h
 *
 *  Created on: 03.07.2013
 *      Author: schickin
 */

#ifndef SEQ_DEF_H_
#define SEQ_DEF_H_

#include <functional>
#include <type_traits>

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

template <typename DefiningFunc>
SeqDef<typename std::result_of<DefiningFunc()>::type> def_seq(const DefiningFunc& defFunc)
{
  return SeqDef<typename std::result_of<DefiningFunc()>::type>(defFunc);
}

#endif /* SEQ_DEF_H_ */
