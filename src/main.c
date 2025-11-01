/* Double pendulum
 * Pedro B.
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define SCR_W (1280)
#define SCR_H (720)
#define SCR_TITLE "Double Pendulum!"

typedef struct _DoublePendulum {
	Vector2 origin;
	Vector2 p1;
	Vector2 p2;

	float l1, l2;
	float m_b1, m_b2;
	float g;
	float angle_1, angle_2;
	float angv_1, angv_2;

	int step;
} DoublePendulum;

static DoublePendulum _dp;

static bool _changed = false;
static float _l1, _l2;
static float _m_b1, _m_b2;
static float _g;

void dp_init(DoublePendulum *dp) {
	dp->origin.x = SCR_W / 2.0f;
	dp->origin.y = SCR_H / 4.0f;

	dp->l1 = _l1 = 200.0f;
	dp->l2 = _l2 = 100.0f;

	dp->m_b1 = _m_b1 = 0.5f;
	dp->m_b2 = _m_b2 = 1.0f;

	dp->g = _g = 9.81f;

	dp->angle_1 = PI / 2.0f;
	dp->angle_2 = -PI / 2.0f;

	dp->angv_1 = 0.0f;
	dp->angv_2 = 0.0f;

	dp->p1.x = 0.0f;
	dp->p1.y = 0.0f;

	dp->p2.x = 0.0f;
	dp->p2.y = 0.0f;

	dp->step = 1;
}

void dp_step(DoublePendulum *dp) {
	float a1, a2;

	const float DT = GetFrameTime();

	const float DELTA = dp->angle_2 - dp->angle_1;

	const float COS_D = cosf(DELTA);
	const float COS2_D = COS_D * COS_D;

	const float SIN_D = sinf(DELTA);

	const float SIN_T1 = sinf(dp->angle_1);
	const float SIN_T2 = sinf(dp->angle_2);

	const float ANGV2_1 = dp->angv_1 * dp->angv_1;
	const float ANGV2_2 = dp->angv_2 * dp->angv_2;

	const float MB = (dp->m_b1 + dp->m_b2);

	const float D1 = MB * dp->l1 - dp->m_b2 * dp->l1 * COS2_D;
	const float D2 = (dp->l2 / dp->l1) * D1;

	a1 = (dp->m_b2 * dp->l1 * ANGV2_1 * SIN_D * COS_D);
	a1 += (dp->m_b2 * dp->g * SIN_T2 * COS_D);
	a1 += (dp->m_b2 * dp->l2 * ANGV2_2 * SIN_D);
	a1 -= (MB * dp->g * SIN_T1);
	a1 /= D1;

	a2 = (-dp->m_b2 * dp->l2 * ANGV2_2 * SIN_D * COS_D);
	a2 += (MB * dp->g * SIN_T1 * COS_D);
	a2 -= (MB * dp->l1 * ANGV2_1 * SIN_D);
	a2 -= (MB * dp->g * SIN_T2);
	a2 /= D2;

	dp->angv_1 += a1 * DT;
	dp->angv_2 += a2 * DT;

	dp->angle_1 += dp->angv_1 * DT;
	dp->angle_2 += dp->angv_2 * DT;

	dp->p1.x = dp->origin.x + dp->l1 * sinf(dp->angle_1);
	dp->p1.y = dp->origin.y + dp->l1 * cosf(dp->angle_1);

	dp->p2.x = dp->p1.x + dp->l2 * sinf(dp->angle_2);
	dp->p2.y = dp->p1.y + dp->l2 * cosf(dp->angle_2);
}

void dp_draw(DoublePendulum *dp) {
	DrawLineEx(dp->origin, dp->p1, 8.0f, RED);
	DrawLineEx(dp->p1, dp->p2, 8.0f, RED);

	DrawCircleV(dp->p1, 8.0f, PURPLE);
	DrawCircleV(dp->p2, 8.0f, GREEN);
}

void update(void) {
	int i;

	if( _changed ) {
		_dp.l1 = _l1;
		_dp.l2 = _l2;
		_dp.m_b1 = _m_b1;
		_dp.m_b2 = _m_b2;
		_dp.g = _g;

		_changed = false;
	}

	for( i = 0; i < 10; ++i ) {
		dp_step(&_dp);
	}

	BeginDrawing();
	ClearBackground(RAYWHITE);
	dp_draw(&_dp);
	EndDrawing();
}

int
#if defined(PLATFORM_WEB)
	EMSCRIPTEN_KEEPALIVE
#endif
	main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	dp_init(&_dp);

	InitWindow(SCR_W, SCR_H, SCR_TITLE);

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(update, 0, 1);
#else
	SetTargetFPS(60);
	while( !WindowShouldClose() ) {
		update();
	}
#endif

	CloseWindow();

	return EXIT_SUCCESS;
}

void
#if defined(PLATFORM_WEB)
	EMSCRIPTEN_KEEPALIVE
#endif
	update_l1(float length) {
	_changed = true;
	_l1 = length;
}

void
#if defined(PLATFORM_WEB)
	EMSCRIPTEN_KEEPALIVE
#endif
	update_l2(float length) {
	_changed = true;
	_l2 = length;
}

void
#if defined(PLATFORM_WEB)
	EMSCRIPTEN_KEEPALIVE
#endif
	update_b1_mass(float mass) {
	_changed = true;
	_m_b1 = mass;
}

void
#if defined(PLATFORM_WEB)
	EMSCRIPTEN_KEEPALIVE
#endif
	update_b2_mass(float mass) {
	_changed = true;
	_m_b2 = mass;
}
