#include "myfatfs.h"
#include "includes.h"
#include "diskio.h"

FATFS fatfs; /* FATFS work area*/

/*
 mount SD Card from Fatfs
 true: mount ok
 false: mount failed
*/
bool mountSDCard(void)
{
  return (f_mount(&fatfs, "SD:", 1) == FR_OK);
}

bool f_file_exists(const TCHAR* path)
{
  FIL tmp;
  if (f_open(&tmp, path, FA_OPEN_EXISTING) == FR_OK)
  {
    f_close(&tmp);
    return true;
  }
  return false;
}