/*
 * ring_buffer.h
 *
 *  Created on: 14.06.2013
 *      Author: schickin
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <array>
#include <cassert>
#include <cstdlib>
#include <initializer_list>

template <typename Elem, std::size_t Capacity>
class RingBuffer {
public:
  RingBuffer() :
    buf_({}), // default initialize all elements (init with zero for built-in types)
    lastIndex_(Capacity-1)
  { }

  const Elem& operator[](std::ptrdiff_t offset) const
  {
    assert(offset <= 0);
    assert(abs(offset) < Capacity);
    return buf_[(lastIndex_ + Capacity + offset) % Capacity];
  }

  Elem& operator[](std::ptrdiff_t offset)
  {
    assert(offset <= 0);
    assert(abs(offset) < Capacity);
    return buf_[(lastIndex_ + Capacity + offset) % Capacity];
  }

  void push_back(const Elem& el)
  {
    lastIndex_ = (lastIndex_ == Capacity-1) ? 0 : lastIndex_+1;
    buf_[lastIndex_] = el;
  }

  void push_back(const std::initializer_list<Elem>& elems) {
    for (auto el : elems) {
      push_back(el);
    }
  }

private:
  std::array<Elem, Capacity> buf_;
  std::size_t lastIndex_;
};


#endif /* RING_BUFFER_H_ */
