/*
 * range_seq.h
 *
 *  Created on: 16.07.2013
 *      Author: schickin
 */

#ifndef RANGE_SEQ_H_
#define RANGE_SEQ_H_

#include "funcy/impl/sequence_crtp.h"

#include <functional>

template <typename ElemType, template <typename> class Comparator = std::less>
class RangeSeq : public SequenceCRTP<RangeSeq<ElemType, Comparator>, ElemType>
{
public:
  typedef ElemType Elem;

  RangeSeq(const Elem& from, const Elem& to)
  :
    curr_(from),
    end_(to)
  { }

  bool empty() const
  {
    return !Comparator<ElemType>()(curr_, end_);
  }

  const Elem& cval() const
  {
    return curr_;
  }

  void next()
  {
    ++curr_;
  }

private:
  Elem curr_;
  const Elem end_;
};


template <typename ElemType>
RangeSeq<ElemType> make_range(const ElemType& begin, const ElemType& end)
{
  return RangeSeq<ElemType>(begin, end);
}

template <typename ElemType>
RangeSeq<ElemType, std::less_equal> make_range_closed(const ElemType& begin, const ElemType& end)
{
  return RangeSeq<ElemType, std::less_equal>(begin, end);
}

#endif /* RANGE_SEQ_H_ */
