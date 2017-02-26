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

#ifndef H9_VERSION_H
#define H9_VERSION_H

/// Denotes version of H9 in the format {MAJOR}{MINOR}{PATCH},
/// whereas each number is a two-digit decimal number without
/// leading zeros (e.g. 900 is version 0.9.0).
#define H9_VERSION 100

/// Defined to the major version number of H9.
#define H9_MAJOR_VERSION (H9_VERSION / 10000)

/// Defined to the minor version number of H9.
#define H9_MINOR_VERSION ((H9_VERSION / 100) % 100)

/// Defined to the patch version number of H9.
#define H9_PATCH_VERSION (H9_VERSION % 100)

#endif // H9_VERSION_H
