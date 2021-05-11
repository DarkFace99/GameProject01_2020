#pragma once

#include <irrKlang.h>
#include "srpch.h"

using namespace irrklang;

#define AUDIO_FILE_PATH "Assets/Audio/"

namespace Srand
{
	enum class SoundType
	{
		DEFAULT,
		MUSIC,
		EFFECT
	};

	struct AudioSource 
	{
		std::string name;
		std::string filePath;
		float volume;
		bool isLoopable;
		SoundType type;

		bool isPlayed = false;

		AudioSource() = default;
		AudioSource(std::string name, float volume, bool isLoopable, std::string filePath, SoundType type = SoundType::DEFAULT)
		{
			this->name = name;
			this->filePath = filePath;
			this->volume = volume;
			this->isLoopable = isLoopable;
			this->type = type;
		}
	};

	class AudioController
	{
	private:
		static AudioController* s_instance;
		ISoundEngine* m_engine = nullptr;
		ISound* sound = nullptr;
		ISound* bgmSound = nullptr;
		std::unordered_map<std::string, AudioSource*> m_soundSource;

		int size = 0;
		bool play = false;
		bool pause = false;

		AudioController() 
		{
			m_engine = createIrrKlangDevice();
		}

	public:
		inline static AudioController& get() 
		{
			if (s_instance == nullptr) 
			{
				s_instance = new AudioController();
			}
			return *s_instance;
		}
		~AudioController() 
		{
			m_soundSource.clear();
			m_engine->drop();
		}

		/// <summary>
		/// Add Audio to controller and can be use to call it later
		/// (Add audio when loading the assets)
		/// </summary>
		/// <param name="audio"> : Data of the audio </param>
		void AddAudioSource(AudioSource* audio);

		/// <summary>
		/// Find matching name of an AudioSource and return its pointer
		/// </summary>
		/// <param name="name"> : Name of the AudioSource </param>
		/// <returns> Pointer to AudioSource</returns>
		AudioSource* Find(std::string name);

		/// <summary>
		/// Play AudioSource by searching inside m_soundSource for a matching name
		/// </summary>
		/// <param name="name"> : Name of the AudioSource </param>
		void Play(std::string name);

		/// <summary>
		/// Play AudioSource that has not been added to m_soundSource
		/// </summary>
		/// <param name="name"> : Name of Audio file </param>
		/// <param name="volume"> : Audio volume </param>
		/// <param name="isLoopable">: Set loop status </param>
		/// <param name="filepath"> : Path of Audio file </param>
		void Play(std::string name, float volume, bool isLoopable, std::string filePath);

		/// <summary>
		/// Pause current playing audio
		/// </summary>
		void Pause();

		/// <summary>
		/// Pause current playing audio
		/// </summary>
		void UnPause();

		/// <summary>
		/// Stop current playing audio and drop its pointer
		/// </summary>
		void Stop();

		/// <summary>
		/// Change volume of selected sound type by a 10% step
		/// </summary>
		/// <param name="mode"> : 1 for increase the volume and else for decrease</param>
		/// <param name="type"> : type of sound that need volume change</param>
		void ChangeVolume(int mode = 1, SoundType type = SoundType::DEFAULT);

		void SetAllVolume(float vol);

		void SetMusicVolume(float vol);
		void SetEffectVolume(float vol);
		std::pair<float, float> GetVolume();
	};
}
