R"(
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 UniColor;
out vec2 TexCoord;
void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	UniColor = vec4(aColor.xyz,1.0f);
	TexCoord = aTexCoord;
}
)"