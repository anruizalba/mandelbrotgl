#ifndef DISPMAP_H 
#define DISPMAP_H 

#include <string.h>
#include "GL/gl3w.h"

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1

#include "GLFW/glfw3.h"
#include "a2kext.h"
#include "a2kktx.h"
#include "shader.h"
#include "draw.hpp"
#include "Myst.hpp"


struct APPINFO {
    char title[128];
    int windowWidth;
    int windowHeight;
    int majorVersion;
    int minorVersion;
    int samples;
    union {
        struct {
            unsigned int fullscreen  : 1;
            unsigned int vsync       : 1;
            unsigned int cursor      : 1;
            unsigned int stereo      : 1;
            unsigned int debug       : 1;
            unsigned int robust      : 1;
        };
        unsigned int all;
    } flags;
};


class dispmap {

protected:

    static void APIENTRY debug_callback(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar *message,
                                        GLvoid *userParam);

private:

    /** Base Path for Shaders files */
    static std::string ShadersPath_;

    APPINFO info;
    static dispmap* instance;
    static void glfw_onResize(GLFWwindow *window, int w, int h) {
        instance->onResize(w, h, window);
    }

    static void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
        instance->onKey(key, action);
    }

    static void glfw_onMouseButton(GLFWwindow *window, int button, int action, int mods) {
        instance->onMouseButton(button, action);
    }

    static void glfw_onMouseMove(GLFWwindow *window, double x, double y) {
        instance->onMouseMove(static_cast<int>(x), static_cast<int>(y));
    }

    static void glfw_onMouseWheel(GLFWwindow *window, double xoffset, double yoffset) {
        instance->onMouseWheel(static_cast<int>(yoffset));
    }

    GLFWwindow *window {nullptr};

    bool enable_up;
    float height;
    float zoom;
    float offset_x;
    float offset_y;
    bool wireframe;
    Draw draw;

public:
    dispmap();

    ~dispmap();

    /**
     * Set base Path for Shaders files
     * @param path   Directory that contains shaders files
     */
    static void setShadersPath(const std::string& path);

    static dispmap* getInstance();

    void init();

    void startup();

    void render(drawArray* state);

    void shutdown();

    void onResize(int w, int h, GLFWwindow *windowR) {

        info.windowWidth = w;
        info.windowHeight = h;

    }

    void onKey(int key, int action); 

    void onMouseButton(int button, int action) {

    }

    void onMouseMove(int x, int y) {

    }

    void onMouseWheel(int pos) {

    }

    void onDebugMessage(GLenum source,
                        GLenum type,
                        GLuint id,
                        GLenum severity,
                        GLsizei length,
                        const GLchar *message) {

        }

};

#endif

