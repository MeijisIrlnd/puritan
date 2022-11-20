/*
  ==============================================================================

    AudioFileFIlter.cpp
    Created: 20 Nov 2022 5:30:43pm
    Author:  Syl

  ==============================================================================
*/

#include "AudioFileFIlter.h"

namespace Puritan::Utils
{
    std::array<juce::String, 5> AudioFileFilter::extensions = { ".wav", ".mp3", ".ogg", ".aiff", ".flac" };
}