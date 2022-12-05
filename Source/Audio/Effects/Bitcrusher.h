/*
  ==============================================================================

    Bitcrusher.h
    Created: 4 Dec 2022 6:10:18pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Utils/Macros.h>
namespace Puritan::Audio::Effects
{
    class Bitcrusher
    {
    public: 
        Bitcrusher();
        ~Bitcrusher();
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
        void releaseResources();
        void setAmount(double newAmt);
    private: 
        float noisify(int channel, float sample);
        void interpolateCoefficients();

        double m_sampleRate;
        juce::dsp::BallisticsFilter<float> m_rmsBallistics;
        int m_rateReduction = 1, m_bitDepth = 32;
        float m_noiseLevel = 0.04f, m_noiseThreshold = 0.8f, m_dryWet{0.5f};
        const int m_updateRate = 100;
        int m_samplesUntilUpdate = 0;
        SDSP::BiquadCascade<1> m_noiseFilter;
        std::vector<SDSP::BiquadCascade<2>> m_highpasses;
        SDSP::SmoothedFilterCoefficients<1> m_noiseCoeffs;
        SDSP::SmoothedFilterCoefficients<2> m_coeffs;
        double m_highpassCutoff{ 1000 };

        juce::AudioBuffer<float> m_processBuffer;
    };
}