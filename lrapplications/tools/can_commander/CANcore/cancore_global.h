/*
 * cancore_global.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _CANCORE_GLOBAL_H_
#define _CANCORE_GLOBAL_H_

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

#endif
