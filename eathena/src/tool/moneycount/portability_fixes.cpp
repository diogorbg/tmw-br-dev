////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2009
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "portability_fixes.hpp"

#ifdef MSWINDOWS
#include "windows.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// problems with missing functions
////////////////////////////////////////////////////////////////////////////////

#ifdef MSWINDOWS
unsigned sleep(unsigned seconds)
{
  Sleep(1000*seconds);
  // should return remaining time if interrupted - however Windoze Sleep cannot be interrupted
  return 0;
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Function for establishing endian-ness
////////////////////////////////////////////////////////////////////////////////

bool stlplus::little_endian(void)
{
  int sample = 1;
  char* sample_bytes = (char*)&sample;
  return sample_bytes[0] != 0;
}

////////////////////////////////////////////////////////////////////////////////
