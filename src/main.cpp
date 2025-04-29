#include "raylib.h"
#include "entity.h"
#include "world.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 800, "fysix ngin");

    World world({0, 980.0f});

    /**for (int x = 0; x<20; x++){
    	world.addEntity(Entity(
    		2.0f, {400+float(x*10), 400}, STATIC_BODY));
    }**/
  
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            world.addEntity(Entity(1.0f, mousePos, RIGID_BODY));
        }
        else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        	Vector2 mousePos = GetMousePosition();
            world.addEntity(Entity(1.0f, mousePos, STATIC_BODY));
        }
        world.update(dt);

        BeginDrawing();
            ClearBackground((Color){15,2,26});
            world.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
