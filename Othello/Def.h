// Def.h
// ‹¤’Ê’è‹`‚ğ‹Lq‚·‚é

#pragma once

// define
static constexpr float PI = 3.14159265358f;
static Vec2i WINDOW_SIZE = { 640, 480 };
static float ASPECT_RATIO = static_cast<float>(WINDOW_SIZE.x) / WINDOW_SIZE.y;
//static constexpr Vec2i FIELD_SIZE = { 10, 20 };

// undef
#undef min
#undef max

