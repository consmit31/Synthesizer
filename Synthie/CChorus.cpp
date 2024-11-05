#include "stdafx.h"
#include "CChorus.h"

CChorus::CChorus(void)
{
	m_delay = 0;
	m_dry = 0;
	m_wet = 0;
	m_modRange = 0;
	m_modRate = 0;
	m_wrloc = 0;
	m_sampleRate = 44100;

	int bufferSize = static_cast<int>(m_sampleRate * 2);
	m_leftQ.resize(bufferSize, 0.0);
	m_rightQ.resize(bufferSize, 0.0);
}

void CChorus::SetSampleRate(double s)
{
	m_sampleRate = s;

	int bufferSize = static_cast<int>(m_sampleRate * 2);
	m_leftQ.resize(bufferSize, 0.0);
	m_rightQ.resize(bufferSize, 0.0);
}

void CChorus::Process(double* frame1, double* frame2)
{
	double modValue = sin(2.0 * PI * m_modRate);
	double delayVariance = m_modRange * modValue;
	double newDelay = Clamp(m_delay + delayVariance, 0.0, 2.0);

	m_wrloc = (m_wrloc + 1) % m_leftQ.size();
	m_leftQ[m_wrloc] = frame1[0];
	m_rightQ[m_wrloc] = frame1[1];

	int delayLength = static_cast<int>(newDelay * m_sampleRate);
	int rdloc = (m_wrloc + m_leftQ.size() - delayLength) % m_leftQ.size();

	double wetLeft = (frame1[0] + m_leftQ[rdloc]) / 2.0;
	double wetRight = (frame1[1] + m_rightQ[rdloc]) / 2.0;

	frame2[0] = wetLeft * m_wet + frame1[0] * m_dry;
	frame2[1] = wetRight * m_wet + frame1[1] * m_dry;

	frame2[0] = Clamp(frame2[0], -1.0, 1.0);
	frame2[1] = Clamp(frame2[1], -1.0, 1.0);
}

void CChorus::XmlLoad(IXMLDOMNode* xml)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "delay")
		{
			value.ChangeType(VT_R8);
			m_delay = Clamp(value.dblVal, 0.0, 2.0);
		}
		else if (name == "wet")
		{
			value.ChangeType(VT_R8);
			m_wet = Clamp(value.dblVal, 0.0, 1.0);
		}
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			m_dry = Clamp(value.dblVal, 0.0, 1.0);
		}
		else if (name == "range")
		{
			value.ChangeType(VT_R8);
			m_modRange = value.dblVal;
		}
		else if (name == "rate")
		{
			value.ChangeType(VT_R8);
			m_modRate = value.dblVal;
		}
	}
}
