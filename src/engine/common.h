/******************************************************************************
 *                         __  __  ____                                       *
 *                        / / / / / __ \                                      *
 *                       / /_/ / / /_/ /          C++                         *
 *                      / __  /  \__, /           Trading                     *
 *                     /_/ /_/  /____/            Framework                   *
 *                                                                            *
 * Copyright (C) 2017   Xiaojun Gao                                           *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/

#ifndef H9_COMMON_H
#define H9_COMMON_H

#include "datetime.h"
#include <boost/noncopyable.hpp>
#include <memory>
#include <utility> // forward

namespace h9 {

using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;

template <typename E> // C++14
constexpr auto toUType(E enumerator) noexcept
{
  return static_cast<std::underlying_type_t<E>>(enumerator);
}

// auto val = std::get<toUType(UserInfoFields::uiEmail)>(uInfo);

using noncopyable = boost::noncopyable;

#define H9_LOG(...)
#define H9_INFO(...)
#define H9_WARNING(...)
#define H9_ERROR(...)

} // namespace h9

#endif // H9_COMMON_H
