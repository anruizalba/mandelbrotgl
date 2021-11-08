#version 330 core
out vec4 color;                         

in COLOR_OUT
{
    vec4 color;
} color_in;
                                        
void main(void)                         
{
    color = color_in.color;
}
