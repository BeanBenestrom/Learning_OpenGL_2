#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


enum CamDirection { FORWARD, BACKWARD, UP, DOWN, LEFT, RIGHT };


class Camera
{
private:
    glm::vec3 local_x_axis;
    glm::vec3 local_y_axis;
    glm::vec3 local_z_axis;

    glm::vec3 position;
    glm::vec2 rotation;

    float speed;
    float sensitivity;  // Measured in degrees

public:
    Camera(const glm::vec3& position, const glm::vec2& rotation, float speed, float sensitivity);
    ~Camera();

    void move(CamDirection direction, float deltaTime);
    void rotate(float offsetX, float offsetY);

    glm::vec3 inline get_position() { return position; }
    glm::vec2 inline get_rotation() { return rotation; }
};