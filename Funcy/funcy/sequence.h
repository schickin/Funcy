/*
 * sequence.h
 *
 *  Created on: 21.06.2013
 *      Author: schickin
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "funcy/impl/sequence_crtp.h"


class Sequence : public SequenceCRTP<Sequence>
{
public:

  Sequence() :
    emptyPtr_(nullptr),
    cvalPtr_(nullptr),
    nextPtr_(nullptr)
  { }


  bool empty() const
  {
    assert(emptyPtr_);
    return emptyPtr_();
  }

  const Elem cval() const
  {
    assert(cvalPtr_);
    return cvalPtr_();
  }

  void next()
  {
    assert(nextPtr_);
    return nextPtr_();
  }

private:

  typedef bool (*EmptyFuncPtr)();
  typedef const Elem (*CValFuncPtr)();
  typedef void (*NextFuncPtr)();

  EmptyFuncPtr emptyPtr_;
  CValFuncPtr cvalPtr_;
  NextFuncPtr nextPtr_;

};


#endif /* SEQUENCE_H_ */
