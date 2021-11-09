#ifndef DRAW_H
#define DRAW_H


#include <string>
#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "a2kktx.h"
#include "shader.h"
#include "vmath.h"
#include "Myst.hpp"

struct drawArray{
        int index;
        float JValue[4];
    };

class Draw
{
  private:


    GLuint          vao[3];
    GLuint          buffers[7];

    GLuint          program;
    GLuint          program2;
    float           h_init;

    GLint           proj_location;
    GLint           color_location;
    GLint           offset_x_location;
    GLint           offset_y_location;
    GLint           zoom_location;
    GLint           object;
    GLint           object2;
    GLint           mv_location;
    GLint           mv_location2;
    GLint           proj_location2;

    int itera;
    int index;
    float delta;



  public:
    Draw();
    ~Draw();
    void makeBuffers(GLFWwindow *window);
    void makeDraw(drawArray *state, bool wireframe, bool enable_up, float height, float windowWidth, float windowHeight
                  , GLFWwindow *window);
    void load_shaders(const std::string& shaders_path);
};

#endif
