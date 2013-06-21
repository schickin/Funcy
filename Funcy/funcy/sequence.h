/*
 * sequence.h
 *
 *  Created on: 21.06.2013
 *      Author: schickin
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "funcy/impl/sequence_crtp.h"

template <typename ElemType>
class Sequence : public SequenceCRTP<Sequence<ElemType> >
{
public:
  typedef ElemType Elem;

  Sequence() :
    innerSeqPtr_(nullptr),
    emptyPtr_(nullptr),
    cvalPtr_(nullptr),
    nextPtr_(nullptr)
  { }

  // default copy constructor

  // constructor from any other sequence
  template <typename SequenceImpl>
  Sequence(SequenceImpl& rSeq) :
    innerSeqPtr_(&rSeq),
    emptyPtr_(emptyImpl<SequenceImpl>),
    cvalPtr_(cvalImpl<SequenceImpl>),
    nextPtr_(nextImpl<SequenceImpl>)
  { }

  // default assignment operator

  // assignment from any other sequence
  template <typename SequenceImpl>
  Sequence& operator=(SequenceImpl& rSeq)
  {
    innerSeqPtr_ = &rSeq;
    emptyPtr_ = emptyImpl<SequenceImpl>;
    cvalPtr_ = cvalImpl<SequenceImpl>;
    nextPtr_ = nextImpl<SequenceImpl>;

    return *this;
  }

  bool empty() const
  {
    assert(emptyPtr_);
    return emptyPtr_(*this);
  }

  Elem cval() const
  {
    assert(cvalPtr_);
    return cvalPtr_(*this);
  }

  void next()
  {
    assert(nextPtr_);
    return nextPtr_(*this);
  }

  bool initialized() const
  {
    return innerSeqPtr_ != nullptr;
  }

private:

  typedef bool (*EmptyFuncPtr)(const Sequence&);
  typedef Elem (*CValFuncPtr)(const Sequence&);
  typedef void (*NextFuncPtr)(Sequence&);

  void* innerSeqPtr_;
  EmptyFuncPtr emptyPtr_;
  CValFuncPtr cvalPtr_;
  NextFuncPtr nextPtr_;

  template <typename SequenceImpl>
  static bool emptyImpl(const Sequence& rSeq)
  {
    return reinterpret_cast<SequenceImpl*>(rSeq.innerSeqPtr_)->empty();
  }

  template <typename SequenceImpl>
  static Elem cvalImpl(const Sequence& rSeq)
  {
    return reinterpret_cast<SequenceImpl*>(rSeq.innerSeqPtr_)->cval();
  }

  template <typename SequenceImpl>
  static void nextImpl(Sequence& rSeq)
  {
    return reinterpret_cast<SequenceImpl*>(rSeq.innerSeqPtr_)->next();
  }

};


#endif /* SEQUENCE_H_ */
