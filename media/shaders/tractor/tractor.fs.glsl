#version 330 core
//layout (binding = 0) uniform sampler2D tex_object;
out vec4 color;                         
                                        
in VS_OUT                               
{                                       
    vec4 color;                         
} fs_in;                                
                                        
void main(void)                         
{                                       
    color = fs_in.color;                
}                                       
