#version 140

in vec4 vPosition;
//in vec4 bPosition
in vec3 vColor;
//in vec3 bColor;
out vec4 color;
// important to use the same variable names

void
main()
{
    gl_Position = vPosition;
    color = vec4(vColor, 1.0);
    //color = vec4(0.0,0.0,0.0,1.0); // black

}
