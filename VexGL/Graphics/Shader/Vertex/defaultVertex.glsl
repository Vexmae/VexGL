R"(
#version 430 core

layout (location = 0) in vec3 VertexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position =  projection * view * model * vec4(VertexPos.x, VertexPos.y, VertexPos.z, 1.0f);
}
)"