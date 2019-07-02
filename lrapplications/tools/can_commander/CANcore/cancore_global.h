#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CANCORE_LIB)
#  define CANCORE_EXPORT Q_DECL_EXPORT
# else
#  define CANCORE_EXPORT Q_DECL_IMPORT
# endif
#else
# define CANCORE_EXPORT
#endif
