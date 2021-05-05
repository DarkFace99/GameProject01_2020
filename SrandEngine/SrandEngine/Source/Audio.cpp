#include "Audio.h"

namespace Srand 
{
    AudioController* AudioController::s_instance = nullptr;

    void AudioController::AddAudioSource(AudioSource* audio)
    {
        std::string key = audio->name;
        m_soundSource.insert({ key, audio });
        size++;
    }

    AudioSource* AudioController::Find(std::string name)
    {
        if (m_soundSource.empty())
            return nullptr;

        AudioSource* search_result = m_soundSource.find(name)->second;

        return search_result;
    }

    void AudioController::Play(std::string name)
    {
        if (m_engine == nullptr)
            return;

        AudioSource* audio = Find(name);

        sound = m_engine->play2D((AUDIO_FILE_PATH + audio->filePath).c_str(), audio->isLoopable, false, true);
        if (sound == nullptr) 
        {
            SR_SYSTEM_ERROR("Error: Cannot find {0}", AUDIO_FILE_PATH + audio->filePath);
            return;
        }
        sound->setVolume(audio->volume);
    }
    void AudioController::Play(std::string name, float volume, bool isLoopable, std::string filePath)
    {
        AddAudioSource(new AudioSource(name, volume, isLoopable, filePath));

        if (m_engine == nullptr)
            return;

        sound = m_engine->play2D((AUDIO_FILE_PATH + filePath).c_str(), isLoopable, false, true);
        if (sound == nullptr)
        {
            SR_SYSTEM_ERROR("Error: Cannot find {0}", AUDIO_FILE_PATH + filePath);
            return;
        }
        sound->setVolume(volume);
    }
    void AudioController::Pause()
    {
        if (!pause) 
        {
            pause = true;
            sound->setIsPaused(pause);
        }
    }
    void AudioController::Stop()
    {
        if (sound == nullptr)
            return;

        m_engine->stopAllSounds();

        //sound = nullptr;

        play = false;
    }
    void AudioController::ChangeVolume(int mode, SoundType type)
    {
        for (auto& src : m_soundSource) 
        {
            if (src.second->type == type) 
            {
                //float volAmount = src.second->volume * (0.1f);

                if(mode == 1)
                    src.second->volume += 0.1f;
                else
                    src.second->volume -= 0.1f;


                if (src.second->volume < 0) 
                    src.second->volume = 0.0f;
                if (src.second->volume > 1)
                    src.second->volume = 1.0f;

                //SR_SYSTEM_TRACE("Vol: {0}", src.second->volume);
            }
        }
    }

    std::pair<float, float> AudioController::GetVolume()
    {
        bool foundM = false;
        bool foundE = false;

        std::pair<float, float> return_pair;

        for (auto& src : m_soundSource) 
        {
            if (!foundM && src.second->type == SoundType::MUSIC) 
            {
                return_pair.first = src.second->volume;
                foundM = true;
            }
            else if (foundM)
            {
                continue;
            }
            if (!foundE && src.second->type == SoundType::EFFECT)
            {
                return_pair.second = src.second->volume;
                foundE = true;
            }
            else if (foundE)
            {
                continue;
            }
        }

        return return_pair;
    }
    
}

