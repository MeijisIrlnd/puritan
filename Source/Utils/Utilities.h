/*
  ==============================================================================

    Utilities.h
    Created: 20 Nov 2022 4:18:29am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Utils/Macros.h>
namespace Puritan::Utils
{
    PURITAN_UNUSED static juce::AudioBuffer<float> resampleBuffer(juce::AudioBuffer<float>& toResample, double originalSampleRate, double newSampleRate)
    {
        juce::AudioBuffer<float> resampled;
        double ratio = originalSampleRate / newSampleRate;
        resampled.setSize(toResample.getNumChannels(), static_cast<int>(toResample.getNumSamples() / ratio));
        auto* read = toResample.getArrayOfReadPointers();
        auto* write = resampled.getArrayOfWritePointers();
        for (auto channel = 0; channel < toResample.getNumChannels(); channel++) {
            juce::LagrangeInterpolator resampler;
            resampler.reset();
            resampler.process(ratio, read[channel], write[channel], resampled.getNumSamples());
        }
        return resampled;
    }

    PURITAN_UNUSED static void loadWithResample(juce::AudioFormatManager& formatManager, const juce::File& toLoad, const double sampleRate, juce::AudioBuffer<float>& destBuffer)
    {
        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(toLoad));
        juce::AudioBuffer<float> inBuffer(2, static_cast<int>(reader->lengthInSamples));
        reader->read(&inBuffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
        destBuffer = resampleBuffer(inBuffer, reader->sampleRate, sampleRate);
    }

}