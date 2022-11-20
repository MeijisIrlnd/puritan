/*
  ==============================================================================

    PadPlayer.h
    Created: 19 Nov 2022 9:42:43pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Types/PadInfo.h>
#include <Utils/Macros.h>
namespace Puritan::Audio
{
    class PadPlayer
    {
    public: 
        PadPlayer();
        void setSample(PadInfo* linked);
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
        void releaseResources();
        void play();
        void stop();
    private: 
        std::mutex m_mutex;
        PadInfo* m_linkedInfo{ nullptr };
        bool m_padPlaying{ false };
        std::uint64_t m_currentSample{ 0 };
    };
}
