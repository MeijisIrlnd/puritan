/*
  ==============================================================================

    LF.cpp
    Created: 19 Nov 2022 5:58:28pm
    Author:  Syl

  ==============================================================================
*/

#include "LF.h"

namespace Puritan::UI
{
    juce::Font LF::m_font = juce::Typeface::createSystemTypefaceFor(BinaryData::PixelTandysoft0rJG_ttf, BinaryData::PixelTandysoft0rJG_ttfSize);
    std::unordered_map<LF::PALETTE_COLOUR, juce::Colour> LF::m_palette;

    LF::LF()
    {
        m_rThumb = juce::ImageCache::getFromMemory(BinaryData::RotaryHandle_png, BinaryData::RotaryHandle_pngSize);
        //5E315A,8B3F5D,B96155,F3A65E,FFE577,CFFE70,8FDE5E,3CA270,3D6F70,323D4F,322946,473C78,4A5BAB,4DA6FF,66FFE3,FFFFEB,C3C2D0,7F7E8E,616070,43434F,282735,3E2346,572A4B,964252,E36856,FFB470,FE9166,EA564A,AF305B,74275D,422544,59265E,80366B,BE4882,FE6B97,FFB5B6
        setDefaultSansSerifTypeface(m_font.getTypefacePtr());
        m_primaryBackgroundColour = getPaletteColour(PALETTE_COLOUR::CREAM);
        m_primaryHighlightColour = getPaletteColour(PALETTE_COLOUR::GREY_BLUE);
        m_primaryTextColour = getPaletteColour(PALETTE_COLOUR::BLACK);
        setColour(juce::TreeView::ColourIds::backgroundColourId, m_primaryBackgroundColour);
        setColour(juce::FileBrowserComponent::ColourIds::filenameBoxBackgroundColourId, m_primaryBackgroundColour);
        setColour(juce::FileBrowserComponent::ColourIds::currentPathBoxBackgroundColourId,m_primaryBackgroundColour);
        setColour(juce::ResizableWindow::backgroundColourId, m_primaryBackgroundColour);

        setColour(juce::PopupMenu::backgroundColourId, m_primaryHighlightColour);
        setColour(juce::TreeView::ColourIds::selectedItemBackgroundColourId, m_primaryHighlightColour);
        setColour(juce::ScrollBar::thumbColourId, m_primaryHighlightColour);

        setColour(juce::Label::ColourIds::textColourId, m_primaryTextColour);
        setColour(juce::Label::ColourIds::textWhenEditingColourId, m_primaryTextColour);
        setColour(juce::TextEditor::ColourIds::textColourId, m_primaryTextColour);
        setColour(juce::ComboBox::ColourIds::textColourId, m_primaryTextColour);
        setColour(juce::DirectoryContentsDisplayComponent::ColourIds::textColourId, m_primaryTextColour);
        setColour(juce::FileBrowserComponent::ColourIds::currentPathBoxTextColourId, m_primaryTextColour);
        setColour(juce::FileBrowserComponent::ColourIds::filenameBoxTextColourId, m_primaryTextColour);
    }

    LF::~LF()
    {
    }

    void LF::drawFileBrowserRow(juce::Graphics& g, int width, int height, PURITAN_UNUSED const juce::File& file, const juce::String& filename, juce::Image* icon, const juce::String& fileSizeDescription, const juce::String& fileTimeDescription, bool isDirectory, bool isItemSelected, PURITAN_UNUSED int itemIndex, juce::DirectoryContentsDisplayComponent& dcc)
    {
        using namespace juce;
        auto fileListComp = dynamic_cast<Component*> (&dcc);

        if (isItemSelected)
            g.fillAll(fileListComp != nullptr ? fileListComp->findColour(DirectoryContentsDisplayComponent::highlightColourId)
                : findColour(DirectoryContentsDisplayComponent::highlightColourId));

        const int x = 32;
        g.setColour(Colours::black);

        if (icon != nullptr && icon->isValid())
        {
            g.drawImageWithin(*icon, 2, 2, x - 4, height - 4,
                RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                false);
        }
        else
        {
            if (auto* d = isDirectory ? getDefaultFolderImage()
                : getDefaultDocumentFileImage())
                d->drawWithin(g, Rectangle<float>(2.0f, 2.0f, x - 4.0f, (float)height - 4.0f),
                    RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
        }

        if (isItemSelected)
            g.setColour(fileListComp != nullptr ? fileListComp->findColour(DirectoryContentsDisplayComponent::highlightedTextColourId)
                : findColour(DirectoryContentsDisplayComponent::highlightedTextColourId));
        else
            g.setColour(fileListComp != nullptr ? fileListComp->findColour(DirectoryContentsDisplayComponent::textColourId)
                : findColour(DirectoryContentsDisplayComponent::textColourId));

        g.setFont(m_font);
        g.setFont((float)height * 0.7f);

        if (width > 450 && !isDirectory)
        {
            auto sizeX = roundToInt((float)width * 0.7f);
            auto dateX = roundToInt((float)width * 0.8f);

            g.drawFittedText(filename,
                x, 0, sizeX - x, height,
                Justification::centredLeft, 1);

            g.setFont((float)height * 0.5f);
            g.setColour(Colours::darkgrey);

            if (!isDirectory)
            {
                g.drawFittedText(fileSizeDescription,
                    sizeX, 0, dateX - sizeX - 8, height,
                    Justification::centredRight, 1);

                g.drawFittedText(fileTimeDescription,
                    dateX, 0, width - 8 - dateX, height,
                    Justification::centredRight, 1);
            }
        }
        else
        {
            g.drawFittedText(filename,
                x, 0, width - x, height,
                Justification::centredLeft, 1);

        }
    }
    void LF::layoutFileBrowserComponent(juce::FileBrowserComponent& browserComp, juce::DirectoryContentsDisplayComponent* fileListComponent, juce::FilePreviewComponent* previewComp, juce::ComboBox* currentPathBox, juce::TextEditor* filenameBox, juce::Button* goUpButton)
    {
        using namespace juce;
        auto sectionHeight = 22;
        auto buttonWidth = 50;

        auto b = browserComp.getLocalBounds().reduced(20, 5);

        auto topSlice = b.removeFromTop(sectionHeight);
        auto bottomSlice = b.removeFromBottom(sectionHeight);

        currentPathBox->setBounds(topSlice.removeFromLeft(topSlice.getWidth() - buttonWidth));

        topSlice.removeFromLeft(6);
        goUpButton->setBounds(topSlice);

        bottomSlice.removeFromLeft(20);
        filenameBox->setBounds(bottomSlice);
        filenameBox->applyFontToAllText(m_font.withHeight(filenameBox->getHeight() / 1.5f), true);
        if (previewComp != nullptr)
            previewComp->setBounds(b.removeFromRight(b.getWidth() / 3));

        if (auto* listAsComp = dynamic_cast<Component*> (fileListComponent))
            listAsComp->setBounds(b.reduced(0, 10));
    }

    void LF::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
    {
        using namespace juce;
        auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
        auto fill = slider.findColour(Slider::rotarySliderFillColourId);

        auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

        auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        PURITAN_UNUSED auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin(8.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
        juce::AffineTransform rotation = juce::AffineTransform::rotation(toAngle, width / 2.0f, height / 2.0f);
        m_rThumb = m_rThumb.rescaled(width, height, juce::Graphics::ResamplingQuality::highResamplingQuality);
        g.drawImageTransformed(m_rThumb, rotation);
    }
}