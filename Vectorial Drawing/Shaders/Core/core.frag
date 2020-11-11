#version 330 core

out vec4 color;
in float zOut;

void main(){
	color = vec4(zOut, zOut, 1.0, 1.0);
}