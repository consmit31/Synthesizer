#include "stdafx.h"
#include "CNoiseGate.h"

CNoiseGate::CNoiseGate()
{
	m_threshold = 0.01;
	m_dry = 1.0;
	m_wet = 0.0;
	m_leftGate = 1.0;
	m_rightGate = 1.0;
    m_attack = 0.01;
    m_release = 0.01;
}

void CNoiseGate::Process(double* frame1, double* frame2)
{
    // Left channel
    if (std::abs(frame1[0]) < m_threshold) {
        // Reduce gain if below threshold
        m_leftGate -= m_release;
        m_leftGate = Clamp(m_leftGate, 0.0, 1.0);
    }
    else {
        // Increase gain if above threshold
        m_leftGate += m_attack;
        m_leftGate = Clamp(m_leftGate, 0.0, 1.0);
    }
    frame2[0] = m_dry * frame1[0] + (m_wet * frame1[0] * m_leftGate);

    // Right channel
    if (std::abs(frame1[1]) < m_threshold) {
        // Reduce gain if below threshold
        m_rightGate -= m_release;
        m_rightGate = Clamp(m_rightGate, 0.0, 1.0);
    }
    else {
        // Increase gain if above threshold
        m_rightGate += m_attack;
        m_rightGate = Clamp(m_rightGate, 0.0, 1.0);
    }
    frame2[1] = m_dry * frame1[1] + (m_wet * frame1[1] * m_rightGate);

	/*if (frame1[0] < m_threshold && frame1[0] > -m_threshold)
	{
		m_leftGate -= 0.01;
		if (m_leftGate < 0)
			m_leftGate = 0;
	}
	else
	{
		m_leftGate += 0.01;
		if (m_leftGate > 1)
			m_leftGate = 1;
	}
	frame2[0] = m_dry * frame1[0] + (m_wet * frame1[0] * m_leftGate);

    if (frame1[1] < m_threshold && frame1[1] > -m_threshold)
    {
        m_rightGate -= 0.001;
        if (m_rightGate < 0)
            m_rightGate = 0;
    }
    else
    {
        m_rightGate += 0.001;
        if (m_rightGate > 1)
            m_rightGate = 1;
    }
    frame2[1] = m_dry * frame1[1] + (m_wet * frame1[1] * m_leftGate);*/

}

void CNoiseGate::XmlLoad(IXMLDOMNode* xml)
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

        if (name == "threshold")
        {
            value.ChangeType(VT_I4);
            m_threshold = value.intVal;
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
    }

}
