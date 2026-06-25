#include "Application.h"

int main()
{
    // Application owns the SFML window, scene creation, and engine loop startup.
    RogaliqueGame::Application app;
    app.run();
    return 0;
}
