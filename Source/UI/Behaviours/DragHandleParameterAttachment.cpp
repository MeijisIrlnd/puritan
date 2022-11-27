/*
  ==============================================================================

    DragHandleParameterAttachment.cpp
    Created: 27 Nov 2022 4:14:46pm
    Author:  Syl

  ==============================================================================
*/

#include "DragHandleParameterAttachment.h"

namespace Puritan::UI
{
    DragHandleParameterAttachment::DragHandleParameterAttachment(juce::RangedAudioParameter& parameter, DragHandle& dragHandle, juce::UndoManager* undoManager) 
        : m_attachment(parameter, [this](float x) {setValue(x); }, undoManager), m_dragHandle(dragHandle)
    {
        sendInitialUpdate();
        m_dragHandle.addListener(this);
    }

    DragHandleParameterAttachment::~DragHandleParameterAttachment()
    {

    }

    void DragHandleParameterAttachment::sendInitialUpdate()
    {
        m_attachment.sendInitialUpdate();
    }

    void DragHandleParameterAttachment::handleValueChanged(PURITAN_UNUSED DragHandle* source, double newX)
    {
        if (!m_ignoreCallbacks) {
            m_attachment.setValueAsPartOfGesture(static_cast<float>(newX));
        }
    }

    void DragHandleParameterAttachment::handleDragStarted(PURITAN_UNUSED DragHandle* source)
    {
        m_attachment.beginGesture();
    }

    void DragHandleParameterAttachment::handleDragEnded(PURITAN_UNUSED DragHandle* source)
    {
        m_attachment.endGesture();
    }

    void DragHandleParameterAttachment::setValue(float newValue)
    {
        juce::ScopedValueSetter<bool> svs(m_ignoreCallbacks, true);
        m_dragHandle.setValue(newValue);
        
    }
}