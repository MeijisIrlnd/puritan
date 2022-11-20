/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <UI/PadManager.h>
using namespace Puritan::UI;

//==============================================================================
/**
*/
class PuritanAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PuritanAudioProcessorEditor (PuritanAudioProcessor&);
    ~PuritanAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PuritanAudioProcessor& audioProcessor;
    PadManager m_padManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PuritanAudioProcessorEditor)
};
