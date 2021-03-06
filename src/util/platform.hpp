//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

/** @file util/platform.hpp
 *
 *  @brief Platform and compiler specific hacks.
 */

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>

// ----------------------------------------------------------------------------- : Windows


// ----------------------------------------------------------------------------- : Linux

// ----------------------------------------------------------------------------- : GCC

#ifdef __GNUC__
  
  /// Absolute value of integers
  template <typename T>
  inline T abs(T a) { return a < 0 ? -a : a; }
  
#endif

