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
        struct Listener
        {
            virtual ~Listener() { }
            virtual void onSampleChanged(int index, std::shared_ptr<PadInfo> newPattern) = 0;
        };
        PadPlayer(const int index);
        PURITAN_INLINE void addListener(Listener* newListener) {
            m_listener = newListener;
        }

        PURITAN_INLINE void removeListener() {
            m_listener = nullptr;
        }
        void setSample(const juce::File& toLoad);
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
        void releaseResources();
        void play();
        void stop();
        PURITAN_INLINE std::shared_ptr<PadInfo> getInfo() { return m_linkedInfo; }
    private: 
        std::mutex m_mutex;
        std::shared_ptr<PadInfo> m_linkedInfo{ nullptr };
        const int m_index;
        Listener* m_listener{ nullptr };
        bool m_padPlaying{ false };
        std::uint64_t m_currentSample{ 0 };
    };
}
