//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FILTER_H_
#define FILTER_H_

template <typename InnerSequence, typename UnaryCondition>
class FilteredSeq;

#include "funcy/impl/sequence_crtp.h"

#include <type_traits>
#include <utility>

template <typename InnerSequence, typename UnaryCondition>
class FilteredSeq : public SequenceCRTP<FilteredSeq<InnerSequence, UnaryCondition>> {
public:
  typedef typename InnerSequence::Elem Elem;

  FilteredSeq(InnerSequence& inner, const UnaryCondition& condition) :
    inner_(inner),
    condition_(condition),
    currElem_()
  {
    while (inner_ && !condition_(currElem_ = inner_.cval())) {
        inner_.next();
    }
  }

  bool empty() const
  {
    return inner_.empty();
  }

  const Elem& cval() const
  {
    return currElem_;
  }

  void next()
  {
    do {
        inner_.next();
    }
    while (inner_ && !condition_(currElem_ = inner_.cval()));
  }

private:
  InnerSequence& inner_;

  typedef typename std::conditional<std::is_function<UnaryCondition>::value,
      typename std::add_lvalue_reference<UnaryCondition>::type,
      UnaryCondition>::type UnaryConditionStorage;
  UnaryConditionStorage condition_;

  Elem currElem_;
};

template <typename SequenceImpl>
class UniqueCondition
{
  typedef typename SequenceImpl::Elem Elem;
public:
  UniqueCondition() :
    previousElem_(),
    firstCall_(true)
  { }

  bool operator()(const Elem& rElem)
  {
    bool result = true;
    if (firstCall_)
      {
        previousElem_ = rElem;
      }
    else if (previousElem_ == rElem) {
        result = false;
    }
    else {
        // TODO: avoid overwriting. keep a reference if the life time of the objects
        // in the Sequence is longer than one call to this operator
        previousElem_ = rElem;

    }
    return result;
  }

private:
  Elem previousElem_;
  bool firstCall_;
};

#endif /* FILTER_H_ */
