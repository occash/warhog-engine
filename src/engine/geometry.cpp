#include "geometry.h"
#include "render/renderer.h"
#include "math\mathlib.h"

unsigned char floatToChar(float value)
{
    //Scale and bias
    value = (value + 1.0f) * 0.5f;
    return (unsigned char)(value * 255.0f);
}

Geometry::Geometry(Renderer *currentRenderer) : m_renderer(currentRenderer)
{
}


Geometry::~Geometry()
{
}


//TODO: Peter said that there are unnecessary vertex inside the cube
//TODO: Now Width divisions: 1 Height divisions : 1 Depth divisions : 1
//TODO: Divisions cube
Mesh *Geometry::cube(float width, float height, float depth,
                     int widthDiv, int heightDiv, int depthDiv)
{
    Mesh *m_cube = m_renderer->createMesh();
    m_cube->verticies.resize(24);
    m_cube->indices.resize(36);
    int ind = 0;
    for (int iter = 0; iter < 3; iter++)
    {
        for (int i = 0; i <= widthDiv; ++i)
        {
            for (int j = 0; j <= heightDiv; ++j)
            {
                for (int k = 0; k <= depthDiv; ++k)
                {
                    float xPos = -width / 2 + i * width / widthDiv;
                    float yPos = -height / 2 + j * height / heightDiv;
                    float zPos = -depth / 2 + k * depth / depthDiv;
                    m_cube->verticies[ind].position[0] = xPos;
                    m_cube->verticies[ind].position[1] = yPos;
                    m_cube->verticies[ind].position[2] = zPos;
                    m_cube->verticies[ind].normal[0] = floatToChar(0.0f);
                    m_cube->verticies[ind].normal[1] = floatToChar(0.0f);
                    m_cube->verticies[ind].normal[2] = floatToChar(0.0f);
                    m_cube->verticies[ind].normal[3] = floatToChar(0.0f);
                    if ((i == 0 || i == widthDiv) && (j == 0 || j == heightDiv) && (k == 0 || k == heightDiv))
                    {
                        switch (iter)
                        {
                        case 0:
                            m_cube->verticies[ind].normal[0] = floatToChar(Math::sign(xPos));
                            break;
                        case 1:
                            m_cube->verticies[ind].normal[1] = floatToChar(Math::sign(yPos));
                            break;
                        case 2:
                            m_cube->verticies[ind].normal[2] = floatToChar(Math::sign(zPos));
                            break;
                        }
                    }
                    else
                    {
						//TODO:normals for not corner vertext
                        m_cube->verticies[ind].normal[0] = floatToChar(xPos / width);
                        m_cube->verticies[ind].normal[1] = floatToChar(yPos / height);
                        m_cube->verticies[ind].normal[2] = floatToChar(zPos / depth);
                    }
                    ++ind;
                }
            }
        }
    }
    m_cube->indices =
    {
        18, 22, 20, 20, 16, 18,
        6, 5, 4, 6, 7, 5,
        17, 21, 23, 17, 23, 19,
        1, 3, 2, 0, 1, 2,
        10, 11, 15, 15, 14, 10,
        8, 12, 13, 13, 9, 8
    };
    return m_cube;
}

Mesh *Geometry::plane(float width /* = 1 */, float height /* = 1 */)
{
    Mesh *m_plane = m_renderer->createMesh();

    std::vector<Vertex> verticies;

    Vertex h_vertex;

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            h_vertex.position[0] = pow(-1, i) * width / 2;
            h_vertex.position[1] = pow(-1, j) * height / 2;
            h_vertex.position[2] = 0;
            verticies.push_back(h_vertex);
        }
    }

    m_plane->verticies = verticies;
    m_plane->indices =
    {
        0, 2, 1, 1, 2, 3,
    };


    for (int i = 0; i < m_plane->verticies.size(); ++i)
    {
        m_plane->verticies[i].normal[0] = floatToChar(0.0f);
        m_plane->verticies[i].normal[1] = floatToChar(0.0f);
        m_plane->verticies[i].normal[2] = floatToChar(1.0f);
        m_plane->verticies[i].normal[3] = floatToChar(0.0f);
    }

    return m_plane;
}
