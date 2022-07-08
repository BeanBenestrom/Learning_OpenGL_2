#include <iostream>

#include "utility.h"
#include "camera.h"


Camera::Camera(const glm::vec3& position, const glm::vec2& rotation, float speed, float sensitivity)
{
    this->position = position;
    this->rotation = rotation;
    this->speed = speed;
    this->sensitivity = sensitivity;

    local_x_axis = utility::rotate_around_y(utility::rotate_around_x(glm::vec3(1.0f, 0.0f, 0.0f), rotation.x), rotation.y);
    local_y_axis = utility::rotate_around_y(utility::rotate_around_x(glm::vec3(0.0f, 1.0f, 0.0f), rotation.x), rotation.y);
    local_z_axis = utility::rotate_around_y(utility::rotate_around_x(glm::vec3(0.0f, 0.0f, 1.0f), rotation.x), rotation.y);
}

Camera::~Camera() { }

void Camera::move(CamDirection direction, float deltaTime)
{
    switch (direction)
    {
    case FORWARD:   position +=  local_z_axis * speed * deltaTime; break;
    case BACKWARD:  position += -local_z_axis * speed * deltaTime; break;
    case UP:        position +=  local_y_axis * speed * deltaTime; break;
    case DOWN:      position += -local_y_axis * speed * deltaTime; break;
    case LEFT:      position +=  local_x_axis * speed * deltaTime; break;
    case RIGHT:     position += -local_x_axis * speed * deltaTime; break;
    default:
        std::cout << "[*] Camera - Given movement direction is not defined\n" << "    direction: " << direction << "\n";
        break;
    }
}

void Camera::rotate(float offsetX, float offsetY)
{
    rotation += glm::vec2(-offsetY * sensitivity, -offsetX * sensitivity);

    local_x_axis = utility::rotate_around_y(utility::rotate_around_x(glm::vec3(1.0f, 0.0f, 0.0f), rotation.x), rotation.y);
    local_y_axis = utility::rotate_around_y(utility::rotate_around_x(glm::vec3(0.0f, 1.0f, 0.0f), rotation.x), rotation.y);
    local_z_axis = utility::rotate_around_y(utility::rotate_around_x(glm::vec3(0.0f, 0.0f, 1.0f), rotation.x), rotation.y);
}