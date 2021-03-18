#pragma once

#include <irrKlang.h>
#include "srpch.h"

using namespace irrklang;

#define AUDIO_FILE_PATH "../Assets/Audio/"

namespace Srand
{
	struct AudioSource 
	{
		std::string name;
		std::string filePath;
		float volume;
		bool isLoopable;

		AudioSource() = default;
		AudioSource(std::string name, float volume, bool isLoopable, std::string filePath)
		{
			this->name = name;
			this->filePath = filePath;
			this->volume = volume;
			this->isLoopable = isLoopable;
		}
	};

	class AudioController
	{
	private:
		static AudioController* s_instance;
		ISoundEngine* m_engine = nullptr;
		ISound* sound = nullptr;
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
			m_engine->drop();
		}

		void AddAudioSource(AudioSource* audio);
		AudioSource* Find(std::string name);
		void Play(std::string name);
		void Pause();
		void Stop();
	};
}
