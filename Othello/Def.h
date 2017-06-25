// Def.h
// ���ʒ�`���L�q����

#pragma once

#include "Vec2.h"

// define
// common
static constexpr float PI = 3.14159265358f;
static constexpr Vec2i WINDOW_SIZE{ 640, 480 };
static float ASPECT_RATIO = static_cast<float>(WINDOW_SIZE.x) / WINDOW_SIZE.y;
static const int DEFAULT_VERTS_COUNT = 4;

// game specific
static constexpr Vec2i FIELD_SIZE = { 8, 8 };

// undef
#undef min
#undef max

