#version 330 core

out vec4 colour;

in vec2 TexCoords;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	colour = mix(texture(texture1, TexCoords), texture(texture2, TexCoords), 0.2);
}
