/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <UI/PadManager.h>
#include <Utils/AudioFileFilter.h>
using namespace Puritan::UI;

//==============================================================================
/**
*/
class PuritanAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::FileBrowserListener
{
public:
    PuritanAudioProcessorEditor (PuritanAudioProcessor&);
    ~PuritanAudioProcessorEditor() override;

    void selectionChanged() override;
    void fileClicked(const juce::File& file, const juce::MouseEvent& e) override;
    void fileDoubleClicked(const juce::File& file) override;
    void browserRootChanged(const juce::File& newRoot) override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;



private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PuritanAudioProcessor& audioProcessor;
    PadManager m_padManager;
    juce::FileBrowserComponent m_fileBrowser;
    const Puritan::Utils::AudioFileFilter m_audioFileFilter;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PuritanAudioProcessorEditor)
};
