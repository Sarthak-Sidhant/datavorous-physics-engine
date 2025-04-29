#include "raylib.h"
#include "entity.h"
#include "world.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 800, "fysix ngin");

    World world({0, 980.0f});

    world.addEntity(Entity(1.0f, {400, 100}));
    world.addEntity(Entity(2.0f, {200,  50}));

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            world.addEntity(Entity(1.0f, mousePos));
        }
        world.update(dt);

        BeginDrawing();
            ClearBackground(BLACK);
            world.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
