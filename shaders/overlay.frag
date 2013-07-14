/// triangles.frag
/// The trivial fragment shader

uniform vec3 u_col;

void main(void)
{
    gl_FragColor = vec4(u_col,1);
}