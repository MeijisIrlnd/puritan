/*
  ==============================================================================

    DragHandleParameterAttachment.h
    Created: 27 Nov 2022 4:14:46pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <UI/DragHandle.h>
#include <Utils/Macros.h>
namespace Puritan::UI
{
    class DragHandleParameterAttachment : public DragHandle::Listener
    {
    public: 
        DragHandleParameterAttachment(juce::RangedAudioParameter& parameter, DragHandle& dragHandle, juce::UndoManager* undoManager = nullptr);
        ~DragHandleParameterAttachment() override;
        void sendInitialUpdate();
        void handleValueChanged(PURITAN_UNUSED DragHandle* source, double newX) override;
        void handleDragStarted(PURITAN_UNUSED DragHandle* source) override;
        void handleDragEnded(PURITAN_UNUSED DragHandle* source) override;
        void setValue(float newValue);
    private:
        juce::ParameterAttachment m_attachment;
        DragHandle& m_dragHandle;
        bool m_ignoreCallbacks{ false };
    };
}