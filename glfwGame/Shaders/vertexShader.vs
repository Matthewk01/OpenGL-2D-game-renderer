#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TextCoord;

void main() {
        gl_Position =  projection * view * model * vec4(aPos.xy, 0.0, 1.0);
        ourColor = aColor;
        TextCoord = aTextCoord;
}