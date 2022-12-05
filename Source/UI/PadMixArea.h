/*
  ==============================================================================

    PadMixArea.h
    Created: 27 Nov 2022 6:00:12pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Puritan::UI
{
    class PadMixArea : public juce::Component
    {
    public: 
        PadMixArea(const int index);
        ~PadMixArea() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        const int m_index;
        juce::Slider m_volumeSlider;
        std::unique_ptr<juce::SliderParameterAttachment> m_volumeSliderAttachment;
    };
} 
