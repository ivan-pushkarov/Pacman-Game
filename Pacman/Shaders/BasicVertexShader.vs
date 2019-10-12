#version 120

attribute vec4 _Color;
attribute vec4 _Position;

uniform mat4 mT;

void main()
{
	gl_FrontColor = _Color;
	gl_Position = mT*_Position;
}