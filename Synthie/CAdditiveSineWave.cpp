#include "StdAfx.h"
#include "CAdditiveSineWave.h"
#include <iostream>
#include <cmath>


short catchOverflow(double d)
{
	if (d < -32768)
		return -32768;
	else if (d > 32767)
		return 32767;

	return short(d);
}

CAdditiveSineWave::CAdditiveSineWave(void)
{
	m_vibratoFreq = 0.0;
	m_vibratoRate = 0.0;
	m_amplitude = 1000.0;
	for (int i = 1; i <= 7; i++) m_amp[i] = 1/i;
	m_freq = 440.0;
}


CAdditiveSineWave::~CAdditiveSineWave(void)
{
	delete[] audio;
	audio = NULL;
}

void CAdditiveSineWave::Start()
{
	audio = new short[int(m_duration * GetSampleRate())];
	index = 0;
	CAdditiveSineWave::GenerateWaveTable();
}

bool CAdditiveSineWave::Generate()
{
	m_frame[1] = audio[index];
	m_frame[0] = audio[index++];

	return index < int(m_duration * GetSampleRate());
}

void CAdditiveSineWave::GenerateWaveTable()
{
	double sinePhase = 0; 
	double vibratoPhase = 0; 
	double time = 0;

	for (int i = 0; i < int(m_duration * GetSampleRate()); i++, time += 1.0 / GetSampleRate())
	{
		double sample = 0.0;

		for (int n = 1; n <= 8 && n * m_freq <= 22050; n++)
		{
			sample += m_amplitude * m_amp[n - 1] * sin(n * sinePhase);
		}

		vibratoPhase += (2 * PI * m_vibratoRate) / GetSampleRate();
		double vibratoEffect = m_vibratoFreq * sin(vibratoPhase);
		sinePhase += (2 * PI * (m_freq + vibratoEffect)) / GetSampleRate();

		audio[i] = catchOverflow(sample);
	}
}