// Copyright(C) 2019 Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "thinks/obj_io/obj_io.h"
#include "thinks/platonic_solids/platonic_solids.h"

namespace {

template <typename MeshT>
void WriteObjMesh(const std::string& file_name, const MeshT& mesh) {
  using MeshPositionsType = decltype(typename MeshT::positions);
  using MeshIndicesType = decltype(typename MeshT::triangle_indices);
  static_assert(
    std::tuple_size<MeshPositionsType>::value > 0 && 
    std::tuple_size<MeshPositionsType>::value % 3 == 0,
    "must have three elements per mesh position");
  static_assert(
    std::tuple_size<MeshIndicesType>::value > 0 && 
    std::tuple_size<MeshIndicesType>::value % 3 == 0,
    "must have three indices per triangle face");

  // Positions.
  auto pos_iter = std::begin(mesh.positions);
  const auto pos_iend = std::end(mesh.positions);
  const auto pos_mapper = [&pos_iter, pos_iend]() {
    using ObjPositionElementType = MeshPositionsType::value_type;
    using ObjPositionType = thinks::obj_io::Position<ObjPositionElementType, 3>;

    // Check that there are 3 or more position elements ahead.
    if (std::distance(pos_iter, pos_iend) < 3) {
      return thinks::obj_io::End<ObjPositionType>();
    }

    const auto pos_x = (*pos_iter++);
    const auto pos_y = (*pos_iter++);
    const auto pos_z = (*pos_iter++);
    return thinks::obj_io::Map(ObjPositionType(pos_x, pos_y, pos_z));
  };

  // Faces.
  auto idx_iter = std::begin(mesh.triangle_indices);
  const auto idx_iend = std::end(mesh.triangle_indices);
  const auto face_mapper = [&idx_iter, idx_iend]() {
    using ObjIndexType = thinks::obj_io::Index<MeshIndicesType::value_type>;
    using ObjFaceType = thinks::obj_io::TriangleFace<ObjIndexType>;

    // Check that there are 3 more indices ahead.
    if (std::distance(idx_iter, idx_iend) < 3) {
      return thinks::obj_io::End<ObjFaceType>();
    }

    // Create a face from the mesh indices.
    const auto idx_0 = ObjIndexType(*idx_iter++);
    const auto idx_1 = ObjIndexType(*idx_iter++);
    const auto idx_2 = ObjIndexType(*idx_iter++);
    return thinks::obj_io::Map(ObjFaceType(idx_0, idx_1, idx_2));
  };

  // Open the OBJ file and pass in the mappers.
  auto ofs = std::ofstream(file_name);
  if (!ofs) {
    throw std::runtime_error("failed to open '" + file_name + "'");
  }

  const auto result = thinks::obj_io::Write(ofs, pos_mapper, face_mapper);
  ofs.close();
}

template <typename MeshT>
void GenerateMeshFile(const std::string& mesh_file_prefix,
                      const std::string& mesh_file_name, const MeshT& mesh) {
  const auto obj_file_name = mesh_file_prefix + "/" + mesh_file_name;
  WriteObjMesh(obj_file_name, mesh);
  std::cout << "Generated '" << obj_file_name << "'" << std::endl;
}

} // namespace

int main(int argc, char* argv[]) {
  // Output location defaults to current directory.
  std::string mesh_file_prefix = ".";
  if (argc > 1) {
    mesh_file_prefix = argv[1];
  } 

  GenerateMeshFile(
    mesh_file_prefix, "4_tetrahedron.obj", 
    thinks::TetrahedronTriangleMesh<double, std::uint16_t>());
  GenerateMeshFile(
    mesh_file_prefix, "6_hexahedron.obj", 
    thinks::HexahedronTriangleMesh<double, std::uint16_t>());
  GenerateMeshFile(
    mesh_file_prefix, "8_octahedron.obj", 
    thinks::OctahedronTriangleMesh<double, std::uint16_t>());
  GenerateMeshFile(
    mesh_file_prefix, "12_dodecahedron.obj", 
    thinks::DodecahedronTriangleMesh<double, std::uint16_t>());
  GenerateMeshFile(
    mesh_file_prefix, "20_icosahedron.obj", 
    thinks::IcosahedronTriangleMesh<double, std::uint16_t>());

  return 0; 
}
