//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef MEMORY_H_
#define MEMORY_H_

#include "funcy/sequence.h"


template <typename InnerSequence>
class MemorizingSeq : public Sequence<MemorizingSeq<InnerSequence>>
{
public:
    typedef typename InnerSequence::Elem Elem;

    MemorizingSeq(InnerSequence& inner) :
      inner_(inner)
    { }

    bool empty() const
    {
      return inner_.empty();
    }

    const Elem& cval() const
    {
      return buf_[bufPos_];
    }

    void next()
    {
      bufPos_ = (bufPos_ + 1) % bufSize;
      buf_[bufPos_] = inner_.cval();
    }

    const Elem& cpred(int idx) const
    {
      return buf_[(bufPos_ - idx) % bufSize];
    }

private:
    static const int bufSize = 2;

    InnerSequence& inner_;
    int bufPos_;
    Elem[bufSize] buf_;
};

#endif /* MEMORY_H_ */
