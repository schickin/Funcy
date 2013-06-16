//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ITERATOR_SEQ_H_
#define ITERATOR_SEQ_H_

#include "funcy/sequence.h"

#include <iterator>
#include <vector>

//! Wrap an STL iterator as a sequence.
//!
template <typename ForwardIterator>
class IteratorSeq : public Sequence<IteratorSeq<ForwardIterator>>
{
public:
  typedef typename std::iterator_traits<ForwardIterator>::value_type Elem;

  IteratorSeq(const ForwardIterator& begin, const ForwardIterator& end)
  :
    it_(begin),
    end_(end)
  { }

  bool empty() const
  {
    return it_ == end_;
  }

  const Elem& cval() const
  {
    return *it_;
  }

  void next()
  {
    ++it_;
  }

private:
  ForwardIterator it_;
  const ForwardIterator end_;
};

template <typename ElemType>
class InitializerListSeq : public Sequence<InitializerListSeq<ElemType>>
{
public:
  typedef ElemType Elem;

  InitializerListSeq(const std::initializer_list<ElemType>& l)
  :
    seqData_(l),
    it_(seqData_.begin()),
    end_(seqData_.end())
  { }

  InitializerListSeq(const InitializerListSeq<ElemType>& other)
  :
    seqData_(other.seqData_),
    it_(seqData_.begin()),
    end_(seqData_.end())
  { }

  bool empty() const
  {
    return it_ == end_;
  }

  const Elem& cval() const
  {
    return *it_;
  }

  void next()
  {
    ++it_;
  }

private:
  InitializerListSeq& operator=(const InitializerListSeq&) = delete;

  typedef std::vector<Elem> Container;
  Container seqData_;
  typename Container::iterator it_;
  const typename Container::iterator end_;

};

//! Constructor method make_seq.
//!
//! Convert STL collections or iterators to sequences.
//! @{

template <typename Coll>
IteratorSeq<typename Coll::const_iterator> make_seq(const Coll& c)
{
  return IteratorSeq<typename Coll::const_iterator>(c.begin(), c.end());
}

template <typename Elem>
InitializerListSeq<Elem> make_seq(const typename std::initializer_list<Elem>& l)
{
  return InitializerListSeq<Elem>(l);
}

template <typename Coll>
IteratorSeq<typename Coll::iterator> make_seq(Coll& c)
{
  return IteratorSeq<typename Coll::iterator>(c.begin(), c.end());
}

template <typename Iter>
IteratorSeq<Iter> make_seq(const Iter& begin, const Iter& end)
{
  return IteratorSeq<Iter>(begin, end);
}

//! @}

#endif /* ITERATOR_SEQ_H_ */
