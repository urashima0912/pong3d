#if !defined(PONG_BALL_H)
#define PONG_BALL_H

#include "../config.h"
#include "palette.h"

#if defined(__cplusplus)
extern "C" {
#endif

PONG typedef struct Ball_t {
  Vector3 position;
  Vector3 size;
  Vector3 velocity;
  Color color;

} Ball_t;

PONG Ball_t *createBall(void);
PONG void updateBall(
  Ball_t *const ball,
  const Palette_t *const palette1,
  const Palette_t *const palette2
);
PONG void drawBall(const Ball_t *const);
PONG void deleteBall(Ball_t **);

#if defined(__cplusplus)
}
#endif

#endif // PONG_BALL_H