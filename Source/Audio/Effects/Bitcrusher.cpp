/*
  ==============================================================================

    Bitcrusher.cpp
    Created: 4 Dec 2022 6:10:18pm
    Author:  Syl

  ==============================================================================
*/

#include "Bitcrusher.h"

namespace Puritan::Audio::Effects
{
    Bitcrusher::Bitcrusher()
    {
        m_highpasses.emplace_back();
        m_highpasses.emplace_back();
    }

    Bitcrusher::~Bitcrusher()
    {
    }

    void Bitcrusher::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        m_sampleRate = sampleRate;
        m_processBuffer.setSize(2, samplesPerBlockExpected);
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlockExpected), 2 };
        m_rmsBallistics.prepare(spec);
        SDSP::RBJ::bandpass(m_noiseCoeffs.target(0), sampleRate, 500, 2);
        std::memcpy(m_noiseCoeffs.current(0), m_noiseCoeffs.target(0), sizeof(double) * 6);
        SDSP::RBJ::highpass(m_coeffs.target(0), sampleRate, m_highpassCutoff, 0.5);
        std::memcpy(m_coeffs.current(0), m_coeffs.target(0), sizeof(double) * 6);
        SDSP::RBJ::highpass(m_coeffs.target(1), sampleRate, m_highpassCutoff, 1.3);
        std::memcpy(m_coeffs.current(1), m_coeffs.target(1), sizeof(double) * 6);
        m_noiseFilter.setCoefficients(m_noiseCoeffs.target(0));
        for (auto& f : m_highpasses) {
            f.setCoefficients(m_coeffs.target(0), 0);
            f.setCoefficients(m_coeffs.target(1), 1);
        }
    }

    void Bitcrusher::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
    {
        auto* read = bufferToFill.buffer->getArrayOfReadPointers();
        auto* write = bufferToFill.buffer->getArrayOfWritePointers();
        if (m_processBuffer.getNumChannels() != bufferToFill.buffer->getNumChannels() || m_processBuffer.getNumSamples() != bufferToFill.buffer->getNumSamples()) {
            m_processBuffer.setSize(bufferToFill.buffer->getNumChannels(), bufferToFill.buffer->getNumSamples());
        }
        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++) {
            m_processBuffer.copyFrom(0, 0, bufferToFill.buffer->getReadPointer(channel), bufferToFill.buffer->getNumSamples());
            std::memcpy(m_processBuffer.getWritePointer(channel), m_processBuffer.getReadPointer(channel), sizeof(float) * m_processBuffer.getNumSamples());
        }
        auto* data = m_processBuffer.getArrayOfWritePointers();
        for (auto sample = 0; sample < bufferToFill.numSamples; sample++) {
            if (m_samplesUntilUpdate == 0) {
                SDSP::RBJ::highpass(m_coeffs.target(0), m_sampleRate, m_highpassCutoff, 0.5);
                SDSP::RBJ::highpass(m_coeffs.target(1), m_sampleRate, m_highpassCutoff, 1.3);
                m_samplesUntilUpdate = m_updateRate;
            }
            interpolateCoefficients();
            float numQuantizeLevels = std::powf(2, static_cast<float>(m_bitDepth));
            for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
            {
                data[channel][sample] = noisify(channel, data[channel][sample]);
                float remainder = std::fmodf(data[channel][sample], 1 / numQuantizeLevels);
                data[channel][sample] -= remainder;
              
                if (m_rateReduction > 1) {
                    data[channel][sample] = data[channel][sample - sample % m_rateReduction];
                }
                //data[channel][sample] = m_highpasses[channel].processSample(data[channel][sample]);
                write[channel][sample] = (data[channel][sample] * m_dryWet) + read[channel][sample] * (1 - m_dryWet);
            }
        }
    }

    void Bitcrusher::releaseResources()
    {
    }

    void Bitcrusher::setAmount(double newAmt)
    {
        m_bitDepth = static_cast<int>(SDSP::KMath::Lerp<float>(32, 2, newAmt));
        m_rateReduction = static_cast<int>(SDSP::KMath::Lerp<float>(1, 50, newAmt));
        m_dryWet = static_cast<float>(newAmt);
        m_highpassCutoff = SDSP::KMath::Lerp<float>(200, 1000, newAmt);
    }

    float Bitcrusher::noisify(int channel, float sample)
    {
        auto env = m_rmsBallistics.processSample(channel, sample);
        if (env > m_noiseThreshold) {
            // rand between -1 and 1.. 
            float rand = std::rand() / static_cast<float>(RAND_MAX);
            float mapped = juce::jmap<float>(rand, 0, 1, -1, 1);
            mapped = m_noiseFilter.processSample(mapped);
            sample += (mapped * m_noiseLevel);
        }
        return sample;
    }

    void Bitcrusher::interpolateCoefficients()
    {
        for (auto& f : m_highpasses) {
            f.setCoefficients(m_coeffs.current(0), 0);
            f.setCoefficients(m_coeffs.current(1), 1);
        }
    }
}