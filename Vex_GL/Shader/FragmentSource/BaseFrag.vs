R"(
#version 430 core

in vec4 UniColor;
in vec2 TexCoord;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

uniform float Opacity;

out vec4 FragColor;

void main() {
	FragColor = mix(texture(Texture0,TexCoord), texture(Texture1,TexCoord), texture(Texture1, TexCoord).a * Opacity);
}
)"