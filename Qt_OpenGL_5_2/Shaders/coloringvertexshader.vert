#version 330
//Shader do pozycjonowania obiektów, używa colorfragmentshader do kolorowania
//Partner: coloringfragmentshader

uniform mat4 mvpMatrix;

in vec4 vertex;
in vec4 color;

out vec4 varyingColor;

void main(void)
{
    varyingColor = color;
    gl_Position = mvpMatrix * vertex;
}
