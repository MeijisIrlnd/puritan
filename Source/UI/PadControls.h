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

namespace Puritan::UI
{
    class PadControls : public juce::Component, public Audio::PadPlayer::Listener
    {
    public: 
        PadControls();
        ~PadControls() override;
        void setSelectedPad(const int newPadIndex);
        void onSampleChanged(int index, std::shared_ptr<PadInfo> newPadInfo) override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        int m_selectedPadIndex{0};
        std::shared_ptr<PadInfo> m_linkedPadInfo{ nullptr };
    };
}