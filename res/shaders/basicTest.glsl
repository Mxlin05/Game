#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;     // Vertex position
layout(location = 1) in vec3 aColor;   // Vertex color

out vec3 vColor;                       // Pass to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);     // Transform vertex position
    vColor = aColor;                   // Pass color along to fragment shader
}

#shader fragment
#version 330 core

in vec3 vColor;                        // Received from vertex shader

out vec4 FragColor;                    // Output fragment color

void main()
{
    FragColor = vec4(vColor, 1.0);     // Output the interpolated color
}