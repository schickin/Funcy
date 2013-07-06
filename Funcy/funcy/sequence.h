/*
 * sequence.h
 *
 *  Created on: 21.06.2013
 *      Author: schickin
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "funcy/impl/sequence_crtp.h"

#include <type_traits>

class SeqDefTag;

template <typename ElemType>
class SeqDef;

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

  // constructor from sequence definition with matching type
  Sequence(const SeqDef<ElemType>& rDef)
  {
    innerSeqPtr_ = const_cast<void*>(reinterpret_cast<const void*>(&rDef));
    emptyPtr_ = &emptySeqDefImpl<SeqDef<ElemType>>;
    cvalPtr_ = &cvalSeqDefImpl<SeqDef<ElemType>>;
    nextPtr_ = &nextSeqDefImpl<SeqDef<ElemType>>;
    deletePtr_ = nullptr;
    clonePtr_ = &cloneSeqDefImpl<SeqDef<ElemType>>;
  }

  // constructor from any other sequence
  template <typename SequenceImpl>
  Sequence(const SequenceImpl& rSeq)
  {
    setInnerSeq(new SequenceImpl(rSeq));
  }

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

  // assignment from any other sequence
  template <typename SequenceImpl>
  typename std::enable_if<
        std::is_base_of<SequenceTag, SequenceImpl>::value, Sequence>::type&
  operator=(const SequenceImpl& rSeq)
  {
    SequenceImpl* pSeq = new SequenceImpl(rSeq);

    if (deletePtr_) {
        deletePtr_(*this);
    }

    setInnerSeq(pSeq);

    return *this;
  }

  // assignment from sequence defining function
  template <typename SequenceDef>
  typename std::enable_if<
        std::is_base_of<SeqDefTag, SequenceDef>::value, Sequence>::type&
  operator=(const SequenceDef& rDef)
  {
    if (deletePtr_) {
        deletePtr_(*this);
    }

    innerSeqPtr_ = const_cast<void*>(reinterpret_cast<const void*>(&rDef));
    emptyPtr_ = &emptySeqDefImpl<SequenceDef>;
    cvalPtr_ = &cvalSeqDefImpl<SequenceDef>;
    nextPtr_ = &nextSeqDefImpl<SequenceDef>;
    deletePtr_ = nullptr;
    clonePtr_ = &cloneSeqDefImpl<SequenceDef>;

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

  void reset()
  {
    if (deletePtr_) {
        deletePtr_(*this);
    }

    innerSeqPtr_ = nullptr;
    emptyPtr_ = nullptr;
    cvalPtr_ = nullptr;
    nextPtr_ = nullptr;
    deletePtr_ = nullptr;
    clonePtr_ = nullptr;
  }

  void* getInnerSeqPtr()
  {
    return innerSeqPtr_;
  }

  const void* getInnerSeqPtr() const
  {
    return innerSeqPtr_;
  }

private:

  template <typename SequenceImpl>
  static bool emptySeqImpl(const Sequence& rSeq)
  {
    return reinterpret_cast<const SequenceImpl*>(rSeq.getInnerSeqPtr())->empty();
  }

  template <typename SequenceDef>
  static bool emptySeqDefImpl(const Sequence& rSeq)
  {
    const_cast<Sequence&>(rSeq) =
        reinterpret_cast<const SequenceDef*>(rSeq.innerSeqPtr_)->newInstance();
    return rSeq.empty();
  }

  template <typename SequenceImpl>
  static Elem cvalSeqImpl(const Sequence& rSeq)
  {
    return reinterpret_cast<const SequenceImpl*>(rSeq.getInnerSeqPtr())->cval();
  }

  template <typename SequenceDef>
  static Elem cvalSeqDefImpl(const Sequence& rSeq)
  {
    const_cast<Sequence&>(rSeq) =
        reinterpret_cast<const SequenceDef*>(rSeq.innerSeqPtr_)->newInstance();
    return rSeq.cval();
  }

  template <typename SequenceImpl>
  static void nextSeqImpl(Sequence& rSeq)
  {
    reinterpret_cast<SequenceImpl*>(rSeq.getInnerSeqPtr())->next();
  }

  template <typename SequenceDef>
  static void nextSeqDefImpl(Sequence& rSeq)
  {
    rSeq = reinterpret_cast<const SequenceDef*>(rSeq.innerSeqPtr_)->newInstance();
    rSeq.next();
  }

  template <typename SequenceImpl>
  static void deleteSeqImpl(Sequence& rSeq)
  {
    delete reinterpret_cast<SequenceImpl*>(rSeq.getInnerSeqPtr());
  }

  template <typename SequenceImpl>
  static void* cloneSeqImpl(const Sequence& rSeq)
  {
    if (rSeq.getInnerSeqPtr()) {
      return new SequenceImpl(*reinterpret_cast<const SequenceImpl*>(rSeq.getInnerSeqPtr()));
    }
    else {
      return nullptr;
    }
  }

  template <typename SequenceDef>
  static void* cloneSeqDefImpl(const Sequence& rSeq)
  {
    return rSeq.innerSeqPtr_;
  }

  template <typename SequenceImpl>
  void setInnerSeq(SequenceImpl* innerSeqPtr)
  {
    innerSeqPtr_ = innerSeqPtr;
    emptyPtr_ = &emptySeqImpl<SequenceImpl>;
    cvalPtr_ = &cvalSeqImpl<SequenceImpl>;
    nextPtr_ = &nextSeqImpl<SequenceImpl>;
    deletePtr_ = &deleteSeqImpl<SequenceImpl>;
    clonePtr_ = &cloneSeqImpl<SequenceImpl>;
  }

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
};


#endif /* SEQUENCE_H_ */
