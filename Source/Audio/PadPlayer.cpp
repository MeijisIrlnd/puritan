/*
  ==============================================================================

    PadPlayer.cpp
    Created: 19 Nov 2022 9:42:43pm
    Author:  Syl

  ==============================================================================
*/

#include "PadPlayer.h"

namespace Puritan::Audio
{
    PadPlayer::PadPlayer(const int index) : m_index(index)
    {
    }

    void PadPlayer::setSample(const juce::File& toLoad)
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        m_linkedInfo.reset(new PadInfo(toLoad));
        if (m_listener != nullptr) {
            m_listener->onSampleChanged(m_index, m_linkedInfo);
        }
    }

    void PadPlayer::prepareToPlay(PURITAN_UNUSED int samplesPerBlockExpected, PURITAN_UNUSED double sampleRate)
    {
    }

    void PadPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        if (m_linkedInfo.get() == nullptr) return;
        auto* read = m_linkedInfo->audioData.getArrayOfReadPointers();
        auto* write = bufferToFill.buffer->getArrayOfWritePointers();
        for (auto sample = 0; sample < bufferToFill.numSamples; sample++)
        {
            if (m_currentSample >= m_linkedInfo->audioData.getNumSamples() * m_normalisedEnd) return;
            for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
            {
                write[channel][sample] += read[channel][m_currentSample];
            }
            ++m_currentSample;
        }
    }

    void PadPlayer::releaseResources()
    {
    }

    void PadPlayer::play()
    {
        m_currentSample = 0;
        if (m_linkedInfo == nullptr) return;
        m_currentSample = static_cast<std::uint64_t>(m_normalisedStart * m_linkedInfo->audioData.getNumSamples());
        m_padPlaying = true;
    }

    void PadPlayer::stop()
    {
        if (m_linkedInfo == nullptr) return;
        m_padPlaying = false;
    }
}