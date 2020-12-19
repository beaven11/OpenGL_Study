#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define numVAOs 1

using namespace std;

GLuint renderingProgram;
// 顶点数组对象
GLuint vao[numVAOs];

void printShaderLog (GLuint shader);

GLuint createShaderProgram ();

void init (GLFWwindow *window);

void display (GLFWwindow *window, double currentTime);

int main ()
{
  if (!glfwInit ())
    {
      exit (EXIT_FAILURE);
    }
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow *window = glfwCreateWindow (600, 600, "Chapter2", NULL, NULL);
  glfwMakeContextCurrent (window);
  if (glewInit () != GLEW_OK)
    {
      exit (EXIT_FAILURE);
    }
  glfwSwapInterval (1);
  init (window);
  while (!glfwWindowShouldClose (window))
    {
      display (window, glfwGetTime ());
      glfwSwapBuffers (window);
      glfwPollEvents ();
    }

  glfwDestroyWindow (window);
  glfwTerminate ();
  exit (EXIT_SUCCESS);
}

GLuint createShaderProgram ()
{
  const char *vshaderSource =
      "#version 430\n"
      "void main(void)\n"
      "{gl_Position = vec4(0.0,0.0,0.0,1.0);}";

  const char *fshaderSource =
      "#version 430\n"
      "out vec4 color;\n"
      "void main(void)\n"
      "{ if(gl_FragCoord.x < 200) {color = vec4(1.0,0.0,0.0,1.0);} else { color = vec4(0.0,0.0,1.0,1.0);} }";

  // 创建着色器
  GLuint vShader = glCreateShader (GL_VERTEX_SHADER);
  GLuint fShader = glCreateShader (GL_FRAGMENT_SHADER);
  // GLSL代码载入
  glShaderSource (vShader, 1, &vshaderSource, NULL);
  glShaderSource (fShader, 1, &fshaderSource, NULL);
  // 着色器编译
  glCompileShader (vShader);
  glCompileShader (fShader);

  GLuint vfProgram = glCreateProgram ();
  glAttachShader (vfProgram, vShader);
  glAttachShader (vfProgram, fShader);
  glLinkProgram (vfProgram);
  return vfProgram;
}

void init (GLFWwindow *window)
{
  renderingProgram = createShaderProgram ();
  glGenVertexArrays (numVAOs, vao);
  glBindVertexArray (vao[0]);
}

void display (GLFWwindow *window, double currentTime)
{
  // 将程序载入OPENGL管线阶段,未运行着色器
  glUseProgram (renderingProgram);
  glPointSize (300.0f);
  // 绘制命令
  glDrawArrays (GL_POINTS, 0, 1);
}

void printShaderLog (GLuint shader)
{
  int len = 0;
  int chWrittn = 0;
  char *log;
  glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &len);
  if (len > 0)
    {
      log = (char *) (malloc (len));
      glGetShaderInfoLog (shader, len, &chWrittn, log);
      cout << "Shader info log:" << log << endl;
      free (log);
    }
}