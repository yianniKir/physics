#include "physics.h"


#include "shader.h"
#include "sprite.h"
#include "object.h"

glm::vec2 DEFAULTSIZE(0.1f,0.1f);
double cursorXPos = 0.0;
double cursorYPos = 0.0;
bool spawnObj = false;

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("src/shaders/vertexShader.glsl", "src/shaders/fragmentShader.glsl");
    Sprite square(shader);

    Object obj(square, glm::vec2(-80,80),DEFAULTSIZE, glm::vec3(1.0f,1.0f,0.0f));
    obj.particle.acceleration.y = -9.81f;
    obj.particle.velocity = glm::vec2(15.0f,0.0f);

   std::vector<Object> objs;

   
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
        if(spawnObj){
            spawnObj = false;
            objs.push_back(Object(square, glm::vec2(cursorXPos*SCRADJUST,-cursorYPos*SCRADJUST),DEFAULTSIZE, glm::vec3(1.0f,1.0f,0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, -9.81f)));
            
        }

        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (auto it = objs.begin(); it != objs.end(); ++it) {
            (*it).particle.integrate(deltaTime);
            (*it).color.g = (*it).particle.posNDC().g;
            (*it).draw();
        }
        
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    //ndc
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    {
       double xpos, ypos;
       //getting cursor position
       glfwGetCursorPos(window, &cursorXPos, &cursorYPos);
       cursorXPos = cursorXPos / SCREEN_WIDTH * 2 -1;
       cursorYPos = cursorYPos / SCREEN_HEIGHT * 2 - 1;
       spawnObj = true;
    }
}