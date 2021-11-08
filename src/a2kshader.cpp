
#define _CRT_SECURE_NO_WARNINGS 1

#include "GL/gl3w.h"

#include <cstdio>

namespace a2k
{

namespace shader
{

extern
GLuint load(const char * filename, GLenum shader_type, bool check_errors)
{
    GLuint result = 0;
    FILE * fp;
    size_t filesize;
    char * data;

    fp = fopen(filename, "rb");

    if (!fp)
    {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    data = new char [filesize + 1];

    if (!data)
        goto fail_data_alloc;

    fread(data, 1, filesize, fp);
    data[filesize] = 0;
    fclose(fp);

    result = glCreateShader(shader_type);

    if (!result)
        goto fail_shader_alloc;

    glShaderSource(result, 1, &data, NULL);

    delete [] data;

    glCompileShader(result);

    if (check_errors)
    {
        GLint status = 0;
        glGetShaderiv(result, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            char buffer[4096];
            glGetShaderInfoLog(result, 4096, NULL, buffer);

            fprintf(stderr, "%s: %s\n", filename, buffer);

            goto fail_compile_shader;
        }
    }

    return result;

fail_compile_shader:
    glDeleteShader(result);

fail_shader_alloc:;
fail_data_alloc:
    return result;
}

}

namespace program
{

GLuint link_from_shaders(const GLuint * shaders,
                         int shader_count,
                         bool delete_shaders,
                         bool check_errors)
{
    int i;

    GLuint program;

    program = glCreateProgram();

    for (i = 0; i < shader_count; i++)
    {
        glAttachShader(program, shaders[i]);
    }

    glLinkProgram(program);

    if (check_errors)
    {
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        if (!status)
        {
            char buffer[4096];
            glGetProgramInfoLog(program, 4096, NULL, buffer);
#ifdef _WIN32
            OutputDebugStringA(buffer);
            OutputDebugStringA("\n");
#endif
            glDeleteProgram(program);
            return 0;
        }
    }

    if (delete_shaders)
    {
        for (i = 0; i < shader_count; i++)
        {
            glDeleteShader(shaders[i]);
        }
    }

    return program;
}

}

}
