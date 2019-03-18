// Copyright(C) 2019 Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#pragma once

#include <array>
#include <type_traits>

namespace thinks {
namespace platonic_solids_internal {

template <typename PositionT, std::size_t VertexCount, 
          typename IndexT, std::size_t TriangleCount>
struct PlatonicSolidTriangleMesh {
  std::array<PositionT, 3 * VertexCount> positions;
  std::array<IndexT, 3 * TriangleCount> triangle_indices;

  static_assert(std::is_floating_point_v<PositionT>,
                "FloatT must be a floating point type");
  static_assert(std::is_integral_v<IndexT>, 
                "IndexT must be an integral type");
};

template <typename FloatT>
struct Phi;

template <>
struct Phi<float> {
  // Golden ratio: (1.0f + std::sqrt(5)) / 2
  static constexpr float value = 1.6180339887498948482045868343656f;
};

template <>
struct Phi<double> {
  // Golden ratio: (1.0 + std::sqrt(5)) / 2
  static constexpr double value = 1.6180339887498948482045868343656;
};

} // namespace platonic_solids_internal

// 4 triangle faces.
template <typename FloatT, typename IndexT>
using TetrahedronTriangleMeshType =
    platonic_solids_internal::PlatonicSolidTriangleMesh<FloatT, 4, IndexT, 4>;

template <typename FloatT, typename IndexT>
constexpr TetrahedronTriangleMeshType<FloatT, IndexT>
TetrahedronTriangleMesh() noexcept {
  return TetrahedronTriangleMeshType<FloatT, IndexT>{
    decltype(TetrahedronTriangleMeshType<FloatT, IndexT>::positions){{
      -1, -1, -1,
      -1, 1, 1,
      1, -1, 1,
      1, 1, -1
    }},
    decltype(TetrahedronTriangleMeshType<FloatT, IndexT>::triangle_indices){{
      1, 0, 2,
      0, 1, 3,
      3, 1, 2,
      0, 3, 2
    }}        
  };
}

// 6 quad faces, tessellated into triangles, 2 triangles per quad.
template <typename FloatT, typename IndexT>
using HexahedronTriangleMeshType =
    platonic_solids_internal::PlatonicSolidTriangleMesh<FloatT, 8, IndexT, 6 * 2>;

template <typename FloatT, typename IndexT>
constexpr HexahedronTriangleMeshType<FloatT, IndexT>
HexahedronTriangleMesh() noexcept {
  return HexahedronTriangleMeshType<FloatT, IndexT>{
    decltype(HexahedronTriangleMeshType<FloatT, IndexT>::positions){{
      1, 1, -1,
      1, -1, 1,
      1, -1, -1,
      1, 1, 1,
      -1, -1, -1,
      -1, 1, -1,
      -1, 1, 1,
      -1, -1, 1
    }},
    decltype(HexahedronTriangleMeshType<FloatT, IndexT>::triangle_indices){{
      0, 1, 2,
      1, 0, 3,
      0, 4, 5,
      4, 0, 2,
      6, 0, 5,
      0, 6, 3,
      1, 6, 7,
      6, 1, 3,
      1, 4, 2,
      4, 1, 7,
      6, 4, 7,
      4, 6, 5      
    }}        
  };
}

// 8 triangle faces.
template <typename FloatT, typename IndexT>
using OctahedronTriangleMeshType =
    platonic_solids_internal::PlatonicSolidTriangleMesh<FloatT, 6, IndexT, 8>;

template <typename FloatT, typename IndexT>
constexpr OctahedronTriangleMeshType<FloatT, IndexT>
OctahedronTriangleMesh() noexcept {
  return OctahedronTriangleMeshType<FloatT, IndexT>{
    decltype(OctahedronTriangleMeshType<FloatT, IndexT>::positions){{
      0, 0, -1,
      -1, 0, 0,
      0, 1, 0,
      1, 0, 0,
      0, -1, 0,
      0, 0, 1
    }},
    decltype(OctahedronTriangleMeshType<FloatT, IndexT>::triangle_indices){{
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

// 12 pentagon faces, tessellated into triangles, 3 triangles per pentagon.
template <typename FloatT, typename IndexT>
using DodecahedronTriangleMeshType =
    platonic_solids_internal::PlatonicSolidTriangleMesh<FloatT, 20, IndexT, 12 * 3>;

template <typename FloatT, typename IndexT>
constexpr DodecahedronTriangleMeshType<FloatT, IndexT>
DodecahedronTriangleMesh() noexcept {
  constexpr auto p = platonic_solids_internal::Phi<FloatT>::value;
  constexpr auto ip = FloatT{1} / p;
  return DodecahedronTriangleMeshType<FloatT, IndexT>{
    decltype(DodecahedronTriangleMeshType<FloatT, IndexT>::positions){{
      -1, 1, -1,
      -p, 0, ip,
      -p, 0, -ip,
      -1, 1, 1,
      -ip, p, 0,
      1, 1, 1,
      ip, p, 0,
      0, ip, p,
      -1, -1, 1,
      0, -ip, p,
      -1, -1, -1,
      -ip, -p, 0,
      0, -ip, -p,
      0, ip, -p,
      1, 1, -1,
      p, 0, -ip,
      p, 0, ip,
      1, -1, 1,
      ip, -p, 0,
      1, -1, -1
    }},
    decltype(DodecahedronTriangleMeshType<FloatT, IndexT>::triangle_indices){{
      1, 0, 2,
      0, 1, 3,
      0, 3, 4,
      4, 5, 6,
      5, 4, 3,
      5, 3, 7,
      8, 3, 1,
      3, 8, 7,
      7, 8, 9,
      8, 10, 11,
      10, 8, 2,
      2, 8, 1,
      0, 10, 2,
      10, 0, 12,
      12, 0, 13,
      0, 14, 13,
      14, 0, 6,
      6, 0, 4,
      15, 5, 16,
      5, 15, 14,
      5, 14, 6,
      9, 5, 7,
      5, 9, 17,
      5, 17, 16,
      18, 8, 11,
      8, 18, 17,
      8, 17, 9,
      19, 10, 12,
      10, 19, 11,
      11, 19, 18,
      13, 19, 12,
      19, 13, 14,
      19, 14, 15,
      19, 17, 18,
      17, 19, 16,
      16, 19, 15
    }}          
  };
}

// 20 triangle faces.
template <typename FloatT, typename IndexT>
using IcosahedronTriangleMeshType =
    platonic_solids_internal::PlatonicSolidTriangleMesh<FloatT, 12, IndexT, 20>;

template <typename FloatT, typename IndexT>
constexpr IcosahedronTriangleMeshType<FloatT, IndexT>
IcosahedronTriangleMesh() noexcept {
  constexpr auto p = platonic_solids_internal::Phi<FloatT>::value;
  return IcosahedronTriangleMeshType<FloatT, IndexT>{
    decltype(IcosahedronTriangleMeshType<FloatT, IndexT>::positions){{
      -1, 0, -p,
      0, p, -1,
      1, 0, -p,
      0, p, 1,
      p, 1, 0,
      1, 0, p,
      -p, 1, 0,
      -p, -1, 0,
      -1, 0, p,
      0, -p, 1,
      p, -1, 0,
      0, -p, -1      
    }},
    decltype(IcosahedronTriangleMeshType<FloatT, IndexT>::triangle_indices){{
      1, 6, 3,
      0, 6, 1,
      3, 4, 1,
      3, 6, 8,
      6, 0, 7,
      2, 0, 1,
      4, 3, 5,
      4, 2, 1,
      7, 8, 6,
      5, 3, 8,
      0, 11, 7,
      11, 0, 2,
      4, 5, 10,
      10, 2, 4,
      8, 7, 9,
      8, 9, 5,
      7, 11, 9,
      11, 2, 10,
      10, 5, 9,
      11, 10, 9
    }}        
  };
}

} // namespace thinks
