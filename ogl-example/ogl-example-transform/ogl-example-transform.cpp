#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <ogl/shader.h>
#include <ogl/program.h>
#include <ogl/vertexbuffer.h>
#include <ogl/indexbuffer.h>
#include <ogl/vertexarray.h>
#include <ogl/texture.h>

#include <ogl/loader.h>

#include <fmt/format.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // During init, enable debug output
  // glEnable(GL_DEBUG_OUTPUT);
  // glDebugMessageCallback(MessageCallback, 0);
  // TODO: make shader more concrete.

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      // positions          // colors           // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
  };

  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first Triangle
      1, 2, 3  // second Triangle
  };

  ogl::shader frag{GL_FRAGMENT_SHADER,
		   ogl::load_shader("res/shader/transform.fs")};
  ogl::shader vert{GL_VERTEX_SHADER,
		   ogl::load_shader("res/shader/transform.vs")};
  ogl::program shader{vert, frag};
  // TODO: improve how to set multiple uniforms without binding explicitly.
  shader.bind();
  shader.set("texture1", 0);
  shader.set("texture2", 1);
  shader.unbind();

  ogl::vertex_buffer vbo{vertices, sizeof(vertices)};
  ogl::vertex_attr pos{GL_FLOAT, 3, false};
  ogl::vertex_attr col{GL_FLOAT, 3, false};
  ogl::vertex_attr tex{GL_FLOAT, 2, false};

  ogl::index_buffer ibo{indices, sizeof(indices)};
  ogl::vertex_array vao{vbo, {pos, col, tex}, ibo};

  // TODO: improve how to load the texture.
  auto [w, h, f, t, d] = ogl::load_texture("res/image/container.jpg");
  ogl::texture image(w, h, f, t, d.get());

  std::tie(w, h, f, t, d) = ogl::load_texture("res/image/awesomeface.png");
  ogl::texture image2(w, h, f, t, d.get());

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // transform
    glm::mat4 trans = glm::mat4(1.0f);
    trans =
	glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0,
    // 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    // draw our first triangle
    shader.bind();
    shader.set("transform", trans);
    glActiveTexture(GL_TEXTURE0);
    image.bind();
    glActiveTexture(GL_TEXTURE0 + 1);
    image2.bind();
    vao.draw();

    // glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
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
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
