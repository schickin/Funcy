/*
 * concat.h
 *
 *  Created on: 21.06.2013
 *      Author: schickin
 */

#ifndef CONCAT_H_
#define CONCAT_H_

#include "funcy/impl/sequence_crtp.h"

//! @todo use variadic template

template <typename InnerSeq1, typename InnerSeq2>
class ConcatenatedSequence :
  public SequenceCRTP<ConcatenatedSequence<InnerSeq1, InnerSeq2>>
{
public:
  typedef typename InnerSeq1::Elem Elem;

  ConcatenatedSequence(InnerSeq1& inner1, InnerSeq2& inner2) :
    innerSeq1_(inner1),
    innerSeq2_(inner2)
  { }

  bool empty() const
  {
    return innerSeq1_.empty() && innerSeq2_.empty();
  }

  const Elem cval() const
  {
    return innerSeq1_.empty() ? innerSeq2_.cval() : innerSeq1_.cval();
  }

  void next()
  {
    if (innerSeq1_.empty()) {
      innerSeq2_.next();
    }
    else {
      innerSeq1_.next();
    }
  }

private:
  InnerSeq1& innerSeq1_;
  InnerSeq2& innerSeq2_;
};

template <typename SequenceImpl1, typename SequenceImpl2>
typename std::enable_if<std::is_base_of<SequenceTag, SequenceImpl1>::value
                        &&
                        std::is_base_of<SequenceTag, SequenceImpl2>::value
                        ,
                        ConcatenatedSequence<SequenceImpl1, SequenceImpl2>>::type
operator<<
(
  SequenceImpl1& seq1, SequenceImpl2& seq2
)
{
  return ConcatenatedSequence<SequenceImpl1, SequenceImpl2>(seq1, seq2);
}

#endif /* CONCAT_H_ */
