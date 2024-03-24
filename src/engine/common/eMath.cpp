//◦ EggEngine ◦
#include "eMath.h"
namespace Engine::Math
{
	constexpr float PI 	= 3.14159265359f;
	constexpr float PI_05 = 1.5707963267948966f;

	/**
	 * Easing equation function for a simple linear tweening, with no easing.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseLinear(float t)
	{
		return t;
	}

	/**
	 * Easing equation function for a quadratic (t^2) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInQuad(float t)
	{
		return t * t;
	}

	/**
	* Easing equation function for a quadratic (t^2) easing out: decelerating to zero velocity.
	*
	* @param t		Current time (in frames or seconds).
	* @return		The correct value.
	*/
	float EaseOutQuad(float t)
	{
		return -t * (t - 2.0f);
	}

	/**
	 * Easing equation function for a quadratic (t^2) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutQuad(float t)
	{
		t *= 2.0f;
		if (t < 1.0f)
		{
			return t * t / 2.0f;
		}
		else
		{
			t -= 1.0f;
			return -0.5f * (t * (t - 2.0f) - 1.0f);
		}
	}

	/**
	 * Easing equation function for a quadratic (t^2) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInQuad(float t)
	{
		if (t < 0.5f) return EaseOutQuad(t * 2.0f) / 2.0f;
		return EaseInQuad((2.0f * t) - 1.0f) / 2.0f + 0.5f;
	}

	/**
	 * Easing equation function for a cubic (t^3) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInCubic(float t)
	{
		return t * t * t;
	}

	/**
	 * Easing equation function for a cubic (t^3) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutCubic(float t)
	{
		t -= 1.0f;
		return t * t * t + 1.0f;
	}

	/**
	 * Easing equation function for a cubic (t^3) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutCubic(float t)
	{
		t *= 2.0f;
		if(t < 1)
		{
			return 0.5f * t * t * t;
		}
		else
		{
			t -= 2.0f;
			return 0.5f * (t * t * t + 2.0f);
		}
	}

	/**
	 * Easing equation function for a cubic (t^3) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInCubic(float t)
	{
		if (t < 0.5f) return EaseOutCubic(2.0f * t) / 2.0f;
		return EaseInCubic(2.0f * t - 1.0f) / 2.0f + 0.5f;
	}

	/**
	 * Easing equation function for a quartic (t^4) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInQuart(float t)
	{
		return t * t * t * t;
	}

	/**
	 * Easing equation function for a quartic (t^4) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutQuart(float t)
	{
		t-= 1.0f;
		return -(t * t * t * t - 1.0f);
	}

	/**
	 * Easing equation function for a quartic (t^4) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutQuart(float t)
	{
		t *= 2.0f;
		if (t < 1.0f)
		{
			return 0.5f * t * t * t * t;
		}
		else
		{
			t -= 2.0f;
			return -0.5f * (t * t * t * t - 2.0f);
		}
	}

	/**
	 * Easing equation function for a quartic (t^4) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInQuart(float t)
	{
		if (t < 0.5f) return EaseOutQuart(2.0f * t ) / 2.0f;
		return EaseInQuart(2.0f * t - 1.0f) / 2.0f + 0.5f;
	}

	/**
	 * Easing equation function for a quintic (t^5) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInQuint(float t)
	{
		return t * t * t * t * t;
	}

	/**
	 * Easing equation function for a quintic (t^5) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutQuint(float t)
	{
		t -= 1.0f;
		return t * t * t * t * t + 1.0f;
	}

	/**
	 * Easing equation function for a quintic (t^5) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutQuint(float t)
	{
		t *= 2.0f;
		if (t < 1.0f)
		{
			return 0.5f * t * t * t * t * t;
		}
		else
		{
			t -= 2.0f;
			return 0.5f * (t * t * t * t * t + 2.0f);
		}
	}

	/**
	 * Easing equation function for a quintic (t^5) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInQuint(float t)
	{
		if (t < 0.5f) return EaseOutQuint(2.0f * t) / 2.0f;
		return EaseInQuint(2.0f * t - 1.0f) / 2.0f + 0.5f;
	}

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInSine(float t)
	{
		return (t == 1.0f) ? 1.0f : -std::cos(t * PI_05) + 1.0f;
	}

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutSine(float t)
	{
		return std::sin(t * PI_05);
	}

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutSine(float t)
	{
		return -0.5f * (std::cos(Math::PI * t) - 1.0f);
	}

	/**
	 * Easing equation function for a sinusoidal (sin(t)) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInSine(float t)
	{
		if (t < 0.5f) return EaseOutSine(2.0f * t) / 2.0f;
		return EaseInSine(2.0f * t - 1.0f) / 2.0f + 0.5f;
	}

	/**
	 * Easing equation function for an exponential (2^t) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInExpo(float t)
	{
		return (t == 0.0f || t == 1.0f) ? t : std::pow(2.0f, 10.0f * (t - 1.0f)) - 0.001f;
	}

	/**
	 * Easing equation function for an exponential (2^t) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutExpo(float t)
	{
		return (t == 1.0f) ? 1.0f : 1.001f * (-std::pow(2.0f, -10.0f * t) + 1.0f);
	}

	/**
	 * Easing equation function for an exponential (2^t) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutExpo(float t)
	{
		if (t == 0.0f) return 0.0f;
		if (t == 1.0f) return 1.0f;
		t *= 2.0f;
		if (t < 1.0f) return 0.5f * std::pow(2.0f, 10.0f * (t - 1.0f)) - 0.0005f;
		return 0.5f * 1.0005f * (-std::pow(2.0f, -10.0f * (t - 1.0f)) + 2.0f);
	}

	/**
	 * Easing equation function for an exponential (2^t) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInExpo(float t)
	{
		if (t < 0.5f) return EaseOutExpo(2.0f * t) / 2.0f;
		return EaseInExpo(2.0f * t - 1.0f) / 2.0f + 0.5f;
	}

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInCirc(float t)
	{
		return -(std::sqrt(1.0f - t * t) - 1.0f);
	}

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutCirc(float t)
	{
		t -= 1.0f;
		return std::sqrt(1.0f - t * t);
	}

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseInOutCirc(float t)
	{
		t *= 2.0f;
		if (t < 1.0f) {
			return -0.5f * (std::sqrt(1.0f - t * t) - 1.0f);
		} else {
			t -= 2.0f;
			return 0.5f * (std::sqrt(1.0f - t * t) + 1.0f);
		}
	}

	/**
	 * Easing equation function for a circular (sqrt(1-t^2)) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @return		The correct value.
	 */
	float EaseOutInCirc(float t)
	{
		if (t < 0.5f) return EaseOutCirc(2.0f * t) / 2.0f;
		return EaseInCirc(2.0f * t - 1.0f) / 2.0f + 0.5f;
	}

