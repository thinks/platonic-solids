// Copyright(C) 2019 Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#pragma once

#include <array>
#include <utility>
#include <type_traits>
#include <vector>

namespace thinks {
namespace platonic_solids_internal {

template <typename VerticesT, typename IndicesT>
constexpr std::pair<VerticesT, IndicesT> MakeMesh(
    const VerticesT &vertices, const IndicesT &indices) noexcept {
  static_assert(std::is_floating_point_v<typename VerticesT::value_type>,
                "FloatT must be a floating point type");
  static_assert(std::is_integral_v<typename IndicesT::value_type>,
                "IndexT must be an integral type");
  return std::make_pair(vertices, indices);
}

} // platonic_solids_internal

template <typename PositionT, std::size_t VertexCount, 
          typename IndexT, std::size_t TriangleCount>
struct TriangleMesh {
  std::array<PositionT, 3 * VertexCount> positions;
  std::array<IndexT, 3 * TriangleCount> triangle_indices;

  static_assert(std::is_floating_point_v<PositionT>,
                "FloatT must be a floating point type");
  static_assert(std::is_integral_v<IndexT>, 
                "IndexT must be an integral type");
};

template <typename FloatT, typename IndexT>
using OctahedronTriangleMesh = TriangleMesh<FloatT, 6, IndexT, 8>;

template <typename FloatT, typename IndexT>
constexpr OctahedronTriangleMesh<FloatT, IndexT>
Octahedron() noexcept {
  return OctahedronTriangleMesh<FloatT, IndexT>{
    decltype(OctahedronTriangleMesh<FloatT, IndexT>::positions){{
      0, 0, -1,
      -1, 0, 0,
      0, 1, 0,
      1, 0, 0,
      0, -1, 0,
      0, 0, 1
    }},
    decltype(OctahedronTriangleMesh<FloatT, IndexT>::triangle_indices){{
      0, 1, 2,
      3, 0, 2,
      1, 0, 4,
      2, 1, 5,
      3, 2, 5,
      4, 0, 3,
      5, 1, 4,
      5, 4, 3      
    }}        
  };
}

} // namespace thinks
