#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform int frameNum;
uniform float frameHorizSize;

void main()
{
	vec2 actualTexCoord = vec2(texCoord.x + frameNum * frameHorizSize, texCoord.y);
	FragColor = texture(texture1, actualTexCoord);
}



