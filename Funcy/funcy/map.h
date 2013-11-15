//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef MAP_H_
#define MAP_H_

template <typename InnerSequence, typename UnaryFunction>
class MappedSeq;

#include "funcy/impl/sequence_crtp.h"

#include <functional>
#include <type_traits>

template <typename InnerSequence, typename UnaryFunction>
class MappedSeq : public SequenceCRTP<MappedSeq<InnerSequence, UnaryFunction>,
                                      typename std::result_of<
                                        decltype(std::declval<UnaryFunction>())&(
                                           typename InnerSequence::Elem)>::type>
{
public:
  typedef typename std::result_of<
      decltype(std::declval<UnaryFunction>())&(typename InnerSequence::Elem)>::type Elem;

  MappedSeq(InnerSequence& inner, const UnaryFunction& func) :
    inner_(inner),
    func_(func)
  { }

  bool empty() const
  {
    return inner_.empty();
  }

  Elem cval() const
  {
    return func_(inner_.cval());
  }

  void next()
  {
    inner_.next();
  }

private:
  InnerSequence& inner_;
  // @todo store typed callables
  std::function<Elem(typename InnerSequence::Elem)> func_;
};

#endif /* MAP_H_ */
