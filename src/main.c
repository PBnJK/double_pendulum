/* Double pendulum
 * Pedro B.
 */

#include <stdbool.h>
#include <stdlib.h>

#include <raylib.h>

#define SCR_W (640)
#define SCR_H (480)
#define SCR_TITLE "Double Pendulum!"

typedef struct _DoublePendulum {
	float ox, oy;
	float len_r1, len_r2;
	float mass_b1, mass_b2;
	float g;
	float angle_1, angle_2;
	float angv_1, angv_2;
	float x1, y1;
	float x2, y2;
} DoublePendulum;

void dp_init(DoublePendulum *dp) {
	dp->ox = 100.0;
	dp->oy = 20.0;

	dp->len_r1 = 100.0;
	dp->len_r2 = 50.0;

	dp->mass_b1 = 2.0;
	dp->mass_b2 = 4.0;

	dp->g = 9.8;

	dp->angle_1 = 0.0;
	dp->angle_2 = 0.0;

	dp->angv_1 = 0.0;
	dp->angv_2 = 0.0;

	dp->x1 = 100.0;
	dp->y1 = 120.0;

	dp->x2 = 100.0;
	dp->y2 = 170.0;
}

void dp_step(DoublePendulum *dp) {
	(void)dp;
}

void dp_draw(DoublePendulum *dp) {
	DrawLine(dp->ox, dp->oy, dp->x1, dp->y1, RED);
	DrawCircle(dp->x1, dp->y1, 2.0, PURPLE);

	DrawLine(dp->x1, dp->y1, dp->x2, dp->y2, ORANGE);
	DrawCircle(dp->x2, dp->y2, 2.0, GREEN);
}

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	DoublePendulum dp;
	bool shouldClose = false;

	InitWindow(SCR_W, SCR_H, SCR_TITLE);
	SetTargetFPS(60);

	dp_init(&dp);

	while( !shouldClose ) {
		shouldClose = WindowShouldClose();

		dp_step(&dp);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		dp_draw(&dp);
		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}
