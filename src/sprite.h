#ifndef SPRITE_H
#define SPRITE_H

#include "physics.h"

#include "shader.h"

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

#endif