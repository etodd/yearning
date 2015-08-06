#pragma once

#include "data/entity.h"
#include "data/components.h"
#include "load.h"
#include "physics.h"
#include "render/ui.h"

namespace VI
{

struct Console
{
	static Array<char> command;
	static bool visible;
	static UIText text;
	static char shift_map[127];
	static char normal_map[127];
	static float repeat_start_time;
	static float repeat_last_time;

	static void init();
	static void update(const Update&);
	static void draw(const RenderParams&);
};

}