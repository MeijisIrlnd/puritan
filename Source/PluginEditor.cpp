/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PuritanAudioProcessorEditor::PuritanAudioProcessorEditor (PuritanAudioProcessor& p)
    : m_audioFileFilter(juce::String("Filter for audio files")), AudioProcessorEditor(&p), audioProcessor(p), m_fileBrowser(juce::FileBrowserComponent::FileChooserFlags::openMode | juce::FileBrowserComponent::FileChooserFlags::canSelectFiles | juce::FileBrowserComponent::FileChooserFlags::useTreeView, juce::File(), &m_audioFileFilter, nullptr)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 1000);
    setLookAndFeel(&m_lf);
    addAndMakeVisible(&m_padManager);
    m_fileBrowser.setLookAndFeel(&m_lf);
    addAndMakeVisible(&m_fileBrowser);
    m_fileBrowser.addListener(this);
}

PuritanAudioProcessorEditor::~PuritanAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void PuritanAudioProcessorEditor::selectionChanged()
{
    auto file = m_fileBrowser.getHighlightedFile();
    if (file.existsAsFile()) {
        PuritanAudioProcessor::getInstance()->getPreviewPlayer()->play(file);
    }
}

void PuritanAudioProcessorEditor::fileClicked(const juce::File& file, PURITAN_UNUSED const juce::MouseEvent& e)
{
    if (file.existsAsFile()) {
        PuritanAudioProcessor::getInstance()->getPreviewPlayer()->play(file);
    }
}

void PuritanAudioProcessorEditor::fileDoubleClicked(PURITAN_UNUSED const juce::File& file)
{
}

void PuritanAudioProcessorEditor::browserRootChanged(PURITAN_UNUSED const juce::File& newRoot)
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
    m_fileBrowser.setBounds(0, 0, getWidth() / 3, getHeight());
    m_padManager.setBounds(getWidth() / 3, 10, static_cast<int>(getWidth() * 0.666666666), getHeight());
}
