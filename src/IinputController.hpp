#include <GLFW/glfw3.h>
#include "window.hpp"
#pragma
namespace TTe {
class IInputController {
    public:
    struct KeyMappings {
        int moveLeft = GLFW_KEY_A;
        int moveRight = GLFW_KEY_D;
        int moveForward = GLFW_KEY_W;
        int moveBackward = GLFW_KEY_S;
        int moveUp = GLFW_KEY_E;
        int moveDown = GLFW_KEY_Q;
        int lookLeft = GLFW_KEY_LEFT;
        int lookRight = GLFW_KEY_RIGHT;
        int lookUp = GLFW_KEY_UP;
        int lookDown = GLFW_KEY_DOWN;
        int space = GLFW_KEY_SPACE;
        int alt = GLFW_KEY_LEFT_ALT;
        int shift = GLFW_KEY_LEFT_SHIFT;
    };

    virtual void updateFromInput(Window* window, float dt) = 0;

    KeyMappings keys{};
};
}  // namespace TTe