#version 120

uniform mat4 mMVP;

varying vec2 texCoords;
varying vec4 colors;

attribute vec2 mVerts;
attribute vec2 mTexCoords;
attribute vec4 mColors;

void main()
{
    gl_Position = mMVP * vec4(mVerts, 0.0, 1.0);

    texCoords = vec2(mTexCoords.x, mTexCoords.y);
    colors = mColors;
}
