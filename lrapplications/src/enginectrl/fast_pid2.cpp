#include "fast_pid2.h"

//#include <Arduino.h>

FastPID2::~FastPID2() {
}

void FastPID2::clear() {
  _last_sp = 0; 
  _last_out = 0;
  _sum = 0.0;
  _last_err = 0;
}

bool FastPID2::setCoefficients(float kp, float ki, float kd, float hz) {
  _p = kp;
  _i = ki;
  _d = kd;
  _ta = 1 / hz;

  return ! _cfg_err;
}

bool FastPID2::setOutputRange(int16_t min, int16_t max)
{
  if (min >= max) {
    setCfgErr();
    return ! _cfg_err;
  }
  _outmin = min;
  _outmax = max;
  return ! _cfg_err;
}

bool FastPID2::configure(float kp, float ki, float kd, float hz, int bits, bool sign) {
  clear();
  _cfg_err = false;
  setCoefficients(kp, ki, kd, hz);
  return ! _cfg_err; 
}

int16_t FastPID2::step(int16_t sp, int16_t fb) {

  // int16 + int16 = int17
  int32_t err = int32_t(sp) - int32_t(fb);
  float P = 0, I = 0;
  float D = 0;

  if (_p) {
    // uint16 * int16 = int32
    P = _p * err;
  }

  if (_i) {
    // int17 * int16 = int33
    _sum += err;

    // Limit sum to 32-bit signed value so that it saturates, never overflows.
    if (_sum > INTEG_MAX)
      _sum = INTEG_MAX;
    else if (_sum < INTEG_MIN)
      _sum = INTEG_MIN;

    // int32
    I = _i * _sum;
  }

  if (_d) {
    // (int17 - int16) - (int16 - int16) = int19
    float deriv = (err - _last_err) - int32_t(sp - _last_sp);
    _last_sp = sp; 
    _last_err = err; 

    // Limit the derivative to 16-bit signed value.
    if (deriv > DERIV_MAX)
      deriv = DERIV_MAX;
    else if (deriv < DERIV_MIN)
      deriv = DERIV_MIN;

    // int16 * int16 = int32
    D = _d * deriv;
  }

  // int32 (P) + int32 (I) + int32 (D) = int34
  int32_t out = int32_t(P + I + D);

  // Make the output saturate
  if (out > _outmax) 
    out = _outmax;
  else if (out < _outmin) 
    out = _outmin;

  return out;
}

void FastPID2::setCfgErr() {
  _cfg_err = true;
  _p = _i = _d = 0.0;
}
