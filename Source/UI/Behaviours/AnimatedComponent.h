/*
  ==============================================================================

    AnimatedComponent.h
    Created: 19 Nov 2022 6:07:09pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace Puritan::UI::Behaviours
{
    class AnimatedComponent : public juce::Component, public juce::Timer
    {
    public:
        AnimatedComponent() {
            startTimerHz(60);
        }
        
        void timerCallback() override {
            repaint();
        }

        virtual ~AnimatedComponent() override {
            stopTimer();
        }

        virtual void paint(juce::Graphics& g) override = 0;
        virtual void resized() override = 0;

    };
}