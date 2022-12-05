/*
  ==============================================================================

    DragHandle.cpp
    Created: 27 Nov 2022 3:04:14pm
    Author:  Syl

  ==============================================================================
*/

#include "DragHandle.h"
#include <UI/WaveformDisplay.h>
namespace Puritan::UI
{
    DragHandle::DragHandle(const juce::Colour& handleColour) : m_handleColour(handleColour)
    {

    }

    DragHandle::~DragHandle()
    {
    }

    void DragHandle::mouseDown(const juce::MouseEvent& ev)
    {
        m_xAtDragStart = static_cast<double>(getBoundsInParent().getX());
        m_dragger.startDraggingComponent(this, ev);
        if (m_listener != nullptr) {
            m_listener->handleDragStarted(this);
        }
    }

    void DragHandle::mouseDrag(const juce::MouseEvent& ev)
    {
        m_dragger.dragComponent(this, ev, &m_constrainer);
        if (static_cast<double>(getBoundsInParent().getX()) != m_xAtDragStart) {
            dynamic_cast<WaveformDisplay*>(getParentComponent())->handleDragged(this, getBoundsInParent().getX());
            if (m_listener != nullptr) {
                m_listener->handleValueChanged(this, getBoundsInParent().getX() / static_cast<double>(getParentWidth()));
            }
        }
    }

    void DragHandle::mouseUp(PURITAN_UNUSED const juce::MouseEvent& ev)
    {
        if (m_listener != nullptr) {
            m_listener->handleDragEnded(this);
        }
    }

    void DragHandle::setValue(float newValue)
    {
        double scaledX = getParentWidth() * static_cast<double>(newValue);
        dynamic_cast<WaveformDisplay*>(getParentComponent())->handleDragged(this, scaledX);
    }

    void DragHandle::reset()
    {

    }

    void DragHandle::paint(juce::Graphics& g)
    {
        g.setColour(m_handleColour);
        g.drawLine(0, 0, 0, static_cast<float>(getHeight()), 5.0f);
    }

    void DragHandle::resized()
    {
        m_constrainer.setMinimumOnscreenAmounts(getHeight(), 5, getHeight(), 5);
    }
}