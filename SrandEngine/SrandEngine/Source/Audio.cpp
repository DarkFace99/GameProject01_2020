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
        sound->setVolume(audio->volume);
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

        sound->stop();
        sound->drop();

        sound = nullptr;

        play = false;
    }
}

