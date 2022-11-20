/*
  ==============================================================================

    Pad.cpp
    Created: 19 Nov 2022 5:52:59pm
    Author:  Syl

  ==============================================================================
*/

#include "Pad.h"

namespace Puritan::UI
{
    Pad::Pad(const int midiNote) : m_gif(juce::MemoryBlock(BinaryData::pad_press_128_128_gif, BinaryData::pad_press_128_128_gifSize)),
        m_midiNote(midiNote)
    {
        m_nameDisplay.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(&m_nameDisplay);
        m_gif.setInterceptsMouseClicks(false, false);
        addAndMakeVisible(&m_gif);
        m_gif.addListener(this);

    }

    Pad::~Pad()
    {

    }

    void Pad::gifPlaybackFinished()
    {
        m_gif.stop();
    }

    void Pad::mouseUp(PURITAN_UNUSED const juce::MouseEvent& ev)
    {
        // Trigger sample, also flash the pad..
        if (m_listener != nullptr) {
            m_listener->onPadClicked(*this);
        }
        m_gif.start();
    }

    void Pad::paint(PURITAN_UNUSED juce::Graphics& g)
    {
    }

    void Pad::resized()
    {
        m_nameDisplay.setBounds(0, getHeight() - getHeight() / 12, getWidth(), getHeight() / 12);
        m_gif.setBounds(0, 0, getWidth(), getHeight());
    }

    void Pad::set(std::shared_ptr<PadInfo> padInfo)
    {
        m_associatedPadInfo = padInfo;
        m_nameDisplay.setText(m_associatedPadInfo->name, juce::dontSendNotification);


    }
}