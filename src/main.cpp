#include "vendors/glad/glad.h"
#include "vendors/GLFW/glfw3.h"
#include "vendors/glm/glm.hpp"
#include "vendors/glm/gtc/matrix_transform.hpp"
#include "vendors/glm/gtc/type_ptr.hpp"

#include <iostream>
#include "shader.h"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 800;

const unsigned int pixPerMeter = 10;

const unsigned int SCRADJUST = SCREEN_WIDTH / pixPerMeter;


glm::vec2 DEFAULTSIZE(0.1f,0.1f);


class Sprite{
    public:
        Sprite(Shader &shader) : shader(shader){
            
            initRenderData();
        }
        
uint VAO;
        void drawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color){
            shader.use();

            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, glm::vec3(position, 0.0f));
            model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
            model = glm::scale(model, glm::vec3(size, 1.0f));
            shader.setMat4("model", model);
            shader.setVec3("spriteColor", color);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

        }

    private:

        
        Shader shader;

        void initRenderData(){
            // configure VAO/VBO
            unsigned int VBO;
            float vertices[] = { 
                -0.5f,0.5f,
                -0.5f,-0.5f,
                0.5f, -0.5f,

                0.5f,-0.5f,
                0.5f,0.5f,
                -0.5f,0.5f
            };

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindVertexArray(VAO);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }    
};


class Object
{
    public:
        glm::vec2   position, size, velocity, acceleration;
        glm::vec3   color;
        float       rotation;

        

        Object(Sprite &sprite): sprite(sprite) {};
        Object(Sprite &sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec2 acceleration = glm::vec2(0.0f,0.0f)) : sprite(sprite), position(position), size(size), color(color), velocity(velocity){
            rotation = 0.0f;
        };

        void update(float dt){
            if((acceleration.x == 0.0f && acceleration.y == 0.0f)){
                std::cout << "dfhsah" << std::endl;
                velocity += acceleration * dt;
            }
                
            position += velocity * dt;
        }
    

        void draw(){
            sprite.drawSprite(glm::vec2(position.x/SCRADJUST, position.y/SCRADJUST), size, rotation, color);
        }
    private:
        Sprite sprite;
};

int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pysics Demo", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("src/shaders/vertexShader.glsl", "src/shaders/fragmentShader.glsl");
    Sprite square(shader);

    Object obj(square, glm::vec2(-80,80),DEFAULTSIZE, glm::vec3(0.0f,1.0f,0.0f));
    //obj.acceleration.y = -9.81f;
    obj.velocity = glm::vec2(5.0f,0.0f);


    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();


        
        // manage user input
        // -----------------
        

        obj.update(deltaTime);

        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        obj.draw();

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}