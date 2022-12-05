/*
  ==============================================================================

    Shader.h
    Created: 4 Dec 2022 4:53:17pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Puritan::UI::Shaders
{
    class Shader : public juce::Component, public juce::Timer
    {
    public: 
        Shader(const int w, const int h) { 
            startTimerHz(60);
            m_frontBuffer = juce::Image(juce::Image::PixelFormat::ARGB, w, h, true);
        }
        virtual ~Shader() override {
            stopTimer();
        } 
        void timerCallback() override {
            repaint();
        }
        virtual void paint(juce::Graphics& g) override = 0;
        virtual void resized() override {} 
    protected: 
        juce::Image m_frontBuffer, m_backBuffer;
    };
}