	float EaseInElastic_helper(float t, float b, float c, float d, float a, float p)
	{
		if (t == 0.0f) return b;
		float t_adj = t / d;
		if (t_adj == 1.0f) return b + c;

		float s;
		if(a < fabsf(c)) {
			a = c;
			s = p / 4.0f;
		} else {
			s = p / (2 * Math::PI) * std::asin(c / a);
		}

		t_adj -= 1.0f;
		return -(a * std::pow(2.0f, 10.0f * t_adj) * std::sin((t_adj * d - s) * (2.0f * Math::PI) / p)) + b;
	}

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseInElastic(float t, float a, float p)
	{
		return EaseInElastic_helper(t, 0, 1.0f, 1.0f, a, p);
	}

	float EaseOutElastic_helper(float t, float /* b */, float c, float /* d */, float a, float p)
	{
		if (t == 0.0f) return 0.0f;
		if (t == 1.0f) return c;

		float s;
		if(a < c) {
			a = c;
			s = p / 4.0f;
		} else {
			s = p / (2.0f * Math::PI) * std::asin(c / a);
		}

		return (a * std::pow(2.0f, -10.0f * t) * std::sin((t - s) * (2.0f * Math::PI) / p) + c);
	}

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseOutElastic(float t, float a, float p)
	{
		return EaseOutElastic_helper(t, 0.0f, 1.0f, 1.0f, a, p);
	}

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseInOutElastic(float t, float a, float p)
	{
		if (t == 0.0f) return 0.0f;
		t *= 2.0f;
		if (t == 2.0f) return 1.0f;

		float s;
		if(a < 1.0f) {
			a = 1.0f;
			s = p / 4.0f;
		} else {
			s = p / (2.0f * Math::PI) * std::asin(1.0f / a);
		}

		if (t < 1.0f) return -0.5f * (a * std::pow(2.0f, 10.0f * (t - 1.0f)) * std::sin((t - 1.0f - s) * (2.0f * Math::PI) / p));
		return a * std::pow(2.0f, -10.0f * (t - 1)) * std::sin((t - 1.0f - s) * (2.0f * Math::PI) / p) * 0.5f + 1.0f;
	}

