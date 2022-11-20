/*
  ==============================================================================

    PadInfo.h
    Created: 19 Nov 2022 6:18:07pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <string>
#include <JuceHeader.h>
#include <Utils/Utilities.h>
namespace Puritan
{
    struct PadInfo
    {
        std::string name;
        std::string path;
        juce::AudioBuffer<float> audioData;

        PadInfo() = default;
        PadInfo(const juce::File& f);
    };
}