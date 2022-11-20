/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PuritanAudioProcessorEditor::PuritanAudioProcessorEditor (PuritanAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 800);
    addAndMakeVisible(&m_padManager);
}

PuritanAudioProcessorEditor::~PuritanAudioProcessorEditor()
{
}

//==============================================================================
void PuritanAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void PuritanAudioProcessorEditor::resized()
{
    m_padManager.setBounds(0, 0, getWidth(), getHeight());
    //m_testGif.setBounds(0, 0, getWidth(), getHeight());
}
