#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <oen/oen.h>
#include <oen/materials/solid_color.h>
#include <oen/materials/textured.h>
#include <oen/meshes/cube.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

auto camera = std::make_shared<oen::spline_camera>();

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(
      GLFW_OPENGL_FORWARD_COMPAT,
      GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // input
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  auto mat =
      std::make_shared<oen::materials::textured>("res/image/container.jpg");
  auto mesh = std::make_shared<oen::meshes::cube>();
  auto tran =
      std::make_shared<oen::translation>(-55.0f, glm::vec3(1.0f, 0.0f, 0.0f));

  // entity
  auto cube = std::make_shared<oen::entity>(mat, mesh, tran);

  // entities
  std::vector<std::shared_ptr<oen::entity>> entities{cube};

  // uncomment this call to draw in wireframe
  // polygons.glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

  glEnable(GL_DEPTH_TEST);

  // render loop-- ---------
  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw our first triangle
    render(camera, entities);
    // glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    //
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released
// this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina
  // displays.
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  static bool firstMouse = true;
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top
  lastX = xpos;
  lastY = ypos;

  float sensitivity = 0.1f; // change this value to your liking
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  camera->set_yaw(camera->get_yaw() + xoffset);
  camera->set_pitch(camera->get_pitch() + yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera->set_fov(camera->get_fov() - yoffset);
}
