#version 330 core
                                                                  
                                                 
in vec4 position; 
//layout (location = 1) in vec4 position;

out COLOR_OUT
{
    vec4 color;
} color_out;
                                                                  
uniform mat4 mv_matrix;                                           
uniform mat4 proj_matrix;
uniform vec4 v_color;

void main(void)                                                   
{                                                                 
    gl_Position = proj_matrix * mv_matrix * position;
    color_out.color = v_color;
}
