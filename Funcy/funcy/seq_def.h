/*
 * seq_def.h
 *
 *  Created on: 03.07.2013
 *      Author: schickin
 */

#ifndef SEQ_DEF_H_
#define SEQ_DEF_H_

#include <funcy/sequence.h>

#include <functional>
#include <type_traits>

class SeqDefTag
{ };

template <typename SeqType>
class TypedSeqDef : public SeqDefTag
{
public:
  typedef std::function<SeqType()> DefiningFunc;
  typedef typename std::result_of<DefiningFunc()>::type Elem;

  TypedSeqDef() :
    defFunc_()
  { }

  TypedSeqDef(const TypedSeqDef& other) :
    defFunc_(other.defFunc_)
  { }

  TypedSeqDef(const DefiningFunc& defFunc) :
    defFunc_(defFunc)
  { }

  TypedSeqDef& operator=(const DefiningFunc& defFunc)
  {
    defFunc_ = defFunc;
    return *this;
  }

  SeqType newInstance() const
  { return defFunc_(); }

private:
  DefiningFunc defFunc_;
};

template <typename ElemType>
class SeqDef : public SeqDefTag
{
public:
  typedef std::function<Sequence<ElemType>()> DefiningFunc;
  typedef ElemType Elem;

  SeqDef() :
    defFunc_()
  { }

  template <typename SeqType>
  SeqDef(const TypedSeqDef<SeqType>& seqDef) :
    defFunc_([=] { return Sequence<ElemType>(seqDef.newInstance()); })
  { }

  template <typename TypedDefiningFunc>
  SeqDef(const TypedDefiningFunc& defFunc) :
    defFunc_([=] { return Sequence<ElemType>(defFunc()); })
  { }

  template <typename SeqType>
  SeqDef& operator=(const TypedSeqDef<SeqType>& seqDef)
  {
    defFunc_ = [=] { return Sequence<ElemType>(seqDef.newInstance()); };
    return *this;
  }

  template <typename TypedDefiningFunc>
  SeqDef& operator=(const TypedDefiningFunc& defFunc)
  {
    defFunc_ = [=] { return Sequence<ElemType>(defFunc()); };
    return *this;
  }

  Sequence<ElemType> newInstance() const
  { return defFunc_(); }

  Sequence<ElemType> lazy() const
  { return Sequence<ElemType>(*this);  }

private:
  DefiningFunc defFunc_;
};

template <typename DefiningFunc>
TypedSeqDef<typename std::result_of<DefiningFunc()>::type> def_seq(const DefiningFunc& defFunc)
{
  return TypedSeqDef<typename std::result_of<DefiningFunc()>::type>(defFunc);
}

#endif /* SEQ_DEF_H_ */
