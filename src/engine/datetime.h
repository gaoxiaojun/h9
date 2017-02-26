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

#ifndef H9_DATE_TIME_H
#define H9_DATE_TIME_H

/**
 *  IMPORTANT: in h9 framework time means <b>local timezone time</b>
 */

#ifdef H9_BOOST_NO_LIB
#define BOOST_DATE_TIME_NO_LIB
#endif

#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/functional/hash.hpp>

namespace h9 {

// gregorian
using date = boost::gregorian::date;
using date_duration = boost::gregorian::date_duration;

using boost::gregorian::years;
using boost::gregorian::months;
using boost::gregorian::weeks;
using boost::gregorian::days;
// posix time
using ptime = boost::posix_time::ptime;
using time_duration = boost::posix_time::time_duration;
using time_period = boost::posix_time::time_period;

using boost::date_time::special_values;
using boost::date_time::not_special;
using boost::date_time::neg_infin;
using boost::date_time::pos_infin;
using boost::date_time::not_a_date_time;
using boost::date_time::max_date_time;
using boost::date_time::min_date_time;

using boost::posix_time::hours;
using boost::posix_time::minutes;
using boost::posix_time::seconds;
using boost::posix_time::milliseconds;
using boost::posix_time::microseconds;

using time_zone_ptr = boost::local_time::time_zone_ptr;
using clock = boost::posix_time::microsec_clock;

} // namespace h9

namespace std {
template <>
class hash<boost::posix_time::ptime> {
public:
  size_t operator()(const boost::posix_time::ptime& t) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, t.date().julian_day());
    boost::hash_combine(seed, t.time_of_day().ticks());
    return seed;
  }
};
} // namespace std

#endif // H9_DATE_TIME_H
