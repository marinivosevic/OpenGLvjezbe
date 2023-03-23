#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "pathconfig.h"

// [
#include "shader.h"
// ]

#include <fstream>
#include <sstream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "v02_000", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    glfwSwapInterval(2);

    glewExperimental = true;
    unsigned int err = glewInit();
    if(err != GLEW_OK) {std::cout << "error\n"; return -1;}

    std::cout << glGetString(GL_VERSION) << std::endl;

    float coords [] = {
        -0.5, -0.5, // 0
         0.5, -0.5, // 1
         0.5,  0.5, // 2
         -0.5, 0.5  // 3
    };

    unsigned int indices [] = {
      0, 1, 2,
      2, 3, 0
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof (float), coords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof (float), 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof (unsigned int), indices, GL_STATIC_DRAW);


    const std::string vs = shaders_folder + "v02_000_v.glsl";
    const std::string fs = shaders_folder + "v02_000_f.glsl";

    std::cout << "shaders folder: " << shaders_folder << std::endl;

    // [
    Shader my_shader({{GL_VERTEX_SHADER, vs}, {GL_FRAGMENT_SHADER, fs}});
    my_shader.bind();
    // ]

    float red = 0.f;
    float step = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if(red < 0.f || red > 1.f)
        {    step *= -1.; }
        red += step;

        glm::mat4 view = glm::mat4(1.);
        glm::mat4 projection = glm::mat4(1.);
        view = glm::translate(view, glm::vec3(0.,0., 1.5f));

        projection = glm::ortho(-10.f, 10.f, -10.f, 10.f, -10.f, 100.f);

        glm::mat4 transform = glm::mat4(1.);
        transform = glm::translate(transform, glm::vec3(0.5, -0.5, 0.));

        // [
        my_shader.setVec4("u_color", {red, 0.3, 0.2, 1.});
        my_shader.setMat4("view", view);
        my_shader.setMat4("projection", projection);
        my_shader.setMat4("transform", transform);
        // ]

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // crtanje drugog pravokutnika
        transform = glm::mat4(1.);
        transform = glm::translate(transform, glm::vec3(-0.5, 0.5, 0.));
        float scale_factor = std::sin(glfwGetTime());
        transform = glm::scale(transform, glm::vec3(scale_factor, scale_factor, scale_factor));

        my_shader.setMat4("transform", transform);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
