/*
  ==============================================================================

    PuritanMath.h
    Created: 19 Nov 2022 6:03:08pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
namespace Puritan
{
    template <typename T> 
    static T lerp(T start, T end, double t)
    {
        return start + (end - start) * t;
    }
}