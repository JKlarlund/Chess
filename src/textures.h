#include <iostream>

#include <GLFW/glfw3.h>

#include <glad/glad.h>
#include <dependencies/textures/stb_image.h>

#ifndef textures_h
#define textures_h

class Texture{
    
    public:
        unsigned int texture;
        int textureWidth, textureHeight, nrChannels;

        Texture(const char * filename){
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            unsigned char *data = stbi_load(filename, &textureWidth, &textureHeight, &nrChannels, 0);
            
            if (data){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else{
                std::cout << "Couldn't load " << filename;
            }

            stbi_image_free(data);

        }
};


#endif