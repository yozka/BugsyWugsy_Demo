//◦ EggEngine ◦
#pragma once
#include <memory>
#include <cfloat>
#include <cmath>

namespace Engine::Math
{
	template<typename T>
	bool IsZero(const T value)
	{
		return std::abs(value) < FLT_EPSILON;
	}


	template<typename T>
	bool IsEqual(const T a, const T b)
	{
		return std::abs(a - b) < FLT_EPSILON;
	}


	template<typename T>
	T Clamp(const T v, const T min, const T max)
	{
		return (v < min) ? min : (v > max) ? max : v;
	}


	/// Получение знака (-1/0/1) числа типа float
	template<typename T>
	int Sign(const T value)
	{
		if (value < 0.0f) {
			return -1;
		} else if (value > 0.0f) {
			return 1;
		} else {
			return 1;
		}
	}

	/**
	 * Easing equation function for a simple linear tweening, with no easing.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseLinear(float t);

	/**
	 * Easing equation function for a quadratic (t^2) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInQuad(float t);

	/**
	* Easing equation function for a quadratic (t^2) easing out: decelerating to zero velocity.
	*
	* @param t		Current time (in frames or seconds).
	* @return		The correct value.
	*/
	float EaseOutQuad(float t);

	/**
	 * Easing equation function for a quadratic (t^2) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutQuad(float t);

	/**
	 * Easing equation function for a quadratic (t^2) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInQuad(float t);

	/**
	 * Easing equation function for a cubic (t^3) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInCubic(float t);

	/**
	 * Easing equation function for a cubic (t^3) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutCubic(float t);

	/**
	 * Easing equation function for a cubic (t^3) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutCubic(float t);

	/**
	 * Easing equation function for a cubic (t^3) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInCubic(float t);

	/**
	 * Easing equation function for a quartic (t^4) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInQuart(float t);

	/**
	 * Easing equation function for a quartic (t^4) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutQuart(float t);

	/**
	 * Easing equation function for a quartic (t^4) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutQuart(float t);

	/**
	 * Easing equation function for a quartic (t^4) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInQuart(float t);

	/**
	 * Easing equation function for a quintic (t^5) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInQuint(float t);

	/**
	 * Easing equation function for a quintic (t^5) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutQuint(float t);

	/**
	 * Easing equation function for a quintic (t^5) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutQuint(float t);

	/**
	 * Easing equation function for a quintic (t^5) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInQuint(float t);

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInSine(float t);

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutSine(float t);

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutSine(float t);

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInSine(float t);

	/**
	 * Easing equation function for an exponential (2^t) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInExpo(float t);

	/**
	 * Easing equation function for an exponential (2^t) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutExpo(float t);

	/**
	 * Easing equation function for an exponential (2^t) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutExpo(float t);

	/**
	 * Easing equation function for an exponential (2^t) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInExpo(float t);

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInCirc(float t);

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutCirc(float t);

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutCirc(float t);

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInCirc(float t);

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseInElastic(float t, float a, float p);

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseOutElastic(float t, float a, float p);

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseInOutElastic(float t, float a, float p);

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseOutInElastic(float t, float a, float p);

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseInBack(float t, float s);

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseOutBack(float t, float s);

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseInOutBack(float t, float s);

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseOutInBack(float t, float s);

	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseOutBounce(float t, float a);

	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseInBounce(float t, float a);

	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseInOutBounce(float t, float a);

	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseOutInBounce(float t, float a);

	/**
	 * Easing function that starts growing slowly, then incrEases in speed. At the end of the curve the speed will be constant.
	 */
	float EaseInCurve(float t);

	/**
	 * Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
	 */
	float EaseOutCurve(float t);

	/**
	 * Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
	 */
	float EaseSineCurve(float t);

	/**
	 * Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
	 * contrary to the usual 0 to 1 easing curve.
	 */
	float EaseCosineCurve(float t);
}


