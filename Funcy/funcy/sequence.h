//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

template <typename SequenceImpl>
class SequenceCRTP;

// Forward declarations of all supported sequence types
template <typename InnerSequence, typename UnaryCondition>
class FilteredSeq;
template <typename SequenceImpl>
class UniqueCondition;
template <typename InnerSequence, typename UnaryFunction>
class MappedSeq;


#include "funcy/memory.h"

#include <cassert>
#include <iterator>
#include <ostream>
#include <type_traits>

template <typename SequenceImpl>
class SequenceCRTP
{
public:
  // must be overridden by subclass
  struct AbstractTypeMustBeOverridden;
  typedef AbstractTypeMustBeOverridden& Elem;

  // must be overridden by subclass
  bool empty() const;

  // must be overridden by subclass
  const Elem cval() const;

  // must be overridden by subclass
  void next();

  operator bool() const
  {
    return !self().empty();
  }

  //! Write sequence to STL container
  //!
  //! @{

  //! Write to STL iterator.
  template <typename OutputIterator>
  void writeTo(OutputIterator itOut,
      typename std::iterator_traits<OutputIterator>::iterator_category* = nullptr)
  {
    while (!self().empty()) {
        *itOut++ = self().cval();
        self().next();
    }
  }

  //! Write to STL collection
  template <typename Collection>
  void writeTo(Collection& coll,
      typename Collection::iterator* = nullptr)
  {
    writeTo(std::back_inserter(coll));
  }

  //! Write to output stream
  void writeTo(std::ostream& os, const char* delim = "")
  {
    writeTo(std::ostream_iterator<typename SequenceImpl::Elem>(os, delim));
  }

  //! @}

  // TODO: write tests
  std::size_t count()
  {
    std::size_t result(0);
    while (!self().empty()) {
        ++result;
        self().next();
    }
    return result;
  }

  template <typename UnaryPredicate>
  FilteredSeq<SequenceImpl, UnaryPredicate> filter(const UnaryPredicate& predicate)
  {
    return FilteredSeq<SequenceImpl, UnaryPredicate>(self(), predicate);
  }

  FilteredSeq<SequenceImpl, UniqueCondition<SequenceImpl> > unique()
  {
    return filter(UniqueCondition<SequenceImpl>());
  }

  template <typename UnaryFunction>
  MappedSeq<SequenceImpl, UnaryFunction> map(const UnaryFunction& func)
  {
    return MappedSeq<SequenceImpl, UnaryFunction>(self(), func);
  }

  template <std::size_t Capacity>
  ConstantSizeMemorySeq<SequenceImpl, Capacity> withMemory()
  {
    return ConstantSizeMemorySeq<SequenceImpl, Capacity>(self());
  }

protected:
  SequenceImpl& self()
  {
    return static_cast<SequenceImpl&>(*this);
  }

  const SequenceImpl& self() const
  {
    return static_cast<const SequenceImpl&>(*this);
  }
};

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
