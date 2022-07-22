R"(
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float Xoffset;
uniform float Yoffset;
out vec4 UniColor;
out vec2 TexCoord;
void main() {
	gl_Position = vec4(aPos.x + Xoffset, aPos.y + Yoffset, aPos.z, 1.0);
	UniColor = vec4(aColor.xyz,1.0f);
	TexCoord = aTexCoord;
}
)"