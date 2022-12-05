/*
  ==============================================================================

    PadMixArea.cpp
    Created: 27 Nov 2022 6:00:12pm
    Author:  Syl

  ==============================================================================
*/

#include "PadMixArea.h"
#include <PluginProcessor.h>
namespace Puritan::UI
{
    PadMixArea::PadMixArea(const int index) : m_index(index)
    {
        auto* tree = PuritanAudioProcessor::getInstance()->getTree();
        m_volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
        m_volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(&m_volumeSlider);
        m_volumeSliderAttachment.reset(new juce::SliderParameterAttachment(*tree->getParameter(fmt::format("Pad{}_Volume", m_index)), m_volumeSlider, nullptr));
    }

    PadMixArea::~PadMixArea()
    {
    }

    void PadMixArea::paint(PURITAN_UNUSED juce::Graphics& g)
    {
    }

    void PadMixArea::resized()
    {
        m_volumeSlider.setBounds(getWidth() / 16, getHeight() / 32, getWidth() / 3, getHeight() - getHeight() / 16);
    }
}
