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
namespace Puritan
{
    struct PadInfo
    {
        std::string name;
        std::string path;
        juce::AudioBuffer<float> audioData;

        PadInfo() = default;
        PadInfo(const std::string& path_) : path(path_)
        {
            // Load here..
        }
    };
}