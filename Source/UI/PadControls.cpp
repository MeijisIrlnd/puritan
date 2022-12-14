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
    PadControls::PadControls(const int index) : m_index(index),
        m_keyRange(m_index, m_index), m_waveformDisplay(index)
    {
        auto* tree = PuritanAudioProcessor::getInstance()->getTree();
        m_nameReadout.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(&m_nameReadout);
        m_panLabel.setText("Pan", juce::dontSendNotification);
        m_panLabel.setJustificationType(juce::Justification::centred);
        m_panSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        m_panSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        m_panLabel.attachToComponent(&m_panSlider, false);
        addAndMakeVisible(&m_panSlider);
        m_panSliderAttachment.reset(new juce::SliderParameterAttachment(*tree->getParameter(fmt::format("Pad{}_Pan", m_index)), m_panSlider, nullptr));
        m_bitcrushLabel.setText("FUCK", juce::dontSendNotification);
        m_bitcrushLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(&m_bitcrushLabel);
        m_bitcrushSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        m_bitcrushSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(&m_bitcrushSlider);
        m_bitcrushLabel.attachToComponent(&m_bitcrushSlider, false);
        m_bitcrushAttachment.reset(new juce::SliderParameterAttachment(*tree->getParameter(fmt::format("Pad{}_BitcrushAmount", m_index)), m_bitcrushSlider, nullptr));
        addAndMakeVisible(&m_waveformDisplay);
        PuritanAudioProcessor::getInstance()->getPadPlayers()->at(m_index)->addListener(this);
    }

    PadControls::~PadControls()
    {
        for (auto& player : *PuritanAudioProcessor::getInstance()->getPadPlayers())
        {
            player->removeListener();
        }
    }

    void PadControls::startTimeChanged(double normalisedPos)
    {
        PuritanAudioProcessor::getInstance()->getPadPlayers()->at(m_index)->setStart(normalisedPos);
    }

    void PadControls::endTimeChanged(double normalisedPos)
    {
        PuritanAudioProcessor::getInstance()->getPadPlayers()->at(m_index)->setEnd(normalisedPos);
    }


    void PadControls::onSampleChanged(PURITAN_UNUSED int index, std::shared_ptr<PadInfo> newPadInfo)
    {
        m_linkedPadInfo = newPadInfo;
        if (m_linkedPadInfo.get() != nullptr) {
            m_nameReadout.setText(m_linkedPadInfo->name, juce::dontSendNotification);
            m_waveformDisplay.setSource(juce::File(m_linkedPadInfo->path));
        }
    }

    void PadControls::paint(PURITAN_UNUSED juce::Graphics& g)
    {
    }

    void PadControls::resized()
    {
        m_nameReadout.setBounds(0, 0, getWidth(), getHeight() / 12);
        m_waveformDisplay.setBounds(0, getHeight() / 12, getWidth(), getHeight() / 3);
        m_panSlider.setBounds(0, getHeight() / 12 + getHeight() / 12 + getHeight() / 3, getWidth() / 16, getWidth() / 16);
        m_bitcrushSlider.setBounds(getWidth() / 8, m_panSlider.getY(), getWidth() / 16, getWidth() / 16);
    }

}