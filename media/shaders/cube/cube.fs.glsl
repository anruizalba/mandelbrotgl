#version 420 core                       
in vec4 gl_FragCoord;
 
out vec4 frag_color;

in VS_OUT                               
{                                       
    float offset_x ;                         
    float offset_y ;                         
    float zoom ;                         
} fs_in;
 
#define MAX_ITERATIONS 500
 
int get_iterations()
{

    float zoom = fs_in.zoom;
    float center_x = fs_in.offset_x;
    float center_y = fs_in.offset_y;
    float real = ((gl_FragCoord.x / 1080.0 - 0.5) * zoom + center_x);
    float imag = ((gl_FragCoord.y / 1080.0 - 0.5) * zoom + center_y);
 
    int iterations = 0;
    float const_real = real;
    float const_imag = imag;
 
    while (iterations < MAX_ITERATIONS)
    {
        float tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        float dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iterations;
    }
    return iterations;
}


vec4 return_color()
{
    int iter = get_iterations();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragDepth = 0.0f;
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
 
    float iterations = float(iter)/ 50.0;    
//    return vec4(0.0f, 1.0f, 0.0f, 1.0f);
    return vec4(0.0f, iterations, 0.0f, 1.0f);
}
 
void main()
{
    frag_color = return_color();
}
