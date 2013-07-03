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
class Sequence : public SequenceCRTP<Sequence<ElemType>, ElemType>
{
public:
  typedef ElemType Elem;

  Sequence() :
    innerSeqPtr_(nullptr),
    emptyPtr_(nullptr),
    cvalPtr_(nullptr),
    nextPtr_(nullptr),
    deletePtr_(nullptr),
    clonePtr_(nullptr)
  { }

  Sequence(const Sequence& other) :
    innerSeqPtr_(other.clonePtr_(other)),
    emptyPtr_(other.emptyPtr_),
    cvalPtr_(other.cvalPtr_),
    nextPtr_(other.nextPtr_),
    deletePtr_(other.deletePtr_),
    clonePtr_(other.clonePtr_)
  { }

  // constructor from any other untyped sequence
  template <typename OtherElemType>
  Sequence(const Sequence<OtherElemType>& other) :
    innerSeqPtr_(other.clonePtr_(other)),
    emptyPtr_(other.emptyPtr_),
    cvalPtr_(other.cvalPtr_),
    nextPtr_(other.nextPtr_),
    deletePtr_(other.deletePtr_),
    clonePtr_(other.clonePtr_)
  { }

  // constructor from any other typed sequence
  template <typename SequenceImpl>
  Sequence(const SequenceImpl& rSeq) :
    innerSeqPtr_(new SequenceImpl(rSeq)),
    emptyPtr_(&emptyImpl<SequenceImpl>),
    cvalPtr_(&cvalImpl<SequenceImpl>),
    nextPtr_(&nextImpl<SequenceImpl>),
    deletePtr_(&deleteImpl<SequenceImpl>),
    clonePtr_(&cloneImpl<SequenceImpl>)
  { }

  ~Sequence()
  {
    if (deletePtr_) {
        deletePtr_(*this);
    }
  }

  Sequence& operator=(const Sequence& other)
  {
    if (this == &other) {
        return *this;
    }

    void* pSeq = other.clonePtr_(other);

    if (deletePtr_) {
        deletePtr_(*this);
    }

    innerSeqPtr_ = pSeq;
    emptyPtr_ = other.emptyPtr_;
    cvalPtr_ = other.cvalPtr_;
    nextPtr_ = other.nextPtr_;
    deletePtr_ = other.deletePtr_;
    clonePtr_ = other.clonePtr_;

    return *this;
  }

  // assignment from any other untyped sequence
  template <typename OtherElemType>
  Sequence& operator=(const Sequence<OtherElemType>& other)
  {
    void* pSeq = other.clonePtr_(other);

    if (deletePtr_) {
        deletePtr_(*this);
    }

    innerSeqPtr_ = pSeq;
    emptyPtr_ = other.emptyPtr_;
    cvalPtr_ = other.cvalPtr_;
    nextPtr_ = other.nextPtr_;
    deletePtr_ = other.deletePtr_;
    clonePtr_ = other.clonePtr_;

    return *this;
  }

  // assignment from any other typed sequence
  template <typename SequenceImpl>
  Sequence& operator=(const SequenceImpl& rSeq)
  {
    SequenceImpl* pSeq = new SequenceImpl(rSeq);

    if (deletePtr_) {
        deletePtr_(*this);
    }

    innerSeqPtr_ = pSeq;
    emptyPtr_ = &emptyImpl<SequenceImpl>;
    cvalPtr_ = &cvalImpl<SequenceImpl>;
    nextPtr_ = &nextImpl<SequenceImpl>;
    deletePtr_ = &deleteImpl<SequenceImpl>;
    clonePtr_ = &cloneImpl<SequenceImpl>;

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
  typedef void (*DeleteFuncPtr)(Sequence&);
  typedef void* (*CloneFuncPtr)(const Sequence&);

  void* innerSeqPtr_;
  EmptyFuncPtr emptyPtr_;
  CValFuncPtr cvalPtr_;
  NextFuncPtr nextPtr_;
  DeleteFuncPtr deletePtr_;
  CloneFuncPtr clonePtr_;

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

  template <typename SequenceImpl>
  static void deleteImpl(Sequence& rSeq)
  {
    delete reinterpret_cast<SequenceImpl*>(rSeq.innerSeqPtr_);
  }

  template <typename SequenceImpl>
  static void* cloneImpl(const Sequence& rSeq)
  {
    if (rSeq.innerSeqPtr_) {
      return new SequenceImpl(*reinterpret_cast<const SequenceImpl*>(rSeq.innerSeqPtr_));
    }
    else {
      return nullptr;
    }
  }

};


#endif /* SEQUENCE_H_ */
