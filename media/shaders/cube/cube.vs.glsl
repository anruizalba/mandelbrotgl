#version 420 core                                                 
layout (location = 0) in vec4 position; 
                                                                  
out VS_OUT
{                                                                 
    float offset_x;                                                   
    float offset_y;                                                   
    float zoom;                                                   
} vs_out;

uniform mat4 mv_matrix;                                           
uniform mat4 proj_matrix;                                         
uniform float offset_x;
uniform float offset_y;
uniform float zoom;
                                                                  
void main(void)                                                   
{                                                                 
    gl_Position = proj_matrix * mv_matrix * position;             
    vs_out.offset_x = offset_x;
    vs_out.offset_y = offset_y;
    vs_out.zoom = zoom;
}
