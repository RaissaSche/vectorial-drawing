#version 330 core

layout ( location = 0 ) in vec3 vPosition;

out float zOut;

uniform mat4 model;
uniform mat4 ortho;

void main()
{
	zOut = vPosition.z;
	gl_Position = ortho * model * vec4(vPosition.x, vPosition.y, 0.0, 1.0);
}
