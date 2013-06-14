//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef MEMORY_H_
#define MEMORY_H_

#include <cstddef>

template <typename InnerSequence, std::size_t Capacity>
class ConstantSizeMemorySeq;


#include "funcy/sequence.h"
#include "funcy/util/ring_buffer.h"

template <typename InnerSequence, std::size_t Capacity>
class ConstantSizeMemorySeq : public Sequence<ConstantSizeMemorySeq<InnerSequence, Capacity>>
{
public:
    typedef typename InnerSequence::Elem Elem;

    ConstantSizeMemorySeq(InnerSequence& inner) :
      inner_(inner), buf_()
    {
      buf_.push_back(inner_.cval());
    }

    bool empty() const
    {
      return inner_.empty();
    }

    const Elem& cval() const
    {
      return buf_[0];
    }

    void next()
    {
      inner_.next();
      buf_.push_back(inner_.cval());
    }

    const Elem& cpred(std::ptrdiff_t idx = -1) const
    {
      return buf_[idx];
    }

private:
    InnerSequence& inner_;
    RingBuffer<Elem, Capacity> buf_;
};

#endif /* MEMORY_H_ */
