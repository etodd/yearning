#pragma once

#include "data/entity.h"
#include "render.h"

namespace VI
{

#define DEBUG_VIEW 0


struct AudioEntry;

struct View : public ComponentType<View>
{
	struct DebugEntry
	{
		AssetID mesh;
		Quat rot;
		Vec4 color;
		Vec3 pos;
		Vec3 scale;
	};

	static Bitmask<MAX_ENTITIES> list_alpha;
	static Bitmask<MAX_ENTITIES> list_additive;
#if DEBUG_VIEW
	static Array<DebugEntry> debug_entries;
#endif

	Mat4 offset;
	Vec4 color;
	r32 radius;
	RenderMask mask;
	AssetID mesh;
	AssetID shader;
	AssetID texture;
	s8 team;

	static void draw_opaque(const RenderParams&);
	static void draw_alpha(const RenderParams&);
	static void draw_additive(const RenderParams&);
	typedef b8 Filter(const RenderParams&, const View*);
	static void draw_filtered(const RenderParams&, Filter*);

	static void draw_mesh(const RenderParams&, AssetID, AssetID, AssetID, const Mat4&, const Vec4&, r32 = 0.0f);

#if DEBUG_VIEW
	static void debug(AssetID, const Vec3&, const Quat& = Quat::identity, const Vec3& = Vec3(1), const Vec4& = Vec4(1, 1, 1, 0.5f));
#endif

	View();
	View(AssetID);
	void awake();
	~View();

	AlphaMode alpha_mode() const;
	void alpha_mode(AlphaMode);
	void alpha();
	void additive();
	void alpha_disable();
	void draw(const RenderParams&) const;
};

struct Skybox
{
	struct Config
	{
		Vec3 color;
		r32 far_plane;
		r32 fog_start;
		r32 fog_end;
		AssetID texture;
		AssetID mesh;
		AssetID shader;
		b8 valid() const;
	};

	static void draw_alpha(const RenderParams&);
};

struct SkyDecals
{
	struct Config
	{
		Quat rot;
		Vec4 color;
		r32 scale;
		AssetID texture;
	};

	static void draw_alpha(const RenderParams&);
};

struct Clouds
{
	struct Config
	{
		Vec4 color;
		Vec2 velocity;
		r32 height;
		r32 scale;
		r32 shadow;

		Vec2 uv_offset(const RenderParams&) const;
	};

	static void draw_alpha(const RenderParams&);
};

struct Water : public ComponentType<Water>
{
	struct Config
	{
		Vec4 color;
		r32 displacement_horizontal;
		r32 displacement_vertical;
		AssetID texture;
		AssetID mesh;
		b8 ocean;

		Config(AssetID = AssetNull);
	};

	static Water* underwater(const Vec3&);
	static void draw_opaque(const RenderParams&, const Config&, const Vec3&, const Quat&);
	static void draw_hollow(const RenderParams&, const Config&, const Vec3&, const Quat&);
	static void draw_opaque(const RenderParams&);
	static void draw_alpha_late(const RenderParams&);
	static void update_all(const Update&);

	Config config;
	Ref<AudioEntry> audio_entries[MAX_GAMEPADS];
	RenderMask mask;

	Water(AssetID = AssetNull);
	void awake();
	void draw_hollow(const RenderParams&);
	b8 contains(const Vec3&) const;
};

struct SkyPattern
{
	static void draw_opaque(const RenderParams&);
	static void draw_hollow(const RenderParams&);
};

struct ScreenQuad
{
	ScreenQuad();
	AssetID mesh;
	void init(RenderSync*);
	void set(RenderSync*, const Rect2&, const Camera*, const Rect2& = { Vec2::zero, Vec2(1, 1) });
};

}
