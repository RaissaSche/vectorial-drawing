#version 330 core

layout ( location = 0 ) in vec2 vPosition;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 ortho;

void main()
{
	gl_Position = ortho * model * vec4(vPosition, 0.0, 1.0);
	
	TexCoord = vec2( texCoord.x, 1.0 - texCoord.y );
}