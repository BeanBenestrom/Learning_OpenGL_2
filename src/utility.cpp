#include <fstream>
// #include <iostream>

#include "utility.h"


namespace utility 
{
    std::tuple<std::string, bool> load_text_from_file(const std::string& path)
    {
        std::ifstream file;
        file.open(path, std::ios::in);

        if (!file.is_open()) { 
            std::cerr << "[*] Could not open file!\n"
                      << "    PATH: " << path << "\n\n";
            return { "", false }; 
        }

        std::string container = "";         // Makes sure that container is empty
        std::string snippet;                // Line of text     
        
        while (std::getline(file, snippet)) 
        { 
            container += snippet + "\n";
        }
        file.close();
        return { container, true };
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