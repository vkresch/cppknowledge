#pragma once
#include "camera.h"

class FPSCamera : public Camera {
    public:
        FPSCamera(float fov, float width, float height) : Camera(fov, width, height){
            up = glm::vec3(0.0f, 1.0f, 0.0f);
            yaw = -90.0f;
            pitch = 0.0f;
            onMouseMove(0.0f, 0.0f);
            update();
        }

        void onMouseMove(float xRel, float yRel){
            yaw += xRel * mouseSensetivity;
            pitch += yRel * mouseSensetivity;

            // Absicherung damit sich die Steuerung nicht flippt
            if(pitch > 89.0f){
                pitch = 89.0f;
            } else if(pitch < -89.0f){
                pitch = -89.0f;
            }

            glm::vec3 front;
            front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
            front.y = sin(glm::radians(pitch)) * sin(glm::radians(yaw));
            front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
            lookAt = glm::normalize(front);
            update();
        }

        void update() override {
            view = glm::lookAt(position, position+lookAt, up);
            viewProj = projection * view;
        }

        void moveFront(float amount){
            // The vec3 multiplication ignores the y axis so that the fps does not start to fly
            // this can be optionally removed
            translate(glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f) * lookAt) * amount);
            update();
        }

        void moveSideways(float amount){
            translate(glm::normalize(glm::cross(lookAt, up)) * amount);
            update();
        }

    protected:
        float yaw;
        float pitch;
        glm::vec3 lookAt;
        glm::vec3 up;
        const float mouseSensetivity = 0.3f;

};