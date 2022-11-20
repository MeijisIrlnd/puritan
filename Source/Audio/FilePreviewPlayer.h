/*
  ==============================================================================

    FilePreviewPlayer.h
    Created: 20 Nov 2022 1:58:58am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Utils/Macros.h>
#include <Utils/Utilities.h>
namespace Puritan::Audio
{
    class FilePreviewPlayer
    {
    public: 
        FilePreviewPlayer();
        ~FilePreviewPlayer();
        void setFile(const juce::File& toLoad);
        void play();
        void play(const juce::File& toLoad);
        void stop();
        void prepareToPlay(PURITAN_UNUSED int samplesPerBlockExpected, PURITAN_UNUSED double sampleRate);
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
        void releaseResources();
    private: 
        std::mutex m_mutex;
        std::atomic_bool m_playing{ false };
        std::uint16_t m_sampleCounter{ 0 };
        juce::AudioBuffer<float> m_buffer;
        double m_sampleRate{ 0 };


    };
}