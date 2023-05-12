#version 330 core

in vec2 UV;

out float color;

uniform sampler2D renderedTexture;

void main(){
    color = texture(renderedTexture, UV).x;
}