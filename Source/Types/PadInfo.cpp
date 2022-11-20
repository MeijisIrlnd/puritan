/*
  ==============================================================================

    PadInfo.cpp
    Created: 20 Nov 2022 5:44:25pm
    Author:  Syl

  ==============================================================================
*/

#include "PadInfo.h"
#include <PluginProcessor.h>
namespace Puritan
{
    PadInfo::PadInfo(const juce::File& f) : path(f.getFullPathName().toStdString())
    {
        name = f.getFileNameWithoutExtension().toStdString();
        auto sr = PuritanAudioProcessor::getInstance()->getSampleRate();
        auto* formatManager = PuritanAudioProcessor::getInstance()->getFormatManager();
        Utils::loadWithResample(*formatManager, f, sr, audioData);
    }
}