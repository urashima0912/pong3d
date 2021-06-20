#include "palette.h"

/*********************************************************
 * Static functions declaration. 
*********************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

PONG void __updateUser(Palette_t *const);
PONG void __updateMachine(Palette_t *const);

#if defined(__cplusplus)
}
#endif


/*********************************************************
 * Public functions implementation. 
*********************************************************/
PONG Palette_t *createPalette(Vector3 position, Vector3 size, bool isMachine)
{
  Palette_t *palette = MemAlloc(sizeof(Palette_t));
  if (!palette)
  {
    TraceLog(LOG_ERROR, "Error to create a palette.");
    return NULL;
  }

  palette->position = position;
  palette->size = size;
  palette->isCollision = false;
  palette->isMachine = isMachine;
  palette->color = GRAY;

  #if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "The Palette_t has be created:");
    TraceLog(LOG_INFO, TextFormat("\tposition: {x: %f, y: %f, z: %f}", palette->position.x, palette->position.y, palette->position.z));
    TraceLog(LOG_INFO, TextFormat("\tsize:x: {%f, y: %f, z: %f}", palette->size.x, palette->size.y, palette->size.z));
    TraceLog(LOG_INFO, TextFormat("\tisCollision: %d", palette->isCollision));
    TraceLog(LOG_INFO, TextFormat("\tisMachine: %d", palette->isMachine));
    TraceLog(LOG_INFO, TextFormat("\tColor: {r: %u, g: %u, b: %u, a: %u}\n", palette->color.a, palette->color.g, palette->color.b, palette->color.a));
  #endif

  return palette;
}
PONG void updatePalette(Palette_t *const palette)
{
  if (palette->isMachine) __updateMachine(palette);
  else __updateUser(palette);
}
PONG void drawPalette(const Palette_t *const palette)
{
  DrawCubeV(
    palette->position,
    palette->size,
    palette->color
  );
  DrawCubeWiresV(
    palette->position,
    palette->size,
    BLACK
  );
}
PONG void deletePalette(Palette_t **ptrPalette)
{
  if (*ptrPalette)
  {
    Palette_t *palette = *ptrPalette;
    MemFree(palette);
    palette = NULL;
    (*ptrPalette) = NULL;

    #if defined(PONG_DEBUG)
      TraceLog(LOG_INFO, "The Palette_t has be deleted:");
    #endif
  } 
}


/*********************************************************
 * Static functions implementation. 
*********************************************************/
PONG void __updateUser(Palette_t *const palette)
{
  const Vector3 position = palette->position;
  const int32_t limit = (GRID_HEIGHT / 2) - 2;
  if (position.z > -limit && IsKeyPressed(KEY_W)) {
    palette->position.z -= 1;
  } else if (position.z <= limit && IsKeyPressed(KEY_S)) {
    palette->position.z += 1;
  }
}
PONG void __updateMachine(Palette_t *const palette)
{
  // TODO.
}