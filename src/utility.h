#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace utility 
{
    int load_text_from_file(std::string &container, const char* path);
    glm::vec3 rotate_around_x(const glm::vec3& vector, float angle);
    glm::vec3 rotate_around_y(const glm::vec3& vector, float angle);
}