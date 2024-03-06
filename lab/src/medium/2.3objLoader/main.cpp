#include "ourmodel.h"

int main()
{
    GLFWWindowFactory myWindow(800, 600, "LearnOpenGL");
    RectangleModel rectangle(&myWindow);
    myWindow.run([&]()
                 {
                    rectangle.draw();

                     // Custom model updates and rendering logic here.
                     // For example:
                     // model->update();
                     // renderer->draw(model);
                 }); 

    return 0;
}
