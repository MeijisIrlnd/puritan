/*
  ==============================================================================

    Pad.cpp
    Created: 19 Nov 2022 5:52:59pm
    Author:  Syl

  ==============================================================================
*/

#include "Pad.h"
#include <PluginEditor.h>
namespace Puritan::UI
{
    Pad::Pad(const int midiNote, const int index) : m_gif(juce::MemoryBlock(BinaryData::pad_press_128_128_gif, BinaryData::pad_press_128_128_gifSize)),
        m_midiNote(midiNote), m_index(index)
    {
        m_nameDisplay.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(&m_nameDisplay);
        m_gif.setInterceptsMouseClicks(false, false);
        addAndMakeVisible(&m_gif);
        m_gif.addListener(this);

    }

    Pad::~Pad()
    {

    }

    void Pad::gifPlaybackFinished()
    {
        m_gif.stop();
    }

    bool Pad::isInterestedInDragSource(PURITAN_UNUSED const SourceDetails& dragSourceDetails)
    {
        auto* editor = static_cast<PuritanAudioProcessorEditor*>(getParentComponent()->getParentComponent());
        auto draggedFile = editor->getFileBrowser()->getHighlightedFile();
        auto it = std::find(Utils::AudioFileFilter::extensions.begin(), Utils::AudioFileFilter::extensions.end(), draggedFile.getFileExtension());
        return it != Utils::AudioFileFilter::extensions.end();
    }

    void Pad::itemDropped(PURITAN_UNUSED const SourceDetails& dragSourceDetails)
    {
        auto* editor = static_cast<PuritanAudioProcessorEditor*>(getParentComponent()->getParentComponent());
        auto draggedFile = editor->getFileBrowser()->getHighlightedFile();
        if (m_listener != nullptr) {
            m_listener->fileDroppedOnPad(*this, draggedFile);
        }
    }

    void Pad::mouseUp(PURITAN_UNUSED const juce::MouseEvent& ev)
    {
        // Trigger sample, also flash the pad..
        if (m_listener != nullptr) {
            m_listener->onPadClicked(*this);
        }
        m_gif.start();
    }

    void Pad::paint(PURITAN_UNUSED juce::Graphics& g)
    {
    }

    void Pad::resized()
    {
        m_nameDisplay.setBounds(0, getHeight() - getHeight() / 12, getWidth(), getHeight() / 12);
        m_gif.setBounds(0, 0, getWidth(), getHeight());
    }

    void Pad::set(std::shared_ptr<PadInfo> padInfo)
    {
        m_associatedPadInfo = padInfo;
        m_nameDisplay.setText(m_associatedPadInfo->name, juce::dontSendNotification);


    }
}