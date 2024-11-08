#include "stdafx.h"
#include "AdditiveSynth.h"
#include "Notes.h"
#include <string>
#include <sstream>
#include <vector>

CAdditiveSynth::CAdditiveSynth(void)
{
	m_crossFadeIn = 0.0;
	m_crossFadeOut = 0.0;
	m_attack = m_release = m_decay = 0;
	m_sustain = 1.0;
}


CAdditiveSynth::~CAdditiveSynth(void)
{
}

void CAdditiveSynth::Start()
{
	m_sinewave.SetSampleRate(GetSampleRate());
	m_sinewave.SetDuration(m_duration);
	m_sinewave.Start();
	m_time = 0;
}


bool CAdditiveSynth::Generate()
{
	m_sinewave.Generate();

	double fadeFactor = 1.0;
	if (m_time < m_crossFadeIn) 
	{
		fadeFactor = m_time / m_crossFadeIn;
	}
	else if (m_time > (m_duration - m_crossFadeOut)) 
	{
		fadeFactor = (m_duration - m_time) / m_crossFadeOut;
	}

	double factor = 1.0;

	if (m_time < m_attack)
	{
		factor = m_time / m_attack;
	}
	else if (m_time < m_decay)
	{
		double decayFactor = 1.0 - ((m_time - m_attack) / (m_decay - m_attack)) * (1.0 - m_sustain);
		factor = fadeFactor * decayFactor;
	}
	else if (m_time > (m_duration - m_release) && m_release != 0)
	{
		factor = fadeFactor * (1.0 - ((m_time - (m_duration - m_release)) / m_release) * (1.0 - m_sustain));
	}
	else
	{
		factor = fadeFactor * m_sustain;
	}

	m_frame[0] = m_sinewave.Frame(0) * factor;
	m_frame[1] = m_sinewave.Frame(1) * factor;

	//// Update time
	m_time += GetSamplePeriod();

	//// We return true until the time reaches the duration.
	return m_time < m_duration;
}

void CAdditiveSynth::SetNote(CNote* note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "amplitudes")
		{
			std::wstring wide(value.bstrVal);
			std::string str(wide.begin(), wide.end());

			std::stringstream ss(str);
			std::string item;

			double harmonics[8] = { 0 };

			int i = 0;
			while (std::getline(ss, item, char(32))) {
				harmonics[i++] = atof(item.c_str());
			}

			SetAmplitude(harmonics[0]);
		}
		else if (name == "crossFadeIn")
		{
			value.ChangeType(VT_R8);
			SetCrossFadeIn(value.dblVal * m_duration);
		}
		else if (name == "crossFadeOut")
		{
			value.ChangeType(VT_R8);
			SetCrossFadeOut(value.dblVal * m_duration);
		}
		else if (name == "ADSR") {
			std::wstring wide(value.bstrVal);
			std::string str(wide.begin(), wide.end());

			std::stringstream ss(str);
			std::string item;

			std::getline(ss, item, char(32));
			m_attack = atof(item.c_str()) * m_duration;

			std::getline(ss, item, char(32));
			m_decay = m_attack + atof(item.c_str()) * m_duration;

			std::getline(ss, item, char(32));
			m_sustain = atof(item.c_str());

			std::getline(ss, item, char(32));
			m_release = atof(item.c_str()) * m_duration;
		}
		else if (name == "vibrato") {
			std::wstring wide(value.bstrVal);
			std::string str(wide.begin(), wide.end());

			std::stringstream ss(str);
			std::string item;

			std::getline(ss, item, char(32));
			m_sinewave.SetVibratoRate(atof(item.c_str()));

			std::getline(ss, item, char(32));
			m_sinewave.SetVibratoFreq(atof(item.c_str()));
		}

	}

}