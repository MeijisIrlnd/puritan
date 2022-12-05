/*
  ==============================================================================

    DragHandle.h
    Created: 27 Nov 2022 3:04:14pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Utils/Macros.h>
namespace Puritan::UI
{
    class DragHandle : public juce::Component
    {
    public: 
        struct Listener
        {
            virtual ~Listener() { }
            virtual void handleValueChanged(DragHandle* source, double newX) = 0;
            virtual void handleDragStarted(DragHandle* source) = 0;
            virtual void handleDragEnded(DragHandle* source) = 0;
        };
        DragHandle(const juce::Colour& handleColour);
        ~DragHandle() override;
        PURITAN_INLINE void addListener(Listener* newListener) {
            m_listener = newListener;
        }

        void mouseDown(const juce::MouseEvent& ev) override;
        void mouseDrag(const juce::MouseEvent& ev) override;
        void mouseUp(PURITAN_UNUSED const juce::MouseEvent& ev) override;
        void setValue(float newValue);
        void reset();
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        juce::ComponentBoundsConstrainer m_constrainer;
        juce::ComponentDragger m_dragger;
        double m_xAtDragStart{ 0 };
        juce::Colour m_handleColour;
        Listener* m_listener{ nullptr };
    };
}