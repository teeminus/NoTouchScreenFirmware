/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "variants.h"

#ifdef SD_SPI_SUPPORT
  #include "sd.h"
#else
  #include "sdio_sdcard.h"
#endif

static volatile DSTATUS diskStatus = STA_NOINIT;	/* Disk status */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status ()
{
  return diskStatus;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize ()
{
  diskStatus = STA_NOINIT;
  if (SD_Init() == 0)
  {
    diskStatus &= ~STA_NOINIT;
  }
	return diskStatus;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
  if (!count) return RES_PARERR;
  if (diskStatus & STA_NOINIT) return RES_NOTRDY;

	while (SD_ReadDisk(buff,sector,count)) // read error
  {
    SD_Init();	//init again
  }
  return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
  if (!count) return RES_PARERR;
  if (diskStatus & STA_NOINIT) return RES_NOTRDY;
  if (diskStatus & STA_PROTECT) return RES_WRPRT;

	while (SD_WriteDisk((u8*)buff,sector,count)) // write error
  {
    SD_Init();	// init again
  }
  return RES_OK;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
  return RES_OK;
}
