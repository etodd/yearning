#include "audio.h"
#include "asset/soundbank.h"
#include "asset/lookup.h"
#include "data/components.h"
#include "load.h"

#include <stdio.h>
#include "asset/Wwise_IDs.h"
#include "settings.h"

#if !SERVER
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/Plugin/AkVorbisFactory.h>
#if DEBUG
	#include <AK/Comm/AkCommunication.h>
#endif

namespace AK
{
	void* AllocHook(size_t in_size)
	{
		return malloc(in_size);
	}

	void FreeHook(void* in_ptr)
	{
		free(in_ptr);
	}

#if _WIN32
	void * VirtualAllocHook(
		void * in_pMemAddress,
		size_t in_size,
		DWORD in_dwAllocationType,
		DWORD in_dwProtect
		)
	{
		return VirtualAlloc(in_pMemAddress, in_size, in_dwAllocationType, in_dwProtect);
	}
	void VirtualFreeHook(
		void * in_pMemAddress,
		size_t in_size,
		DWORD in_dwFreeType
		)
	{
		VirtualFree(in_pMemAddress, in_size, in_dwFreeType);
	}
#endif
}
#endif

namespace VI
{

#if !SERVER
CAkDefaultIOHookBlocking Audio::wwise_io;
#endif
b8 Audio::dialogue_done = true;

b8 Audio::init()
{
#if !SERVER
	AkMemSettings memSettings;
	memSettings.uMaxNumPools = 20;

	if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
	{
		fprintf(stderr, "Failed to create the Wwise memory manager.\n");
		return false;
	}

	// Create the Stream Manager.
	AkStreamMgrSettings stmSettings;
	AK::StreamMgr::GetDefaultSettings(stmSettings);
	AK::StreamMgr::Create(stmSettings);

	// Create a streaming device with blocking low-level I/O handshaking.
	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
	deviceSettings.uSchedulerTypeFlags = AK_SCHEDULER_BLOCKING;

	// Init registers lowLevelIO as the File Location Resolver if it was not already defined, and creates a streaming device.
	if (!wwise_io.Init(deviceSettings))
	{
		fprintf(stderr, "Failed to create the Wwise streaming device and low-level IO system.\n");
		return false;
	}

#if !_WIN32
	wwise_io.SetBasePath("");
#endif
	
	AkInitSettings initSettings;
	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
	{
		fprintf(stderr, "Failed to initialize the Wwise sound engine.\n");
		return false;
	}

	AkMusicSettings musicInit;
	AK::MusicEngine::GetDefaultInitSettings(musicInit);
		
	if (AK::MusicEngine::Init(&musicInit) != AK_Success)
	{
		fprintf(stderr, "Failed to initialize the Wwise music engine.\n");
		return false;
	}

#if DEBUG
	AkCommSettings commSettings;
	AK::Comm::GetDefaultInitSettings(commSettings);
	if (AK::Comm::Init(commSettings) != AK_Success)
	{
		fprintf(stderr, "Failed to initialize Wwise communication.\n");
		return false;
	}
#endif

	AK::SoundEngine::RegisterCodec( AKCOMPANYID_AUDIOKINETIC, 
									AKCODECID_VORBIS, 
									CreateVorbisFilePlugin, 
									CreateVorbisBankPlugin);

	// Game object for global events
	AK::SoundEngine::RegisterGameObj(MAX_ENTITIES);

	for (s32 i = 0; i < 8; i++)
		AK::SoundEngine::SetListenerPipeline(i, false, false); // Disable listener

	AK::SoundEngine::RegisterBusMeteringCallback(AK::BUSSES::DIALOGUE, Audio::dialogue_volume_callback, (AkMeteringFlags)AK_EnableBusMeter_Peak);

	global_param(AK::GAME_PARAMETERS::SFXVOL, (r32)Settings::sfx / 100.0f);
	global_param(AK::GAME_PARAMETERS::MUSICVOL, (r32)Settings::music / 100.0f);
#endif

	return true;
}

r32 Audio::dialogue_volume = 0.0f;

#if !SERVER
// Wwise callbacks
void Audio::dialogue_volume_callback(AK::IAkMetering* metering, AkChannelConfig channel_config, AkMeteringFlags flags)
{
	r32 sum = 0.0f;
	AK::SpeakerVolumes::ConstVectorPtr peak = metering->GetPeak();
	for (s32 i = 0; i < channel_config.uNumChannels; i++)
		sum += peak[i];
	dialogue_volume = sum;
}

void Audio::dialogue_done_callback(AkCallbackType type, AkCallbackInfo* info)
{
	dialogue_done = true;
}
#endif

void Audio::term()
{
#if !SERVER
#if DEBUG
	AK::Comm::Term();
#endif
	AK::MusicEngine::Term();
	AK::SoundEngine::Term();
	wwise_io.Term();
	if (AK::IAkStreamMgr::Get())
		AK::IAkStreamMgr::Get()->Destroy();
	AK::MemoryMgr::Term();
#endif
}

void Audio::update()
{
#if !SERVER
	for (auto i = Audio::list.iterator(); !i.is_last(); i.next())
	{
		Transform* transform = i.item()->get<Transform>();
		if (transform)
		{
			Vec3 pos;
			Quat rot;
			transform->absolute(&pos, &rot);

			AkSoundPosition sound_position;
			sound_position.Position.X = pos.x;
			sound_position.Position.Y = pos.y;
			sound_position.Position.Z = pos.z;
			Vec3 forward = rot * Vec3(0, 0, -1.0f);
			sound_position.Orientation.X = forward.x;
			sound_position.Orientation.Y = forward.y;
			sound_position.Orientation.Z = forward.z;
			AK::SoundEngine::SetPosition(transform->entity_id, sound_position);
		}
	}
	AK::SoundEngine::RenderAudio();
#endif
}

AkUniqueID Audio::get_id(const char* str)
{
#if SERVER
	return 0;
#else
	return AK::SoundEngine::GetIDFromString(str);
#endif
}

void Audio::post_global_event(AkUniqueID event_id)
{
#if !SERVER
	AK::SoundEngine::PostEvent(event_id, MAX_ENTITIES);
#endif
}

b8 Audio::post_dialogue_event(AkUniqueID event_id)
{
#if SERVER
	return true;
#else
	AkPlayingID id = AK::SoundEngine::PostEvent(event_id, MAX_ENTITIES, AkCallbackType::AK_EndOfEvent, &dialogue_done_callback);
	return id != 0;
#endif
}

void Audio::post_global_event(AkUniqueID event_id, const Vec3& pos)
{
	post_global_event(event_id, pos, Vec3(0, 0, 1));
}

void Audio::post_global_event(AkUniqueID event_id, const Vec3& pos, const Vec3& forward)
{
#if !SERVER
	const AkGameObjectID id = MAX_ENTITIES + 1;
	AK::SoundEngine::RegisterGameObj(id);
	AK::SoundEngine::SetActiveListeners(id, 0b01111); // All listeners

	AkSoundPosition sound_position;
	sound_position.Position.X = pos.x;
	sound_position.Position.Y = pos.y;
	sound_position.Position.Z = pos.z;
	sound_position.Orientation.X = -forward.x;
	sound_position.Orientation.Y = -forward.y;
	sound_position.Orientation.Z = -forward.z;
	AK::SoundEngine::SetPosition(id, sound_position);

	AK::SoundEngine::PostEvent(event_id, id);
	AK::SoundEngine::UnregisterGameObj(id);
#endif
}

void Audio::global_param(AkRtpcID id, AkRtpcValue value)
{
#if !SERVER
	AK::SoundEngine::SetRTPCValue(id, value);
#endif
}

void Audio::listener_disable(u32 listener_id)
{
#if !SERVER
	AK::SoundEngine::SetListenerPipeline(listener_id, false, false);
#endif
}

void Audio::listener_enable(u32 listener_id)
{
#if !SERVER
	AK::SoundEngine::SetListenerPipeline(listener_id, true, false);
#endif
}

void Audio::listener_update(u32 listener_id, const Vec3& pos, const Quat& rot)
{
#if !SERVER
	AkListenerPosition listener_position;
	listener_position.Position.X = pos.x;
	listener_position.Position.Y = pos.y;
	listener_position.Position.Z = pos.z;
	Vec3 forward = rot * Vec3(0, 0, -1);
	listener_position.OrientationFront.X = forward.x;
	listener_position.OrientationFront.Y = forward.y;
	listener_position.OrientationFront.Z = forward.z;
	Vec3 up = rot * Vec3(0, 1, 0);
	listener_position.OrientationTop.X = up.x;
	listener_position.OrientationTop.Y = up.y;
	listener_position.OrientationTop.Z = up.z;
	AK::SoundEngine::SetListenerPosition(listener_position, listener_id);
#endif
}

void Audio::awake()
{
#if !SERVER
	AK::SoundEngine::RegisterGameObj(entity_id);
	AK::SoundEngine::SetActiveListeners(entity_id, 0b01111); // All listeners
#endif
}

Audio::~Audio()
{
#if !SERVER
	AK::SoundEngine::UnregisterGameObj(entity_id);
#endif
}

void Audio::post_event(AkUniqueID event_id)
{
#if !SERVER
	AK::SoundEngine::PostEvent(event_id, entity_id);
#endif
}

void Audio::param(AkRtpcID id, AkRtpcValue value)
{
#if !SERVER
	AK::SoundEngine::SetRTPCValue(id, value, entity_id);
#endif
}

}
