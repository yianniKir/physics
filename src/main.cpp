#include "physics.h"


#include "shader.h"
#include "sprite.h"
#include "object.h"

glm::vec2 DEFAULTSIZE(0.1f,0.1f);
double cursorXPos = 0.0;
double cursorYPos = 0.0;
bool spawnObj = false;
bool wkey =false;

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

bool checkCollision(Object &obj1, Object &obj2){
    //position is in center
    glm::vec2 obj1Pos = obj1.particle.posNDC();
    glm::vec2 obj2Pos = obj2.particle.posNDC();

    bool colX = obj1Pos.x + obj1.size.x >= obj2Pos.x && obj2Pos.x + obj2.size.x >= obj1Pos.x;
    bool colY = obj1Pos.y + obj1.size.y >= obj2Pos.y && obj2Pos.y + obj2.size.y >= obj1Pos.y;

    return colX && colY;

}   

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

   std::vector<Object> objs;

   
    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    int d = 0;
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
            objs.push_back(Object(square, glm::vec2(cursorXPos*SCRADJUST,-cursorYPos*SCRADJUST),DEFAULTSIZE, glm::vec3(1.0f,1.0f,0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
            //objs[d].particle.acceleration.y = -9.81f;
            d++;

        }

        if(wkey){
            wkey = false;
            objs[d-1].particle.addForce(glm::vec2(0.0f, 5000.0f));
        }


        std::vector<uint> indicesToRemove;

        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        for (uint i = 0; i < objs.size(); ++i) {
            for (uint j = i + 1; j < objs.size(); ++j) {
                if (checkCollision(objs[i], objs[j])) {
                    indicesToRemove.push_back(i);
                    indicesToRemove.push_back(j);
                }
            }
        }

        std::sort(indicesToRemove.begin(), indicesToRemove.end()); // Sort indices
        indicesToRemove.erase(std::unique(indicesToRemove.begin(), indicesToRemove.end()), indicesToRemove.end()); // Remove duplicates
        for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it) {
            objs.erase(objs.begin() + *it); // Erase objects from the vector
        }
        
        for (auto it = objs.begin(); it != objs.end(); ++it) {
            //(*it).particle.addForce(glm::vec2(0.0f,-49.0f));
            (*it).particle.integrate(deltaTime);
            
            //std::cout << (*it).particle.acceleration.y << std::endl;
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
    if(key == GLFW_KEY_W && action == GLFW_PRESS)
        wkey = true;

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