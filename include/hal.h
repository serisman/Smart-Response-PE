// Name: hal.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-10-03
// License: MIT

#ifndef __hal_h_included__
#define __hal_h_included__

#if defined(CC2430)
  #include "cc243x/cc243x.h"
#elif defined(CC2531)
  #include "cc253x/cc253x.h"
#elif defined(CC2533)
  #include "cc253x/cc253x.h"
#endif

#endif /* __hal_h_included__ */
