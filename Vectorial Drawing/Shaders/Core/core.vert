#version 330 core

layout ( location = 0 ) in vec3 vPosition;


uniform mat4 model;
uniform mat4 ortho;

void main()
{
	gl_Position = ortho * model * vec4(vPosition, 1.0);
}
