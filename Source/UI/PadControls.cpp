/*
  ==============================================================================

    PadControls.cpp
    Created: 20 Nov 2022 10:22:58pm
    Author:  Syl

  ==============================================================================
*/

#include "PadControls.h"
#include <PluginProcessor.h>
#include <UI/LF.h>
namespace Puritan::UI
{
    PadControls::PadControls()
    {
        for (auto& player : *PuritanAudioProcessor::getInstance()->getPadPlayers())
        {
            player->addListener(this);
        }
    }

    PadControls::~PadControls()
    {
        for (auto& player : *PuritanAudioProcessor::getInstance()->getPadPlayers())
        {
            player->removeListener();
        }
    }

    void PadControls::setSelectedPad(const int newPadIndex)
    {
        m_selectedPadIndex = newPadIndex;
        m_linkedPadInfo = PuritanAudioProcessor::getInstance()->getPadInfo(newPadIndex);
    }

    void PadControls::onSampleChanged(PURITAN_UNUSED int index, PURITAN_UNUSED std::shared_ptr<PadInfo> newPadInfo)
    {
        if (index != m_selectedPadIndex) return;
        m_linkedPadInfo = newPadInfo;
        DBG(m_linkedPadInfo->name);
    }

    void PadControls::paint(juce::Graphics& g)
    {
        g.fillAll(LF::getPaletteColour(LF::PALETTE_COLOUR::BURNT_SIENNA));
    }

    void PadControls::resized()
    {
    }
}