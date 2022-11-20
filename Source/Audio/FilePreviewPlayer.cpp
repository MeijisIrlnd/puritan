/*
  ==============================================================================

    FilePreviewPlayer.cpp
    Created: 20 Nov 2022 1:58:58am
    Author:  Syl

  ==============================================================================
*/

#include "FilePreviewPlayer.h"
#include <PluginProcessor.h>
namespace Puritan::Audio
{
    FilePreviewPlayer::FilePreviewPlayer()
    {
    }

    FilePreviewPlayer::~FilePreviewPlayer()
    {
    }

    void FilePreviewPlayer::setFile(const juce::File& toLoad)
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        stop();
        m_buffer.clear();
        Puritan::Utils::loadWithResample(*PuritanAudioProcessor::getInstance()->getFormatManager(), toLoad, m_sampleRate, m_buffer);
    }

    void FilePreviewPlayer::play()
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        m_sampleCounter = 0;
        m_playing.store(true);
    }

    void FilePreviewPlayer::play(const juce::File& toLoad)
    {
        setFile(toLoad);
        play();
    }

    void FilePreviewPlayer::stop()
    {
        m_playing.store(false);
    }

    void FilePreviewPlayer::prepareToPlay(PURITAN_UNUSED int samplesPerBlockExpected, double sampleRate)
    {
        m_sampleRate = sampleRate;
    }

    void FilePreviewPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        if (!m_playing.load() || m_sampleCounter >= m_buffer.getNumSamples()) return;
        auto* read = m_buffer.getArrayOfReadPointers();
        auto* write = bufferToFill.buffer->getArrayOfWritePointers();
        for (auto sample = 0; sample < bufferToFill.numSamples; sample++)
        {
            PURITAN_UNUSED auto n = m_buffer.getNumSamples();
            if (m_sampleCounter >= m_buffer.getNumSamples()) {
                m_playing.store(false);
                return;
            }
            for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
            {
                write[channel][sample] += read[channel][m_sampleCounter];
                
            }
            ++m_sampleCounter;
        }
    }

    void FilePreviewPlayer::releaseResources()
    {
    }
}