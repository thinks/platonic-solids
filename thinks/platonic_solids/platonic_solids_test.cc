// Copyright(C) 2019 Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "thinks/platonic_solids/platonic_solids.h"

namespace {

void DummyTest() {
  int a = 2;
  int b = 3;
  REQUIRE(a == b);
}

void DummyTest2() {
  const auto oct_mesh = thinks::Octahedron<float, int>();
}

} // namespace
