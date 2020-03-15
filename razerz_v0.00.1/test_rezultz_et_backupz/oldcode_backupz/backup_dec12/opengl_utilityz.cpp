
#include "opengl_utilityz.hpp"






void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    screen_beenresized = true;

}



void APIENTRY GLAPIENTRY glDebugOutput(GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar *message,
                         const void *userParam)
{
  //ignore non-significant error/warning codes
 if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

 std::cout << "---------------" << std::endl;
 std::cout << "Debug message (" << id << "): " <<  message << std::endl;

 switch (source)
 {
     case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
     case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
     case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
     case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
     case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
     case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
 } std::cout << std::endl;

 switch (type)
 {
     case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
     case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
     case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
     case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
     case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
     case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
     case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
     case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
     case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
 } std::cout << std::endl;

 switch (severity)
 {
     case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
     case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
     case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
     case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
 } std::cout << std::endl;
 std::cout << std::endl;
}

int opengl_context_settup()
{
  glewExperimental = GL_TRUE;
  //launch gluitInit
  if (!glfwInit())
{
  std::cout << "flfwinit faild :()\n";
  return -1;
}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
return 0;
}

int run_opengl_setup(GLFWwindow* out_window)
{

if(!out_window)
{
  glfwTerminate();
  std::cout <<"windowfailureload\n";
  return -3;
}

glfwMakeContextCurrent(out_window);
glfwSetFramebufferSizeCallback(out_window, framebuffer_size_callback);

GLenum glewErr = glewInit();
std::cout << "glew_code::" << glewErr <<'\n' <<'\n';
glViewport( 0, 0, MAIN_SCREEN_WIDTH, MAIN_SCREEN_HIGHT );
GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
{
std::cout <<"debug iniaizled\n";
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
glDebugMessageCallback(glDebugOutput, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}

  return 0;
}
