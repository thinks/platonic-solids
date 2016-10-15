![alt text][header]

[header]: https://github.com/thinks/platonic-solids/blob/master/images/collection.png "Platonic Solids in 3D"

# Platonic Solids in 3D
This repository contains models of the five platonic solids in 3D. The models are found in the [model folder](https://github.com/thinks/platonic-solids/tree/master/models). Images of these models are found in the [image folder](https://github.com/thinks/platonic-solids/tree/master/images).

The motivation for this small project is that it is hard to find models of the platonic solids in a simple format. Generating the vertices of the models is trivial and well-documented (e.g. [wikipedia](https://en.wikipedia.org/wiki/Platonic_solid)]). However, discussions often omit how to generate the vertex indices for triangulations. The models provided in this repository are in the simplest possible format (.obj), which in its simplest form consists only of a vertex list and a face list in plain-text. Feel free to copy the data found here if you wish to use other formats. The models use shared vertices and higher order polygons (quads and pentagons) have been triangulated. The triangulation is in counter-clockwise order. Finally, the models are centered at the origin and scaled in the typical way such that the largest vertex magnitude is equal to either `1` (tetrahedron, cube, octahedron), or the gold ratio `(1 + sqrt(5)/2` (dodecahedron, icosahedron).

The images were rendered with a path tracer using Monte-Carlo sampling. The noise present in the images is typical for this type of process, where noise is iteratively removed as sampling increases. Finally, the wireframes were manually added as a post-processing step. 

## Future Work
It would be more clear to re-order the vertices such that they correspond to the table found at [wikipedia](https://en.wikipedia.org/wiki/Platonic_solid#Cartesian_coordinates)].
