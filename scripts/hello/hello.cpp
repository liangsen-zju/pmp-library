#include <iostream>

#include "pmp/SurfaceMesh.h"
#include "pmp/io/io.h"

int main()
{
    // instantiate a SurfaceMesh object
    pmp::SurfaceMesh mesh;

    // add 4 vertices
    const auto v0 = mesh.add_vertex(pmp::Point(0, 0, 0));
    const auto v1 = mesh.add_vertex(pmp::Point(1, 0, 0));
    const auto v2 = mesh.add_vertex(pmp::Point(0, 1, 0));
    const auto v3 = mesh.add_vertex(pmp::Point(0, 0, 1));

    // // add 4 triangles
    mesh.add_triangle(v0, v1, v3);
    mesh.add_triangle(v1, v2, v3);
    mesh.add_triangle(v2, v0, v3);
    mesh.add_triangle(v0, v2, v1);

    //cout
    std::cout << "veties = " << mesh.n_vertices() << std::endl;
    std::cout << "faces = " << mesh.n_faces() << std::endl;
    std::cout << "edges = " << mesh.n_edges() << std::endl;
    std::cout << "halfedges= " << mesh.n_halfedges() << std::endl;

    // // read a obj files
    // pmp::read(mesh, "../external/pmp-data/off/bunny.off");
    // pmp::write(mesh, "output.obj");

    std::cout << "write obj" << std::endl;
}
