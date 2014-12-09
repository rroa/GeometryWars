#version 120

varying vec2 texCoords;
varying vec4 colors;
uniform sampler2D tex;

void main()
{
    gl_FragColor = texture2D(tex, texCoords) * colors;
}
