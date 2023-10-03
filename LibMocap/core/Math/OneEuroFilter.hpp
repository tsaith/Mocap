
#pragma once

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <ctime>

#include "Core/Math/MathLib.h"

namespace one_euro {

static const double UndefinedTime = -1.0 ;

class LowPassFilter {
    
  double y, a, s ;
  bool initialized ;

  void SetAlpha(double alpha) {

    if (alpha<=0.0 || alpha>1.0) 
      throw std::range_error("alpha should be in (0.0., 1.0]") ;

    a = alpha ;

  }

public:

  LowPassFilter(double alpha, double initval=0.0) {

    y = s = initval ;
    SetAlpha(alpha) ;
    initialized = false ;

  }

  double Filter(double value) {

    double result ;
    if (initialized)
      result = a*value + (1.0-a)*s ;
    else {
      result = value ;
      initialized = true ;
    }
    y = value ;
    s = result ;

    return result ;

  }

  double FilterWithAlpha(double value, double alpha) {

    SetAlpha(alpha) ;
    return Filter(value) ;

  }

  bool HasLastRawValue(void) {
    return initialized ;
  }

  double LastRawValue(void) {
    return y ;
  }

};


class OneEuroFilter {

public:

  OneEuroFilter() {
  }

  void Init(double Freq0, double MinCutoff=1.0, double Beta=0.0, double DCutoff=1.0) {

    mFreq = Freq0;
    SetMinCutoff(MinCutoff);
    SetBeta(Beta);
    SetDerivativeCutoff(DCutoff);
    mX = new LowPassFilter(alpha(MinCutoff));
    mDx = new LowPassFilter(alpha(DCutoff));
    mLastTime = UndefinedTime;

  }

  double Filter(double Value, double Timestamp=UndefinedTime) {

    // update the sampling frequency based on timestamps
    if (mLastTime!=UndefinedTime && Timestamp!=UndefinedTime) {
      mFreq = 1.0 / (Timestamp - mLastTime);
    }

    mLastTime = Timestamp;
    // estimate the current variation per second 
    double dvalue = mX->HasLastRawValue() ? (Value - mX->LastRawValue())*mFreq : 0.0 ; // FIXME: 0.0 or value?
    double edvalue = mDx->FilterWithAlpha(dvalue, alpha(mDcutoff)) ;
    // use it to update the cutoff frequency
    double cutoff = mMinCutoff + mBeta*fabs(edvalue) ;
    // filter the given value
    return mX->FilterWithAlpha(Value, alpha(cutoff)) ;

  }

  ~OneEuroFilter(void) {
    delete mX;
    delete mDx;
  }


private:

  double mFreq ;
  double mMinCutoff ;
  double mBeta;
  double mDcutoff ;
  LowPassFilter *mX ;
  LowPassFilter *mDx ;
  double mLastTime;

  double alpha(double cutoff) {

    double te = 1.0 / mFreq;
    double tau = 1.0 / (2*M_PI*cutoff);
    return 1.0 / (1.0 + tau/te);

  }

  void SetMinCutoff(double mc) {

    if (mc<=0) throw std::range_error("mMinCutoff should be >0");
    mMinCutoff = mc;

  }

  void SetBeta(double b) {
    mBeta = b ;
  }

  void SetDerivativeCutoff(double dc) {

    if (dc<=0) throw std::range_error("Derivative cutoff should be greater than zero.");
    mDcutoff = dc;

  }


};

} // namespace


/* -*- coding: utf-8 -*-
 *
 * Author: Nicolas Roussel (nicolas.roussel@inria.fr)
 *
 * Copyright 2019 Inria
 * 
 * BSD License https://opensource.org/licenses/BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this list of conditions
 * and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions
 * and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or
 * promote products derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */