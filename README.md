![alt text][header]

[header]: https://github.com/thinks/platonic-solids/blob/master/images/collection.png "Platonic Solids in 3D"

# Platonic Solids in 3D
This repository contains 3D [models](https://github.com/thinks/platonic-solids/tree/master/models) of the [platonic solids]((https://en.wikipedia.org/wiki/Platonic_solid)) in the [OBJ file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file), [images](https://github.com/thinks/platonic-solids/tree/master/images) of the platonic solids, and C++ [code](https://github.com/thinks/platonic-solids/tree/master/thinks/platonic_solids) to generate triangle meshes of the platonic solids.

The motivation for this small project is that it is hard to find models of the platonic solids in a simple format. Generating the vertices of the models is trivial and well-documented (e.g. [wikipedia](https://en.wikipedia.org/wiki/Platonic_solid)). However, discussions often omit how to generate the vertex indices for triangulations.

Everything in this repository is released under the [MIT license](https://en.wikipedia.org/wiki/MIT_License).

## Models
The models are found in the [model folder](https://github.com/thinks/platonic-solids/tree/master/models). These models are stored in the simplest possible format ([OBJ file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file)), containing only vertices and face indices. Feel free to copy the data found here if you wish to use other formats. The models use shared vertices, and higher order polygons (quads and pentagons) have been triangulated. The triangulation is in counter-clockwise order. Finally, the models are centered at the origin and scaled in the typical way such that the largest vertex magnitude is equal to either `1` (tetrahedron, cube, octahedron), or the golden ratio `(1 + sqrt(5))/2` (dodecahedron, icosahedron).

## Code
In some cases it is convenient to be able to generate triangle meshes of the platonic solids in code, rather than having to rely on parsing models from files. Unit testing is a good example of this, where it is often desirable to avoid file dependencies.  

```bash
$ cd d: && mkdir platonic-solids
$ cd platonic-solids
$ git clone --recursive https://github.com/thinks/platonic-solids.git .
$ mkdir build && cd build
$ cmake -DPLATONIC_SOLIDS_GENERATE_MODELS=ON ..
$ cmake --build . --config Release
```

Note that a recursive clone is required to initialize the [obj-io](https://github.com/thinks/obj-io) submodule. When the configuration flag `PLATONIC_SOLIDS_GENERATE_MODELS` is set to `ON`, the files in the [model folder](https://github.com/thinks/platonic-solids/tree/master/models) are generated as part of the build process. This can be used to make sure that the model files are always in sync with the triangle meshes generated by the code. To ignore this feature simply set the flag to `PLATONIC_SOLIDS_GENERATE_MODELS=OFF`, or don't set it at all. 

The code for generating triangle meshes is located in a [single header file](https://github.com/thinks/platonic-solids/blob/master/thinks/platonic_solids/platonic_solids.h). If, for instance, we wish to generate a scaled triangle mesh it might look something like this.

```cpp
#include <cstdint>
#include <tuple>
#include <vector>

#include "thinks/platonic_solids/platonic_solids.h"

struct MyVec3 {
  float x;
  float y;
  float z;
};

struct MyMesh {
  std::vector<MyVec3> positions;
  std::vector<std::uint32_t> indices;
};

// Takes in any of the platonic solids and returns a scaled copy
// in another mesh format.
template <typename MeshT>
MyMesh ScaledSolid(const MeshT& mesh, const float scale) {
  using MeshPositionsType = decltype(typename MeshT::positions);
  using MeshIndicesType = decltype(typename MeshT::triangle_indices);

  MyMesh my_mesh;

  // Copy and scale positions.
  const std::size_t kPosCount = std::tuple_size<MeshPositionsType>::value / 3;
  my_mesh.positions.reserve(kPosCount);
  for (std::size_t i = 0; i < kPosCount; ++i) {
    my_mesh.positions.push_back(MyVec3{
        scale * mesh.positions[3 * i],
        scale * mesh.positions[3 * i + 1],
        scale * mesh.positions[3 * i + 2],
    });
  }

  // Copy indices.
  const std::size_t kIdxCount = std::tuple_size<MeshIndicesType>::value;
  my_mesh.indices.reserve(kIdxCount);
  for (std::size_t i = 0; i < kIdxCount; ++i) {
    my_mesh.indices.push_back(mesh.triangle_indices[i]);
  }

  return my_mesh;
}

MyMesh ScaledIcosahedron() {
  // Note that we provide the types to be used for the platonic solid
  // positions and indices here.
  return ScaledSolid(thinks::IcosahedronTriangleMesh<float, std::uint32_t>(),
                     2.f);
}
```

## Images
Images of the platonic solids can be found in the [image folder](https://github.com/thinks/platonic-solids/tree/master/images). The images were rendered with a path tracer using Monte-Carlo sampling. The graininess present in the images is typical for this type of process, where noise is iteratively removed as sampling increases. Finally, the wireframes were manually added as a post-processing step. 

## Future Work
It would be more clear to re-order the vertices such that they correspond to the table found at [wikipedia](https://en.wikipedia.org/wiki/Platonic_solid#Cartesian_coordinates).
