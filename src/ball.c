#include "ball.h"

const float SPEED = 0.25;

/*********************************************************
 * Static functions declaration. 
*********************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

PONG bool __initializeBall(Ball_t *const ball);
PONG bool __checkCollision(const Ball_t *const ball, const Palette_t *const palette);

#if defined(__cplusplus)
}
#endif


/*********************************************************
 * Public functions implementation. 
*********************************************************/
PONG Ball_t *createBall(void)
{
  Ball_t *ball = MemAlloc(sizeof(Ball_t));
  if (!ball) {
    TraceLog(LOG_ERROR, "Error to create a Ball_t.");
    return NULL;
  }

  ball->size = (Vector3) {0.5f, 0.5f, 0.5f};
  ball->color = RED;
  __initializeBall(ball);

  #if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "The Ball_t has been created:");
    TraceLog(LOG_INFO, TextFormat("\tposition: {x: %f, y: %f, z: %f}", ball->position.x, ball->position.y, ball->position.z));
    TraceLog(LOG_INFO, TextFormat("\tsize:x: {%f, y: %f, z: %f}", ball->size.x, ball->size.y, ball->size.z));
    TraceLog(LOG_INFO, TextFormat("\tColor: {r: %u, g: %u, b: %u, a: %u}\n", ball->color.a, ball->color.g, ball->color.b, ball->color.a));
  #endif

  return ball;
}
PONG void updateBall(Ball_t *const ball, const Palette_t *const palette1, const Palette_t *const palette2)
{
  const float diff = GRID_WIDTH/2 + 4;
  if (ball->position.x < -diff || ball->position.x > diff)
  {
    __initializeBall(ball);
  } 
  else
  {
    if (ball->position.z < -GRID_HEIGHT/2 || ball->position.z > GRID_HEIGHT/2)
    {
      ball->velocity.z *= -1;
    }
    else
    {
      const bool collision = __checkCollision(ball, palette1) || __checkCollision(ball, palette2);
      if (collision) {
        ball->velocity.x *= -1;
        const int32_t direction = GetRandomValue(-1, 1);
        ball->velocity.z = direction * SPEED;
      };
    }

    ball->position.x += ball->velocity.x;
    ball->position.z += ball->velocity.z;
  }
}
PONG void drawBall(const Ball_t *const ball)
{
  DrawCubeV(
    ball->position,
    ball->size,
    ball->color
  );
  DrawCubeWiresV(
    ball->position,
    ball->size,
    BLACK
  );
}
PONG void deleteBall(Ball_t **ptrBall)
{
  if ((*ptrBall))
  {
    MemFree((*ptrBall));
    ptrBall = NULL;

    #if defined(PONG_DEBUG)
      TraceLog(LOG_INFO, "The Ball_t has been deleted:");
    #endif
  }
}


/*********************************************************
 * Static functions implementation. 
*********************************************************/
PONG bool __initializeBall(Ball_t *const ball)
{
  const int32_t direction = GetRandomValue(0, 1);
  ball->position = (Vector3) {0};
  ball->velocity = (Vector3) {0};
  ball->velocity.x = (direction == 0) ? -SPEED : SPEED;
}
PONG bool __checkCollision(const Ball_t *const ball, const Palette_t *const palette) {
  BoundingBox ballBox = (BoundingBox) {
    (Vector3){
      ball->position.x - (ball->size.x / 2),
      ball->position.y - (ball->size.y / 2),
      ball->position.z - (ball->size.z / 2),
    },
    (Vector3){
      ball->position.x + (ball->size.x / 2),
      ball->position.y + (ball->size.y / 2),
      ball->position.z + (ball->size.z / 2),
    }
  };
  BoundingBox paletteBox = (BoundingBox) {
    (Vector3){
      palette->position.x - (palette->size.x / 2),
      palette->position.y - (palette->size.y / 2),
      palette->position.z - (palette->size.z / 2),
    },
    (Vector3){
      palette->position.x + (palette->size.x / 2),
      palette->position.y + (palette->size.y / 2),
      palette->position.z + (palette->size.z / 2),
    }
  };

  return CheckCollisionBoxes(ballBox, paletteBox);
}
