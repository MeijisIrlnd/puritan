/*
  ==============================================================================

    LF.h
    Created: 19 Nov 2022 5:58:28pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace Puritan::UI
{
    class LF : public juce::LookAndFeel_V4
    {
    public:
        LF();
        ~LF() override;
    };
}