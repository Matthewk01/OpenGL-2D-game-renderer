#version 330 core

in vec3 ourColor;
in vec2 TextCoord;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main() {
        vec4 texColor = texture(ourTexture, TextCoord);
        if(texColor.a < 0.1){
                discard;
                }
        FragColor = texColor;
}