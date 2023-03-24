#ifndef SHADER_CLASS_H
#define sHADER_CLASS_H

#include <GL/glew.h>
#include<string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contets(const char* filename);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* vertexFIle, const char* fragmentFile);

        void Activate();
        void Delete();
};
#endif