#include "behavior.h"

namespace VI
{

void Sequence::run()
{
	active(true);
	index = 0;
	children[0]->run();
}

void Sequence::child_done(Behavior* child, b8 success)
{
	active(true);
	if (success)
	{
		index++;
		if (index < num_children)
			children[index]->run();
		else
			done(true);
	}
	else
		done(false);
}

void Select::run()
{
	active(true);
	index = 0;
	children[0]->run();
}

void Select::child_done(Behavior* child, b8 success)
{
	if (success)
		done(true);
	else
	{
		index++;
		if (index < num_children)
			children[index]->run();
		else
			done(false);
	}
}

void Parallel::run()
{
	active(true);
	children_done = 0;
	for (s32 i = 0; i < num_children; i++)
	{
		children[i]->run();
		if (!active())
			break;
	}
}

void Parallel::child_done(Behavior* child, b8 success)
{
	if (success)
	{
		children_done++;
		if (children_done == num_children)
			done(true);
	}
	else
	{
		for (s32 i = 0; i < num_children; i++)
			children[i]->abort();
		done(false);
	}
}

Repeat::Repeat(Behavior* child, s32 repeat)
	: BehaviorDecorator(child), repeat_count(repeat), repeat_index()
{
}

void Repeat::run()
{
	active(true);
	repeat_index = 0;
	child->run();
}

void Repeat::child_done(Behavior* child, b8 succeeded)
{
	if (succeeded)
	{
		if (repeat_index < repeat_count || repeat_count < 0)
		{
			repeat_index++;
			child->run();
		}
		else
			done(true);
	}
	else
		done(false);
}

void Delay::run()
{
	timer = duration;
	active(true);
}

void Delay::update(const Update& u)
{
	timer -= u.time.delta;
	if (timer < 0)
		done();
}

Succeed::Succeed(Behavior* b) : BehaviorDecorator(b) { }

void Succeed::run()
{
	active(true);
	child->run();
}

void Succeed::child_done(Behavior* b, b8 success)
{
	done(true);
}

Invert::Invert(Behavior* b) : BehaviorDecorator(b) { }

void Invert::run()
{
	active(true);
	child->run();
}

void Invert::child_done(Behavior* b, b8 success)
{
	done(!success);
}


}