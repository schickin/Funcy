//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef MAP_H_
#define MAP_H_

#include "funcy/sequence.h"

#include <type_traits>

template <typename SequenceImpl>
class Sequence;

template <typename InnerSequence, typename UnaryFunction>
class MappedSeq : public Sequence<MappedSeq<InnerSequence, UnaryFunction>> {
public:
  typedef decltype(
      std::declval<UnaryFunction>()(
          std::declval<typename InnerSequence::Elem>()
      )
  ) Elem;

  MappedSeq(InnerSequence& inner, const UnaryFunction& func) :
    inner_(inner),
    func_(func)
  { }

  bool empty() const
  {
    return inner_.empty();
  }

  const Elem cval() const
  {
    return func_(inner_.cval());
  }

  void next()
  {
    inner_.next();
  }

private:
  InnerSequence& inner_;
  const UnaryFunction& func_;
};


#endif /* MAP_H_ */
