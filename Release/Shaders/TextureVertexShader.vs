#version 120

attribute vec4 _Position;
attribute vec2 _TexturePosition;
varying vec2 _TexPosition;

uniform mat4 mT;

void main(void) {
  gl_Position = mT*_Position;
  _TexPosition = _TexturePosition;
}