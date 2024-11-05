#pragma once
#include "Instrument.h"
#include "CAdditiveSineWave.h"

class CAdditiveSynth : public CInstrument
{
public:
	CAdditiveSynth(void);
	virtual ~CAdditiveSynth(void);

	virtual void Start();
	virtual bool Generate();
	
	void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double& a) { m_sinewave.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d; }
	void SetCrossFadeIn(double d) { m_attack = d; }
	void SetCrossFadeOut(double d) { m_release = d; }
	virtual void SetNote(CNote* note);

private:
	CAdditiveSineWave m_sinewave;
	double m_duration;
	double m_time;
	double m_release;
	double m_attack;
	double m_crossFadeIn;
	double m_crossFadeOut;
	double m_sustain;
	double m_decay;
};

