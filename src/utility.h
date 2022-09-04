#pragma once

#include <iostream>
#include <string>
#include <tuple>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace utility 
{
    std::tuple<std::string, bool> load_text_from_file(const std::string& path);
    glm::vec3 rotate_around_x(const glm::vec3& vector, float angle);
    glm::vec3 rotate_around_y(const glm::vec3& vector, float angle);
}