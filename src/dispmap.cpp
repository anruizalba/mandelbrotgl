#include "dispmap.hpp"
#include <stdio.h>

#include <GL/glext.h>

/** Base Path for Shaders files */
std::string dispmap::ShadersPath_ = ".";

dispmap * dispmap::instance = 0;

int sb6IsExtensionSupported(const char * extname)
{
    GLint numExtensions;
    GLint i;

    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for (i = 0; i < numExtensions; i++)
    {
        const GLubyte * e = glGetStringi(GL_EXTENSIONS, i);
        if (!strcmp((const char *)e, extname))
        {
            return 1;
        }
    }

    return 0;
}


dispmap::dispmap() :
        info(),
        enable_up(false),
        height(0.0f),
        wireframe(false)
{

}

dispmap::~dispmap()
{
}

/**
 * Set base Path for Shaders files
 * @param path   Directory that contains shaders files
 */
void dispmap::setShadersPath(const std::string& path)
{
    ShadersPath_ = path;
}

dispmap* dispmap::getInstance()
{
    if (instance == 0)
    {
        instance = new dispmap();
    }

    return instance;
}

void dispmap::init()
{

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }


    static const char title[] = "farming simulator";
    memcpy(info.title, title, sizeof(title));

    info.windowWidth = 800;
    info.windowHeight = 600;

    info.majorVersion = 3;
    info.minorVersion = 3;

    info.samples = 0;
    info.flags.all = 0;
    info.flags.cursor = 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minorVersion);

//    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
//
#ifndef _DEBUG
            if (info.flags.debug)
#endif /* _DEBUG */
            {
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
            }

    if (info.flags.robust) {
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
    }
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, info.samples);
    glfwWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);

    window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title,
                              info.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open window\n");
        return;
    }





    glfwSetWindowSizeCallback(window, glfw_onResize);
    glfwSetKeyCallback(window, glfw_onKey);
    glfwSetMouseButtonCallback(window, glfw_onMouseButton);
    glfwSetCursorPosCallback(window, glfw_onMouseMove);
    glfwSetScrollCallback(window, glfw_onMouseWheel);
    if (!info.flags.cursor) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    gl3wInit();


    

  //  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
   // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glfwMakeContextCurrent(window);
    startup();
/*    glViewport(0, 0, info.windowWidth, info.windowHeight);

    static const GLfloat black[] = {0.7f, 0.9f, 0.44f, 1.0f};
    static const GLfloat one = 1.0f;

    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);
    state[0]=0.0f;
    state[1]=0.0f;

    draw.makeDraw(this->state, wireframe, enable_up, height, (float)info.windowWidth, (float)info.windowHeight, window);

    glfwSwapBuffers(window);

    glfwPollEvents(); */
}

void dispmap::startup()
{
    draw.load_shaders(ShadersPath_);
    draw.makeBuffers(window);
}

void dispmap::render(drawArray* state)
{

    static const GLfloat black[] = {0.7f, 0.9f, 0.44f, 1.0f};
    static const GLfloat one = 1.0f;

    
    glfwMakeContextCurrent(window);

    glViewport(0, 0, info.windowWidth, info.windowHeight);
    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);


  //  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
   // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);


    draw.makeDraw(state, wireframe, enable_up, height, (float)info.windowWidth, (float)info.windowHeight, window);

    glfwSwapBuffers(window);
//    glfwGetKey(window, GLFW_KEY_ESCAPE);
//    glfwWindowShouldClose(window);
    glfwPollEvents();

}


void dispmap::shutdown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}



void APIENTRY dispmap::debug_callback(GLenum source,
                                               GLenum type,
                                               GLuint id,
                                               GLenum severity,
                                               GLsizei length,
                                               const GLchar* message,
                                               GLvoid* userParam)
{
    reinterpret_cast<dispmap *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
}


void dispmap::onKey(int key, int action) {

    if (action == 1) {
        switch (key) {
            case GLFW_KEY_KP_ADD:
                break;
            case GLFW_KEY_KP_SUBTRACT:
                break;
            case 'F':
                break;
            case 'W':
                break;
            case 'P':
                break;
            case 'J':
                break;
            case 'K':
                break;
            case 'D':
                height += 0.5f;
                break;
            case 'S':
                height -= 0.5f;
                break;
            default:
                break;
        };
    }
}
