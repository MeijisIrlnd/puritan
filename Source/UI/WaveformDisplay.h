/*
  ==============================================================================

    WaveformDisplay.h
    Created: 27 Nov 2022 2:49:22pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <UI/DragHandle.h>
#include <UI/Behaviours/DragHandleParameterAttachment.h>
namespace Puritan::UI
{
    class WaveformDisplay : public juce::Component, public juce::ChangeListener
    {
    public: 
        WaveformDisplay(const int index);
        ~WaveformDisplay() override;
        // Called after resized..
        void setup();
        void changeListenerCallback(PURITAN_UNUSED juce::ChangeBroadcaster* source) override;
        void setSource(const juce::File& f);
        void handleDragged(DragHandle* dragged, double newValue);
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        void paintNoThumbnail(juce::Graphics& g, juce::Rectangle<int>& bounds);
        void paintThumbnail(juce::Graphics& g, juce::Rectangle<int>& bounds);
        const int m_index;
        bool m_hasBeenSetup{ false };
        juce::AudioThumbnailCache m_thumbnailCache;
        juce::AudioThumbnail m_thumbnail;
        DragHandle m_startHandle, m_endHandle;
        std::unique_ptr<DragHandleParameterAttachment> m_startHandleAttachment, m_endHandleAttachment;
    };
}