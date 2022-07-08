#include <fstream>
// #include <iostream>

#include "utility.h"


namespace utility 
{
    int load_text_from_file(std::string &container, const char* path)
    {
        std::ifstream file;
        file.open(path, std::ios::in);

        if (!file.is_open()) { return 0; }

        container = "";         // Makes sure that container is empty
        std::string snippet;    // Line of text     
        
        while (std::getline(file, snippet)) 
        { 
            container += snippet + "\n";
        }
        file.close();
        return 1;
    }

    glm::vec3 rotate_around_x(const glm::vec3& vector, float angle)
    {
        float radians = -glm::radians(angle);
        return glm::vec3(vector.x, cos(radians) * vector.y + sin(radians) * vector.z, -sin(radians) * vector.y + cos(radians) * vector.z);
    }

    glm::vec3 rotate_around_y(const glm::vec3& vector, float angle)
    {
        float radians = glm::radians(angle);
        return glm::vec3(cos(radians) * vector.x + sin(radians) * vector.z, vector.y, -sin(radians) * vector.x + cos(radians) * vector.z);
    }
}