/*
  ==============================================================================

    AudioFileFilter.h
    Created: 20 Nov 2022 5:36:34am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Utils/Macros.h>

namespace Puritan::Utils
{
    struct AudioFileFilter : public juce::FileFilter
    {
        AudioFileFilter(const juce::String& description) : juce::FileFilter(description) { }
        ~AudioFileFilter() override { }

        bool isFileSuitable(const juce::File& file) const override
        {
            auto ext = file.getFileExtension();
            auto it = std::find(extensions.begin(), extensions.end(), ext);
            return it != extensions.end();
        }

        bool isDirectorySuitable(PURITAN_UNUSED const juce::File& directory) const override { return true; }

        static std::array<juce::String, 5> extensions;
    };
}