	/**
	 * Easing equation function for an elastic (exponentially decaying sine wave) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @param p		Period.
	 * @return		The correct value.
	 */
	float EaseOutInElastic(float t, float a, float p)
	{
		if (t < 0.5f) return EaseOutElastic_helper(t * 2.0f, 0.0f, 0.5f, 1.0f, a, p);
		return EaseInElastic_helper(2.0f * t - 1.0f, 0.5f, 0.5f, 1.0f, a, p);
	}

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseInBack(float t, float s)
	{
		return t * t * ((s + 1.0f) * t - s);
	}

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseOutBack(float t, float s)
	{
		t -= 1.0f;
		return t * t * ((s + 1) * t + s) + 1.0f;
	}

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseInOutBack(float t, float s)
	{
		t *= 2.0f;
		if (t < 1.0f) {
			s *= 1.525f;
			return 0.5f * (t * t * ((s + 1.0f) * t - s));
		} else {
			t -= 2.0f;
			s *= 1.525f;
			return 0.5f * (t * t * ((s + 1.0f) * t + s) + 2.0f);
		}
	}

	/**
	 * Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
	 * @return		The correct value.
	 */
	float EaseOutInBack(float t, float s)
	{
		if (t < 0.5f) return EaseOutBack(2.0f * t, s) / 2.0f;
		return EaseInBack(2.0f * t - 1.0f, s) / 2.0f + 0.5f;
	}

	float EaseOutBounce_helper(float t, float c, float a)
	{
		if (t == 1.0f) return c;
		if (t < (4.0f / 11.0f)) {
			return c * (7.5625f * t * t);
		} else if (t < (8.0f / 11.0f)) {
			t -= (6.0f / 11.0f);
			return -a * (1.0f - (7.5625f * t * t + 0.75f)) + c;
		} else if (t < (10.0f / 11.0f)) {
			t -= (9.0f / 11.0f);
			return -a * (1.0f - (7.5625f * t * t + 0.9375f)) + c;
		} else {
			t -= (21.0f / 22.0f);
			return -a * (1.0f - (7.5625f * t * t + 0.984375f)) + c;
		}
	}

	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out: decelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseOutBounce(float t, float a)
	{
		return EaseOutBounce_helper(t, 1.0f, a);
	}

	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in: accelerating from zero velocity.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseInBounce(float t, float a)
	{
		return 1.0f - EaseOutBounce_helper(1.0f - t, 1.0f, a);
	}


	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in/out: acceleration until halfway, then deceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseInOutBounce(float t, float a)
	{
		if (t < 0.5f) return EaseInBounce(2.0f * t, a) / 2.0f;
		else return (t == 1.0f) ? 1.0f : EaseOutBounce(2.0f * t - 1.0f, a) / 2.0f + 0.5f;
	}

	/**
	 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out/in: deceleration until halfway, then acceleration.
	 *
	 * @param t		Current time (in frames or seconds).
	 * @param a		Amplitude.
	 * @return		The correct value.
	 */
	float EaseOutInBounce(float t, float a)
	{
		if (t < 0.5f) return EaseOutBounce_helper(t * 2.0f, 0.5f, a);
		return 1.0f - EaseOutBounce_helper(2.0f - 2.0f * t, 0.5f, a);
	}

	float sinProgress(float value)
	{
		return std::sin((value * Math::PI) - PI_05) / 2.0f + 0.5f;
	}

	// SmoothBegin blends Smooth and Linear Interpolation.
	// Progress 0 - 0.3      : Smooth only
	// Progress 0.3 - ~ 0.5  : Mix of Smooth and Linear
	// Progress ~ 0.5  - 1   : Linear only
	float smoothBeginEndMixFactor(float value)
	{
		return Math::Clamp(1.0f - value * 2.0f + 0.3f, 0.0f, 1.0f);
	}

	/**
	 * Easing function that starts growing slowly, then incrEases in speed. At the end of the curve the speed will be constant.
	 */
	float EaseInCurve(float t)
	{
		const float sinProgress = Math::sinProgress(t);
		const float mix = smoothBeginEndMixFactor(t);
		return sinProgress * mix + t * (1.0f - mix);
	}

	/**
	 * Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
	 */
	float EaseOutCurve(float t)
	{
		const float sinProgress = Math::sinProgress(t);
		const float mix = smoothBeginEndMixFactor(1.0f - t);
		return sinProgress * mix + t * (1.0f - mix);
	}

	/**
	 * Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
	 */
	float EaseSineCurve(float t)
	{
		return (std::sin(((t * Math::PI * 2.0f)) - PI_05) + 1.0f) / 2.0f;
	}

	/**
	 * Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
	 * contrary to the usual 0 to 1 easing curve.
	 */
	float EaseCosineCurve(float t)
	{
		return (std::cos(((t * Math::PI * 2.0f)) - PI_05) + 1.0f) / 2.0f;
	}

}
