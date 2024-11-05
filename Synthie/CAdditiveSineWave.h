#pragma once
#include "AudioNode.h"
class CAdditiveSineWave : public CAudioNode
{
public:
	CAdditiveSineWave(void);
	~CAdditiveSineWave(void);

	virtual void Start();
	virtual bool Generate();
	void GenerateWaveTable();

	void SetFreq(double freq) { m_freq = freq; }
	void SetAmplitude(double amp) { memcpy(&m_amp, &amp, sizeof(double) * 8); }
	void SetDuration(double d) { m_duration = d; }
	void SetVibratoRate(double rate) { m_vibratoRate = rate; }
	void SetVibratoFreq(double freq) { m_vibratoFreq = freq; }

private:
	double m_duration;
	double m_freq;
	double m_amp[8];
	double m_amplitude;

	int index;
	short* audio;
	double m_vibratoRate;
	double m_vibratoFreq;
};

