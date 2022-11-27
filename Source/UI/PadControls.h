/*
  ==============================================================================

    PadControls.h
    Created: 20 Nov 2022 10:22:58pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Audio/PadPlayer.h>
#include <UI/WaveformDisplay.h>

namespace Puritan::UI
{
    class PadControls : public juce::Component, public Audio::PadPlayer::Listener
    {
    public: 
        PadControls(const int index);
        ~PadControls() override;
        void onSampleChanged(int index, std::shared_ptr<PadInfo> newPadInfo) override;
        void startTimeChanged(double normalisedPos);
        void endTimeChanged(double normalisedPos);
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        int m_index;

        std::shared_ptr<PadInfo> m_linkedPadInfo{ nullptr };
        juce::Label m_nameReadout;
        WaveformDisplay m_waveformDisplay;
        std::pair<int, int> m_keyRange;
        juce::Slider m_panSlider;
        std::unique_ptr<juce::SliderParameterAttachment> m_panSliderAttachment;
        juce::Label m_panLabel;
    };
}