/// overlay.vert
/// The trivial vertex shader

uniform mat4 prmtx;

void main(void)
{
    gl_Position = prmtx * gl_Vertex;
}
