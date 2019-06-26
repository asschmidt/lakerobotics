#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAN_USBTIN_LIB)
#  define CAN_USBTIN_EXPORT Q_DECL_EXPORT
# else
#  define CAN_USBTIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAN_USBTIN_EXPORT
#endif
