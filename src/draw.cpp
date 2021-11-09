#include "draw.hpp"
#include "cube.h"
#include "GLFW/glfw3.h"
#include "GL/gl3w.h"
#include "math.h"
#include <iostream>

GLfloat graph[400];

Draw::Draw() :
        vao(),
        buffers(),
        program(0),
        program2(0),
        h_init(-10.0f),
        proj_location(0),
        color_location(0),
        offset_x_location(0),
        offset_y_location(0),
        zoom_location(0),
        object(0),
        mv_location(0),
        mv_location2(0),
        proj_location2(0),
        itera(4),
        index(0),
	delta(0.0f)
{
    for (int i =0; i <400; i+=4)
    {
        graph[i]= float(i)* 0.01 ;
        graph[i + 1]= float(i)* 0.01;
        graph[i + 2]= -0.5;
        graph[i + 3]= 1.0;
    }
}

Draw::~Draw() {
    glDeleteVertexArrays(2, vao);
    glDeleteProgram(program);
    glDeleteProgram(program2);
}

void Draw::makeBuffers(GLFWwindow *window) {

    glGenVertexArrays(3, vao);


   // glEnable(GL_CULL_FACE);
   // glFrontFace(GL_CW);

    //glBindVertexArray(vao[1]);
    glGenBuffers(7, buffers);


    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL); // 
    glEnableVertexAttribArray(0);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices),
                 vertices,
                 GL_STATIC_DRAW);


 //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
 //   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


}

void Draw::makeDraw(drawArray *state, bool wireframe, bool enable_up, float height, float windowWidth, float windowHeight,
                    GLFWwindow *window) {

    glfwMakeContextCurrent(window);
    glUseProgram(program);

    glBindVertexArray(vao[0]);
//    glCullFace(GL_FRONT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    vmath::mat4 proj_matrix = vmath::perspective(40.0f,
                                                 windowWidth / windowHeight,
                                                 0.1f, 1000.0f);
    vmath::mat4 mv_matrix = vmath::Tmat4<float> (
                        vmath::translate(-0.0f, 0.0f, -0.5f)
                    );


    float offset_x = height;

    glUniform1f(offset_x_location, state->JValue[0]);
    glUniform1f(offset_y_location, state->JValue[1]);
    glUniform1f(zoom_location, state->JValue[2]);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);


//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(GLint));


    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Draw::load_shaders(const std::string& shaders_path) {
    if (program)
        glDeleteProgram(program);


    GLuint vs = a2k::shader::load(((std::string)(shaders_path+"/cube/cube.vs.glsl")).c_str(), GL_VERTEX_SHADER);
    GLuint fs = a2k::shader::load(((std::string)(shaders_path+"/cube/cube.fs.glsl")).c_str(), GL_FRAGMENT_SHADER);


    program = glCreateProgram();

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    mv_location = glGetUniformLocation(program, "mv_matrix");
    proj_location = glGetUniformLocation(program, "proj_matrix");
    offset_x_location = glGetUniformLocation(program, "offset_x");
    offset_y_location = glGetUniformLocation(program, "offset_y");
    zoom_location = glGetUniformLocation(program, "zoom");
}
