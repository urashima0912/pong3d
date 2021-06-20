#include "config.h"
#include "src/palette.h"

void DraRectGrid(int width, int height, float spacing);

int main(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SCREEN_TITLE
  );

  HideCursor();

  Camera camera = {0};
  camera.position = (Vector3){0.0f, (float)GRID_WIDTH - 5.0f, 15.0f};
  camera.target = (Vector3){0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  bool isPerspective = true;

  const float palettePosZ = (GRID_WIDTH / 2.0f) - 0.5f;

  Palette_t *player = createPalette(
    (Vector3){-palettePosZ, 0.0f, 0.5f},
    (Vector3){1.0f, 1.0f, 3.0f},
    false
  );
  if (!player) {
    CloseWindow();
    return 1;
  }

  Palette_t *enemy = createPalette(
    (Vector3){palettePosZ, 0.0f, 0.5f},
    (Vector3){1.0f, 1.0f, 3.0f},
    true
  );
  if (!player) {
    deletePalette(&player);
    CloseWindow();
    return 1;
  };

  SetTargetFPS(FPS);
  while (!WindowShouldClose())
  {

    if (IsKeyPressed(KEY_F1))
    {
      if (isPerspective)
      {
        camera.position = (Vector3){0.0f, (float)GRID_WIDTH + 10, 0.000001f};
        camera.projection = CAMERA_ORTHOGRAPHIC;
        camera.fovy = (float)GRID_WIDTH;
        isPerspective = false;
      }
      else 
      {
        camera.position = (Vector3){0.0f, (float)GRID_WIDTH - 5.0f, 15.0f};
        camera.projection = CAMERA_PERSPECTIVE;
        camera.fovy = 45.0f;
        isPerspective = true;
      }
    }

    updatePalette(player);
    updatePalette(enemy);
    BeginDrawing();
    ClearBackground(BLACK);
      BeginMode3D(camera);
        drawPalette(player);
        drawPalette(enemy);
        DraRectGrid(GRID_WIDTH, GRID_HEIGHT, 1.0f);

      EndMode3D();
      DrawFPS(10, 10);
    EndDrawing();
  }
  deletePalette(&player);
  deletePalette(&enemy);
  CloseWindow();

  return 0;
}


void DraRectGrid(int width, int height, float spacing)
{
    int halfWidth = width/2;
    int halfheight = height/2;
    rlCheckRenderBatchLimit((width + height)*4);

    rlBegin(RL_LINES);
      for (int i = -halfWidth; i <= halfWidth; i++)
      {
        if (i == 0)
        {
          rlColor3f(0.5f, 0.5f, 0.5f);
          rlColor3f(0.5f, 0.5f, 0.5f);
          rlColor3f(0.5f, 0.5f, 0.5f);
          rlColor3f(0.5f, 0.5f, 0.5f);
        }
        else
        {
          rlColor3f(0.75f, 0.75f, 0.75f);
          rlColor3f(0.75f, 0.75f, 0.75f);
          rlColor3f(0.75f, 0.75f, 0.75f);
          rlColor3f(0.75f, 0.75f, 0.75f);
        }

        rlVertex3f((float)i*spacing, 0.0f, (float)-halfheight*spacing);
        rlVertex3f((float)i*spacing, 0.0f, (float)halfheight*spacing);
      }
      for (int i = -halfheight; i <= halfheight; i++)
      {
        if (i == 0)
        {
          rlColor3f(0.5f, 0.5f, 0.5f);
          rlColor3f(0.5f, 0.5f, 0.5f);
          rlColor3f(0.5f, 0.5f, 0.5f);
          rlColor3f(0.5f, 0.5f, 0.5f);
        }
        else
        {
          rlColor3f(0.75f, 0.75f, 0.75f);
          rlColor3f(0.75f, 0.75f, 0.75f);
          rlColor3f(0.75f, 0.75f, 0.75f);
          rlColor3f(0.75f, 0.75f, 0.75f);
        }

        rlVertex3f((float)-halfWidth*spacing, 0.0f, (float)i*spacing);
        rlVertex3f((float)halfWidth*spacing, 0.0f, (float)i*spacing);
      }
    rlEnd();
}