/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 27 Nov 2022 2:49:22pm
    Author:  Syl

  ==============================================================================
*/

#include <fmt/core.h>
#include "WaveformDisplay.h"
#include <PluginProcessor.h>
#include <UI/PadControls.h>
#include <UI/LF.h>
namespace Puritan::UI
{
    WaveformDisplay::WaveformDisplay(const int index) : m_index(index), m_thumbnailCache(5),
        m_thumbnail(512, *PuritanAudioProcessor::getInstance()->getFormatManager(), m_thumbnailCache),
        m_startHandle(LF::getPaletteColour(LF::PALETTE_COLOUR::LIME_A)),
        m_endHandle(LF::getPaletteColour(LF::PALETTE_COLOUR::ORANGE_A))
    {
        addAndMakeVisible(&m_startHandle);
        addAndMakeVisible(&m_endHandle);
        m_thumbnail.addChangeListener(this);
    }

    WaveformDisplay::~WaveformDisplay()
    {
    }

    void WaveformDisplay::setup()
    {
        if (!m_hasBeenSetup) {
            std::string padName = fmt::format("Pad{}", m_index);
            auto* tree = PuritanAudioProcessor::getInstance()->getTree();
            m_startHandleAttachment.reset(new DragHandleParameterAttachment(*tree->getParameter(fmt::format("{}_StartTime", padName)), m_startHandle, nullptr));
            m_endHandleAttachment.reset(new DragHandleParameterAttachment(*tree->getParameter(fmt::format("{}_EndTime", padName)), m_endHandle, nullptr));
            m_hasBeenSetup = true;
        }
    }

    void WaveformDisplay::changeListenerCallback(PURITAN_UNUSED juce::ChangeBroadcaster* source)
    {
        repaint();
        resized();
    }

    void WaveformDisplay::setSource(const juce::File& f)
    {
        m_thumbnail.setSource(new juce::FileInputSource(f));
    }

    void WaveformDisplay::handleDragged(DragHandle* dragged, double newValue)
    {
        if (dragged == &m_startHandle) {
            if (newValue >= m_endHandle.getBounds().getX()) {
                dragged->setBounds(m_endHandle.getX() - 5, 0, 5, getHeight());
            }
        }
        else {
            if (newValue <= m_startHandle.getBounds().getX()) {
                dragged->setBounds(m_startHandle.getX() + 5, 0, 5, getHeight());
            }
        }
    }

    void WaveformDisplay::paint(juce::Graphics& g)
    {
        juce::Rectangle<int> thumbnailBounds(0, 0, getWidth(), getHeight());
        if (m_thumbnail.getNumChannels() == 0) {
            paintNoThumbnail(g, thumbnailBounds);
        }
        else {
            paintThumbnail(g, thumbnailBounds);
        }
    }

    void WaveformDisplay::resized()
    {
        if (m_thumbnail.getNumChannels() != 0) {
            m_startHandle.setBounds(0, 1, 5, getHeight() - 2);
            m_endHandle.setBounds(getWidth() - 5, 1, 5, getHeight() - 2);
            setup();
        }
    }
    void WaveformDisplay::paintNoThumbnail(juce::Graphics& g, juce::Rectangle<int>& bounds)
    {
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::BLACK));
        g.drawRect(bounds);
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::BLACK));
        g.setFont(LF::getFont(14.0f));
        g.drawFittedText("No File Loaded", bounds, juce::Justification::centred, 1);
    }

    void WaveformDisplay::paintThumbnail(juce::Graphics& g, juce::Rectangle<int>& bounds)
    {
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::BLACK));
        g.drawRect(bounds);
        g.setColour(LF::getPaletteColour(LF::PALETTE_COLOUR::GREY_B));
        m_thumbnail.drawChannels(g, bounds, 0.0, m_thumbnail.getTotalLength(), 1.0f);
    }
}