#if !defined(PONG_PALETTE_H)
#define PONG_PALETTE_H
#include "../config.h"

#if defined(__cplusplus)
extern "C" {
#endif

PONG typedef struct Palette_t {
  Vector3 position;
  Vector3 size;
  Color color;
  bool isCollision; // TODO: I need to check it.
  bool isMachine;

} Palette_t;

PONG Palette_t *createPalette(Vector3 position, Vector3 size, bool isMachine);
PONG void updatePalette(Palette_t *const palette, const Vector3 ballPosition);
PONG void drawPalette(const Palette_t *const palette);
PONG void deletePalette(Palette_t **ptrPalette);

#if defined(__cplusplus)
}
#endif
#endif // PONG_PALETTE_H