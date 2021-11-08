#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec4 colors;
out VS_OUT
{                                                                 
    vec4 color;                                                   
} vs_out;                                                         
                                                                  
uniform mat4 mv_matrix;                                           
uniform mat4 proj_matrix;                                         
uniform mat4 color_matrix;                                         
uniform int obj;
                                                                  
void main(void)
{
vec4 N;
vec4 c;

    gl_Position = proj_matrix * mv_matrix * position;
    N = color_matrix * normal * 0.4;
    c = vec4(0.33, 0.33, 0.33, 0.0) * dot(N, normalize(vec4(0.5, 1.0, 0.0, 0.0))) + vec4(0.0, 0.0, 0.0, 1.0);
    vs_out.color= vec4((c.x + c.y + c.z + 1)*colors[0], (c.x + c.y + c.z +1)* colors[1], (c.x + c.y + c.z +1)* colors[2], 1.0);
 //   vs_out.color= colors;


}                                                                
