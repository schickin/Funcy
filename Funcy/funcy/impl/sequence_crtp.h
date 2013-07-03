//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SEQUENCE_CRTP_H_
#define SEQUENCE_CRTP_H_

#include <cassert>
#include <iterator>
#include <vector>
#include <ostream>
#include <type_traits>


// Forward declarations of all supported sequence types
template <typename InnerSequence, typename UnaryCondition>
class FilteredSeq;
template <typename SequenceImpl>
class UniqueCondition;
template <typename InnerSequence, typename UnaryFunction>
class MappedSeq;
template <typename InnerSequence, std::size_t Capacity>
class ConstantSizeMemorySeq;
template <typename InnerSeq1, typename InnerSeq2>
class ConcatenatedSequence;

class SequenceTag
{ };

template <typename SequenceImpl, typename Elem>
class SequenceCRTP : public SequenceTag
{
public:
  // must be overridden by subclass
  bool empty() const;

  // must be overridden by subclass
  Elem cval() const;

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

  std::vector<Elem> toVec()
  {
    std::vector<Elem> result;
    self().writeTo(result);
    return result;
  }

  // TODO: write tests
  std::size_t count()
  {
    std::size_t result(0);
    while (!self().empty())
    {
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

  template <typename OtherSeq>
  int compareWith(OtherSeq& other)
  {
    while (!self().empty() && !other.empty())
    {
      if (self().cval() < other.cval())
      {
        return -1;
      }
      if (other.cval() < self().cval())
      {
        return 1;
      }
      self().next();
      other.next();
    }
    if (self().empty())
    {
      if (other.empty())
      {
        return 0;
      }
      return -1;
    }
    return 1;
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


#endif /* SEQUENCE_CRTP_H_ */
