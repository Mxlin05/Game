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
uniform sampler2D uTexture;
uniform vec2 uOffset;
uniform vec2 uScale;
uniform bool isSelected;
uniform bool isHovered;

out vec4 FragColor;

void main() {
    vec2 uv = TexCoord * uScale + uOffset;
    vec4 texColor = texture(uTexture, uv);

    if (isHovered) {
        FragColor = vec4(1.0, 1.0, 0.0, 1.0); // Bright yellow highlight
    } else if (isSelected) {
        FragColor = vec4(0.7, 0.7, 0.0, 1.0); // Darker yellow
    } else {
        FragColor = texColor;
    }
}