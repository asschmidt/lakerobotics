#include "AutoPID.h"

/**
 *
 * @param input
 * @param setpoint
 * @param output
 * @param outputMin
 * @param outputMax
 * @param Kp
 * @param Ki
 * @param Kd
 */
AutoPID::AutoPID(double *input, double *setpoint, double *output, double outputMin, double outputMax,
                 double Kp, double Ki, double Kd)
{
  _input = input;
  _setpoint = setpoint;
  _output = output;

  _outputMin = outputMin;
  _outputMax = outputMax;

  setGains(Kp, Ki, Kd);
  _timeStep = 1000;
}

/**
 *
 * @param Kp
 * @param Ki
 * @param Kd
 */
void AutoPID::setGains(double Kp, double Ki, double Kd)
{
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}

/**
 *
 * @param bangOn
 * @param bangOff
 */
void AutoPID::setBangBang(double bangOn, double bangOff)
{
  _bangOn = bangOn;
  _bangOff = bangOff;
}

/**
 *
 * @param bangRange
 */
void AutoPID::setBangBang(double bangRange)
{
  setBangBang(bangRange, bangRange);
}

/**
 *
 * @param outputMin
 * @param outputMax
 */
void AutoPID::setOutputRange(double outputMin, double outputMax)
{
  _outputMin = outputMin;
  _outputMax = outputMax;
}

/**
 *
 * @param timeStep
 */
void AutoPID::setTimeStep(unsigned long timeStep)
{
  _timeStep = timeStep;
}

/**
 *
 * @param threshold
 * @return
 */
bool AutoPID::atSetPoint(double threshold)
{
  return abs(*_setpoint - *_input) <= threshold;
}

/**
 *
 */
void AutoPID::run()
{
  if (_stopped)
  {
    _stopped = false;
    reset();
  }

  //if bang thresholds are defined and we're outside of them, use bang-bang control
  if (_bangOn && ((*_setpoint - *_input) > _bangOn))
  {
    *_output = _outputMax;
    _lastStep = millis();
  }
  else if (_bangOff && ((*_input - *_setpoint) > _bangOff))
  {
    *_output = _outputMin;
    _lastStep = millis();
  }
  else
  {
	//otherwise use PID control
    unsigned long _dT = millis() - _lastStep;   //calculate time since last update

    //if long enough, do PID calculations
    if (_dT >= _timeStep)
    {
      _lastStep = millis();

      double _error = *_setpoint - *_input;
      // Riemann sum integral
      _integral += (_error + _previousError) / 2 * _dT / 1000.0;
      //_integral = constrain(_integral, _outputMin/_Ki, _outputMax/_Ki);

      // Derivative
      double _dError = (_error - _previousError) / _dT / 1000.0;
      _previousError = _error;

      double PID = (_Kp * _error) + (_Ki * _integral) + (_Kd * _dError);

      //*_output = _outputMin + (constrain(PID, 0, 1) * (_outputMax - _outputMin));
      *_output = constrain(PID, _outputMin, _outputMax);
    }
  }
}

/**
 *
 */
void AutoPID::stop()
{
  _stopped = true;
  reset();
}

/**
 *
 */
void AutoPID::reset()
{
  _lastStep = millis();
  _integral = 0;
  _previousError = 0;
}

/**
 *
 * @return
 */
bool AutoPID::isStopped()
{
  return _stopped;
}

/**
 *
 */
void AutoPIDRelay::run()
{
  AutoPID::run();

  while ((millis() - _lastPulseTime) > _pulseWidth)
	  _lastPulseTime += _pulseWidth;

  *_relayState = ((millis() - _lastPulseTime) < (_pulseValue * _pulseWidth));
}

/**
 *
 * @return
 */
double AutoPIDRelay::getPulseValue()
{
  return (isStopped()?0:_pulseValue);
}
