#ifndef __SHADER_H__
#define __SHADER_H__

namespace a2k
{

namespace shader
{

GLuint load(const char * filename,
            GLenum shader_type = GL_FRAGMENT_SHADER,
#ifdef _DEBUG
            bool check_errors = true);
#else
            bool check_errors = true);
#endif

}

namespace program
{

GLuint link_from_shaders(const GLuint * shaders,
                         int shader_count,
                         bool delete_shaders,
#ifdef _DEBUG
                         bool check_errors = true);
#else
                         bool check_errors = false);
#endif

}

}

#endif /* __SHADER_H__ */
