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
    PadControls::PadControls() : m_thumbnailCache(5), m_thumbnail(512, *PuritanAudioProcessor::getInstance()->getFormatManager(), m_thumbnailCache)
    {
        m_nameReadout.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(&m_nameReadout);
        m_thumbnail.addChangeListener(this);
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

    void PadControls::changeListenerCallback(PURITAN_UNUSED juce::ChangeBroadcaster* source)
    {
        repaint();
    }

    void PadControls::setSelectedPad(const int newPadIndex)
    {
        m_selectedPadIndex = newPadIndex;
        m_linkedPadInfo = PuritanAudioProcessor::getInstance()->getPadInfo(newPadIndex);
        if (m_linkedPadInfo.get() != nullptr) {
            m_nameReadout.setText(m_linkedPadInfo->name, juce::dontSendNotification);
            m_thumbnail.setSource(new juce::FileInputSource(juce::File(m_linkedPadInfo->path)));
        }
    }

    void PadControls::onSampleChanged(int index, std::shared_ptr<PadInfo> newPadInfo)
    {
        if (index != m_selectedPadIndex) return;
        m_linkedPadInfo = newPadInfo;
        if (m_linkedPadInfo.get() != nullptr) {
            m_nameReadout.setText(m_linkedPadInfo->name, juce::dontSendNotification);
            m_thumbnail.setSource(new juce::FileInputSource(juce::File(m_linkedPadInfo->path)));
        }
    }

    void PadControls::paint(juce::Graphics& g)
    {
        juce::Rectangle<int> thumbnailBounds(0, getHeight() / 12, getWidth(), getHeight() / 3);
        if (m_thumbnail.getNumChannels() == 0) {
            paintNoThumbnail(g, thumbnailBounds);
        }
        else {
            paintThumbnail(g, thumbnailBounds);
        }
    }

    void PadControls::resized()
    {
        m_nameReadout.setBounds(0, 0, getWidth(), getHeight() / 12);
    }

    void PadControls::paintNoThumbnail(juce::Graphics& g, juce::Rectangle<int>& bounds)
    {
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::BLACK));
        g.drawRect(bounds);
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::BLACK));
        g.setFont(LF::getFont(14.0f));
        g.drawFittedText("No File Loaded", bounds, juce::Justification::centred, 1);
    }

    void PadControls::paintThumbnail(juce::Graphics& g, juce::Rectangle<int>& bounds)
    {
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::BLACK));
        g.drawRect(bounds);
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::PURPLE_H));
        m_thumbnail.drawChannels(g, bounds, 0.0, m_thumbnail.getTotalLength(), 1.0f);
    }
}