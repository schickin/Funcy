/*
 * metaprog.h
 *
 *  Created on: 15.11.2013
 *      Author: schickin
 */

#ifndef METAPROG_H_
#define METAPROG_H_

#include <type_traits>

template <typename Callable>
using function_storage =
    typename std::conditional<std::is_function<Callable>::value,
                              const Callable&,
                              Callable>::type;

// Definition without declaration to show type info in compiler errors
template <typename T>
class TD;

#endif /* METAPROG_H_ */
