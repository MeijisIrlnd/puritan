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
        m_vThumb = juce::ImageCache::getFromMemory(BinaryData::MixerHandle_png, BinaryData::MixerHandle_pngSize);
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

    void LF::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
    {
        using namespace juce;
        if (slider.isBar())
        {
            g.setColour(slider.findColour(Slider::trackColourId));
            g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), (float)y + 0.5f, sliderPos - (float)x, (float)height - 1.0f)
                : Rectangle<float>((float)x + 0.5f, sliderPos, (float)width - 1.0f, (float)y + ((float)height - sliderPos)));
        }
        else
        {
            auto thumbWidth = width / 4;
            auto thumbHeight = height / 6;
            int yOffset = thumbHeight / 2;
            maxSliderPos += yOffset;
            minSliderPos -= yOffset;
            auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

            auto trackWidth = jmin(6.0f, slider.isHorizontal() ? (float)height * 0.25f : (float)width * 0.25f);

            Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
                slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y - yOffset));

            Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
                slider.isHorizontal() ? startPoint.y : (float)y + (yOffset));

            Path backgroundTrack;
            backgroundTrack.startNewSubPath(startPoint);
            backgroundTrack.lineTo(endPoint);
            g.setColour(slider.findColour(Slider::backgroundColourId));
            g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            Path valueTrack;
            Point<float> minPoint, maxPoint, thumbPoint;

            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : (float)width * 0.5f,
                                   slider.isHorizontal() ? (float)height * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : maxSliderPos };
            }
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
                auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }

            //auto thumbWidth = getSliderThumbRadius(slider);


            if (!isTwoVal)
            {
                //g.setColour(slider.findColour(Slider::thumbColourId));
                auto thumbY = juce::jmin(static_cast<float>(height - yOffset), maxPoint.getY() - yOffset);
                thumbY = juce::jmax(static_cast<float>(endPoint.getY() - yOffset), thumbY - yOffset);
                juce::Rectangle<float> targetRect((width / 2.0f) - (thumbWidth / 2.0f), thumbY, static_cast<float> (thumbWidth), static_cast<float> (thumbHeight));
                g.setImageResamplingQuality(juce::Graphics::ResamplingQuality::highResamplingQuality);
                g.drawImage(m_vThumb, targetRect);
                //g.setColour(juce::Colours::red);
                //g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
            }

            if (isTwoVal || isThreeVal)
            {
                auto sr = jmin(trackWidth, (slider.isHorizontal() ? (float)height : (float)width) * 0.4f);
                auto pointerColour = slider.findColour(Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer(g, minSliderPos - sr,
                        jmax(0.0f, (float)y + (float)height * 0.5f - trackWidth * 2.0f),
                        trackWidth * 2.0f, pointerColour, 2);

                    drawPointer(g, maxSliderPos - trackWidth,
                        jmin((float)(y + height) - trackWidth * 2.0f, (float)y + (float)height * 0.5f),
                        trackWidth * 2.0f, pointerColour, 4);
                }
                else
                {
                    //drawPointer(g, jmax(0.0f, (float)x + (float)width * 0.5f - trackWidth * 2.0f),
                    //    minSliderPos - trackWidth,
                    //    trackWidth * 2.0f, pointerColour, 1);
                    //
                    //drawPointer(g, jmin((float)(x + width) - trackWidth * 2.0f, (float)x + (float)width * 0.5f), maxSliderPos - sr,
                    //    trackWidth * 2.0f, pointerColour, 3);
                }
            }
        }
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