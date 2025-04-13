#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D t1;

void main() {
    FragColor = texture(t1, TexCoord)
}
