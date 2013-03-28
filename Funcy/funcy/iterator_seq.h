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
template <typename ForwardIterator, typename ElemType>
class AbstractIteratorSeq : public Sequence<AbstractIteratorSeq<ForwardIterator, ElemType>>
{
public:
  typedef ElemType Elem;

  AbstractIteratorSeq(const ForwardIterator& begin, const ForwardIterator& end)
  :
    it_(begin),
    end_(end)
  { }

  // default copy constructor and assignment operator

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

protected:
  void setIterators(const ForwardIterator& from, const ForwardIterator& to)
  {
    it_ = from;
    end_ = to;
  }

private:
  ForwardIterator it_;
  ForwardIterator end_;
};

template <typename ForwardIterator>
class IteratorSeq :
  public AbstractIteratorSeq<ForwardIterator,
                             typename std::iterator_traits<ForwardIterator>::value_type>
{
public:
  typedef typename std::iterator_traits<ForwardIterator>::value_type Elem;

  IteratorSeq(const ForwardIterator& begin, const ForwardIterator& end)
  :
    AbstractIteratorSeq<ForwardIterator,
                        typename std::iterator_traits<ForwardIterator>::value_type>(
      begin, end)
  { }
};

template <typename Elem>
class InitializerListSeq :
  public AbstractIteratorSeq<typename std::vector<Elem>::iterator,
                             Elem>
{
public:
  InitializerListSeq(const std::initializer_list<Elem>& l)
  :
    AbstractIteratorSeq<typename std::vector<Elem>::iterator, Elem>(
      seqData_.begin(), seqData_.end()),
      seqData_(l)
  {
    setIterators(seqData_.begin(), seqData_.end());
  }

  InitializerListSeq(const InitializerListSeq& other) :
    AbstractIteratorSeq<typename std::vector<Elem>::iterator, Elem>(
      seqData_.begin(), seqData_.end()),
      seqData_(other.seqData_)
  {
    setIterators(seqData_.begin(), seqData_.end());
  }

private:
  InitializerListSeq& operator=(const InitializerListSeq&) = delete;

  std::vector<Elem> seqData_;
};

//! @todo add variants that are able to take ownership of the passed collection or
//! initializer list

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
