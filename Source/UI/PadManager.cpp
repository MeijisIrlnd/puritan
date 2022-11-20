/*
  ==============================================================================

    PadManager.cpp
    Created: 19 Nov 2022 6:28:36pm
    Author:  Syl

  ==============================================================================
*/

#include "PadManager.h"

namespace Puritan::UI
{
    PadManager::PadManager()
    {
        setInterceptsMouseClicks(false, true);
        for (auto i = 0; i < 16; i++) {
            m_pads.emplace_back(new Pad(i));
            addAndMakeVisible(m_pads.back().get());
            m_pads.back()->addListener(this);
        }
    }

    PadManager::~PadManager()
    {
    }

    void PadManager::paint(PURITAN_UNUSED juce::Graphics& g)
    {
    }

    void PadManager::resized()
    {
        // Ok, so for now lets fit em all in normally.. 
        auto w = getWidth() / 4;
        auto h = getHeight() / 4;
        auto yMultiplier = -1;
        for (auto i = 0; i < m_pads.size(); i++) {
            yMultiplier = i % 4 == 0 ? ++yMultiplier : yMultiplier;
            auto x = w * (i % 4);
            auto y = h * yMultiplier;
            m_pads[i]->setBounds(x, y, w, h);
        }
    }

    void PadManager::onPadClicked(PURITAN_UNUSED const Pad& clickedPad)
    {
        PURITAN_UNUSED const int midiNote = clickedPad.getMidiNote();
        // So this should just schedule a midi note.. 
    }
}