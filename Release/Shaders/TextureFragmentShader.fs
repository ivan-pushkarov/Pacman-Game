#version 120

varying vec2 _TexPosition;
uniform vec4 _Color;
uniform sampler2D _Texture;

void main(void) {
  gl_FragColor = vec4(1, 1, 1, texture2D(_Texture, _TexPosition).a) * _Color;
}