#include "stdafx.h"
#include "CFlange.h"

CFlange::CFlange(void)
{
	m_delay = 0;
	m_dry = 0;
	m_wet = 0;
	m_modRange = 0;
	m_modRate = 0;
	m_level = 1;
	m_wrloc = 0;
	m_sampleRate = 0;

	m_leftQ.resize(200000);
	m_rightQ.resize(200000);

	m_outL.resize(200000);
	m_outR.resize(200000);
}

void CFlange::Process(double* frameIn, double* frameOut)
{
	double modValue = sin(2 * PI * m_modRate);
	double delayVariance = m_modRange * modValue;
	double newDelay = m_delay + delayVariance;

	if (newDelay < 0) newDelay = 0;

	m_wrloc = (m_wrloc + 1) % m_leftQ.size();
	m_leftQ[m_wrloc] = frameIn[0];
	m_rightQ[m_wrloc] = frameIn[1];

	int delayLength = static_cast<int>((newDelay * m_sampleRate + 0.5));
	int rdloc = (m_wrloc + m_leftQ.size() - delayLength) % m_leftQ.size();

	double wetLeft = (frameIn[0] + m_leftQ[rdloc] + m_outL[rdloc] * m_level) / 3;
	double wetRight = (frameIn[1] + m_rightQ[rdloc] + m_outR[rdloc] * m_level) / 3;

	frameOut[0] = wetLeft * m_wet + frameIn[0] * m_dry;
	frameOut[1] = wetRight * m_wet + frameIn[1] * m_dry;

	m_outL[m_wrloc] = frameOut[0] * 0.99;
	m_outR[m_wrloc] = frameOut[1] * 0.99;
}

void CFlange::XmlLoad(IXMLDOMNode* xml)
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
			m_delay = value.dblVal;
		}
		else if (name == "wet")
		{
			value.ChangeType(VT_R8);
			m_wet = value.dblVal;
		}
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			m_dry = value.dblVal;
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
		else if (name == "level")
		{
			value.ChangeType(VT_R8);
			m_level = value.dblVal;
		}
	}
}