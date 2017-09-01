//=============================================================================
// Copyright (C) 2011-2016 by Graphics & Geometry Group, Bielefeld University
// Copyright (C) 2017 Daniel Sieger
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//=============================================================================

#include "MeshProcessingViewer.h"

#include <surface_mesh/algorithms/SurfaceSubdivision.h>
#include <surface_mesh/algorithms/SurfaceFeatures.h>
#include <surface_mesh/algorithms/SurfaceSimplification.h>
#include <surface_mesh/algorithms/SurfaceRemeshing.h>

using namespace surface_mesh;

//=============================================================================

void MeshProcessingViewer::keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS) // only react on key press events
        return;

    switch (key)
    {
        case GLFW_KEY_L:
        {
            // SurfaceFeatures fd(m_mesh);
            // fd.detectAngle(90);
            SurfaceSubdivision sd(m_mesh);
            sd.catmullClark();
            updateMesh();
            break;
        }
        case GLFW_KEY_R:
        {
            Scalar l(0);
            for (auto eit : m_mesh.edges())
                l += distance(m_mesh.position(m_mesh.vertex(eit, 0)),
                              m_mesh.position(m_mesh.vertex(eit, 1)));
            l /= (Scalar)m_mesh.nEdges();

            //uniformRemeshing(m_mesh,l);

            auto bb = m_mesh.bounds().size();
            adaptiveRemeshing(m_mesh,
                              0.001*bb,  // min length
                              0.2*bb,    // max length
                              0.001*bb); // approx. error
            updateMesh();
            break;
        }
        case GLFW_KEY_S:
        {
            simplify(m_mesh,m_mesh.nVertices() * 0.1, 5);
            updateMesh();
            break;
        }
        case GLFW_KEY_T:
        {
            if (!m_mesh.isTriangleMesh())
                m_mesh.triangulate();
            updateMesh();
            break;
        }
        default:
        {
            MeshViewer::keyboard(window, key, scancode, action, mods);
            break;
        }
    }
}
