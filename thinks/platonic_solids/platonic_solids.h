// Copyright(C) 2019 Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#pragma once

#include <array>
#include <utility>
#include <type_traits>
#include <vector>

namespace thinks {

template <typename FloatT, typename IndexT>
constexpr std::pair<std::array<FloatT, 6 * 3>, std::array<IndexT, 8 * 3>> 
Octahedron() noexcept {
  static_assert(std::is_floating_point_v<FloatT>, "FloatT must be a floating point type");
  static_assert(std::is_integral_v<IndexT>, "IndexT must be an integral type");
  return std::make_pair(
    std::array<FloatT, 6 * 3>{{
      0, 0, -1,
      -1, 0, 0,
      0, 1, 0,
      1, 0, 0,
      0, -1, 0,
      0, 0, 1
    }}, 
    std::array<IndexT, 8 * 3>{{
      0, 1, 2,
      3, 0, 2,
      1, 0, 4,
      2, 1, 5,
      3, 2, 5,
      4, 0, 3,
      5, 1, 4,
      5, 4, 3      
    }});
}

} // namespace thinks