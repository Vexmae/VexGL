#version 430 core

layout(location = 0) in vec3 _vertexPosition;
layout(location = 1) in vec2 _textureCoordinates;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TextureCoordinates;

void main(){
    gl_Position = projection * view * model * vec4(_vertexPosition,1.0f);
    TextureCoordinates = _textureCoordinates;
}