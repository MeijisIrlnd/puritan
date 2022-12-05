/*
  ==============================================================================

    PadManager.cpp
    Created: 19 Nov 2022 6:28:36pm
    Author:  Syl

  ==============================================================================
*/

#include "PadManager.h"
#include <PluginProcessor.h>
#include <PluginEditor.h>
namespace Puritan::UI
{
    PadManager::PadManager()
    {
        setInterceptsMouseClicks(false, true);
        for (auto i = 0; i < 16; i++) {
            m_pads.emplace_back(new Pad(i, i));
            addAndMakeVisible(m_pads.back().get());
            m_pads.back()->addListener(this);
            m_padControls.emplace_back(new PadControls(i));
            addAndMakeVisible(m_padControls.back().get());
            m_padControls.back()->setVisible(false);
            m_padMixAreas.emplace_back(new PadMixArea(i));
            addAndMakeVisible(m_padMixAreas.back().get());
            m_padMixAreas.back()->setVisible(false);
        }
        m_padControls.back()->setVisible(true);
        m_padMixAreas.back()->setVisible(true);
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
        // 2/3 width height is for pads, remaining 3rd is pad controls...
        auto padControlsWidth = static_cast<int>(getWidth() * 0.6666666);
        auto padControlsHeight =static_cast<int>(getWidth() * 0.6666666);
        auto w = static_cast<int>(padControlsWidth / 4);
        auto h = static_cast<int>(padControlsHeight / 4);
        auto yMultiplier = -1;
        auto wDelta = static_cast<int>(getWidth() - padControlsWidth);
        // pads need to be offset by width - 23rds width
        for (auto i = 0; i < m_pads.size(); i++) {
            yMultiplier = i % 4 == 0 ? ++yMultiplier : yMultiplier;
            auto x = w * (i % 4);
            auto y = h * yMultiplier;
            m_pads[i]->setBounds(x + wDelta, y, w, h);
        }
        for (auto i = 0; i < m_padControls.size(); i++) {
            m_padControls[i]->setBounds(wDelta, padControlsHeight, padControlsWidth, getHeight() - padControlsHeight);
        }
        for (auto i = 0; i < m_padMixAreas.size(); i++) {
            m_padMixAreas[i]->setBounds(0, getHeight() / 2, wDelta, getHeight() / 2);
        }
    }


    void PadManager::onPadClicked(const Pad& clickedPad)
    {
        auto index = clickedPad.getIndex();
        PuritanAudioProcessor::getInstance()->triggerPad(index);
        for (auto i = 0; i < m_padControls.size(); i++) {
            m_padControls[i]->setVisible(false);
        }
        for (auto i = 0; i < m_padMixAreas.size(); i++) {
            m_padMixAreas[i]->setVisible(false);
        }
        m_padControls[index]->setVisible(true);
        m_padMixAreas[index]->setVisible(true);
    }

    void PadManager::fileDroppedOnPad(Pad& pad, const juce::File& f)
    {
        auto index = pad.getIndex();
        PuritanAudioProcessor::getInstance()->loadToPad(index, f);
        pad.set(PuritanAudioProcessor::getInstance()->getPadInfo(index));
    }
}