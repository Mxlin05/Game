#shader vertex
#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 TexCoord;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

in vec2 TexCoord;
uniform vec4 uColor;

out vec4 FragColor;

void main() {
    FragColor = uColor;
}
