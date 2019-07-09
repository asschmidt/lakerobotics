/*
 * XmlSettings.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QSettings>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

// Project includes
#include "Utils.h"
#include "XmlSettings.h"

// Static function declarations
static bool readXmlFile(QIODevice& device, QSettings::SettingsMap& map);
static bool writeXmlFile(QIODevice& device, const QSettings::SettingsMap& map);

/**
 *
 */
bool readXmlFile(QIODevice& device, QSettings::SettingsMap& map)
{
	QXmlStreamReader xmlReader(&device);

	QString currentElementName;
	while (!xmlReader.atEnd())
	{
		xmlReader.readNext();
		while (xmlReader.isStartElement())
		{
			if (xmlReader.name() == "SettingsMap")
			{
				xmlReader.readNext();
				continue;
			}

			if (!currentElementName.isEmpty())
			{
				currentElementName += "/";
			}
			currentElementName += xmlReader.name().toString();
			xmlReader.readNext();
		}

		if (xmlReader.isEndElement())
		{
			continue;
		}

		if (xmlReader.isCharacters() && !xmlReader.isWhitespace())
		{
			QString key = currentElementName;
			QString value = xmlReader.text().toString();

			map[key] = value;

			currentElementName.clear();
		}
	}

	if (xmlReader.hasError())
	{
		return false;
	}

	return true;
}

/**
 *
 */
bool writeXmlFile(QIODevice& device, const QSettings::SettingsMap& map)
{
	QXmlStreamWriter xmlWriter(&device);
	xmlWriter.setAutoFormatting(true);

	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement("SettingsMap");

	QSettings::SettingsMap::const_iterator mi = map.begin();
	for (mi; mi != map.end(); ++mi)
	{
		std::vector< std::string > groups;

		//StringUtils::SplitList(mi.key().toStdString().c_str(), "/", &groups);
		groups = split(mi.key().toStdString(), '/');

		foreach(std::string groupName, groups)
		{
			xmlWriter.writeStartElement(groupName.c_str());
		}

		xmlWriter.writeCharacters(mi.value().toString());

		foreach(std::string groupName, groups)
		{
			xmlWriter.writeEndElement();
		}
	}

	xmlWriter.writeEndElement();
	xmlWriter.writeEndDocument();

	return true;
}

/**
 *
 */
CANCORE_EXPORT QSettings::Format registerXmlSettingsFormat()
{
	QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);

	return XmlFormat;
}
