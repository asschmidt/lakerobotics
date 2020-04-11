#ifndef FastPID2_H
#define FastPID2_H

#include <stdint.h>

#define INTEG_MAX    (INT32_MAX)
#define INTEG_MIN    (INT32_MIN)
#define DERIV_MAX    (INT16_MAX)
#define DERIV_MIN    (INT16_MIN)

/*
  A fixed point PID controller with a 32-bit internal calculation pipeline.
*/
class FastPID2 {

public:
  FastPID2()
  {
    clear();
  }

  FastPID2(float kp, float ki, float kd, float hz, int bits=16, bool sign=false)
  {
    configure(kp, ki, kd, hz, bits, sign);
  }

  ~FastPID2();

  bool setCoefficients(float kp, float ki, float kd, float hz);
  bool setOutputConfig(int bits, bool sign);
  bool setOutputRange(int16_t min, int16_t max);
  void clear();
  bool configure(float kp, float ki, float kd, float hz, int bits=16, bool sign=false);
  int16_t step(int16_t sp, int16_t fb);

  bool err() {
    return _cfg_err;
  }

private:

  void setCfgErr(); 

private:

  // Configuration
  float _p, _i, _d;
  float _ta;
  int64_t _outmax, _outmin; 
  bool _cfg_err; 
  
  // State
  int16_t _last_sp, _last_out;
  float _sum;
  int32_t _last_err;
};

#endif
