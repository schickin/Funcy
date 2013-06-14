/*
 * ring_buffer.h
 *
 *  Created on: 14.06.2013
 *      Author: schickin
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <array>
#include <initializer_list>

template <typename Elem, std::size_t Capacity>
class RingBuffer {
public:
  RingBuffer() :
    buf_({}),
    lastIndex_(Capacity-1)
  { }

  const Elem& operator[](std::ptrdiff_t offset) const
  { return buf_[(lastIndex_ + offset) % Capacity]; }

  Elem& operator[](std::ptrdiff_t offset)
  { return buf_[(lastIndex_ + offset) % Capacity]; }

  void push_back(const Elem& el)
  {
    lastIndex_ = (lastIndex_ + 1) % Capacity;
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
