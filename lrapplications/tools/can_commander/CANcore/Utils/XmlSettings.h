/*
 * XmlSettings.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _XMLSETTINGS_H_
#define _XMLSETTINGS_H_

// Qt includes
#include <QtCore/QSettings>

// Project includes
#include "cancore_global.h"

CANCORE_EXPORT QSettings::Format registerXmlSettingsFormat();

#endif
