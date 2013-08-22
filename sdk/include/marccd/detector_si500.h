#ifndef si500_h
#define si500_h

/*
 * (C) Copyright 1996, Michael Blum 
 */

#include "detector.h"
#include "ccd_chips.h"

/* Driver file - needed for ioctl definitions and others... */
#include "drivers/si/si500.h"

/* These should evenually be dynamically changeable depending on which chip is in use */
#ifdef CCD_CHIP_SERIAL_PREPIXELS
#undef CCD_CHIP_SERIAL_PREPIXELS
#undef CCD_CHIP_SERIAL_IMAGEPIXELS
#undef CCD_CHIP_SERIAL_POSTPIXELS
#undef CCD_CHIP_SERIAL_TOTALPIXELS
#undef CCD_CHIP_PARALLEL_PREPIXELS
#undef CCD_CHIP_PARALLEL_IMAGEPIXELS
#undef CCD_CHIP_PARALLEL_POSTPIXELS
#undef CCD_CHIP_PARALLEL_TOTALPIXELS
#endif
#define CCD_CHIP_SERIAL_PREPIXELS	SI424A_CCD_CHIP_SERIAL_PREPIXELS	
#define CCD_CHIP_SERIAL_IMAGEPIXELS	SI424A_CCD_CHIP_SERIAL_IMAGEPIXELS	
#define CCD_CHIP_SERIAL_POSTPIXELS	SI424A_CCD_CHIP_SERIAL_POSTPIXELS	
#define CCD_CHIP_SERIAL_TOTALPIXELS	SI424A_CCD_CHIP_SERIAL_TOTALPIXELS	
#define CCD_CHIP_PARALLEL_PREPIXELS	SI424A_CCD_CHIP_PARALLEL_PREPIXELS	
#define CCD_CHIP_PARALLEL_IMAGEPIXELS	SI424A_CCD_CHIP_PARALLEL_IMAGEPIXELS	
#define CCD_CHIP_PARALLEL_POSTPIXELS	SI424A_CCD_CHIP_PARALLEL_POSTPIXELS	
#define CCD_CHIP_PARALLEL_TOTALPIXELS	SI424A_CCD_CHIP_PARALLEL_TOTALPIXELS	

#define DETECTOR_SI500_NFAST		CCD_CHIP_SERIAL_IMAGEPIXELS
#define DETECTOR_SI500_NSLOW		CCD_CHIP_PARALLEL_IMAGEPIXELS
#define DETECTOR_SI500_IMAGESIZE 	(DETECTOR_SI500_NFAST * DETECTOR_SI500_NFAST)

/* This will depend on how many readouts there are and/or how many are in use */
#define DETECTOR_SI500_NFASTDETECTORS 	1
#define DETECTOR_SI500_NSLOWDETECTORS 	1
#define DETECTOR_SI500_NDETECTORS 	(DETECTOR_SI500_NSLOWDETECTORS*DETECTOR_SI500_NFASTDETECTORS)


/* PDEBUG(G) Macros suggested by A. Rubini in Linux Journal #23 (1996) pg 10-17 */
/*
#ifndef PDEBUG
#   ifdef DEBUG_si500
#      ifdef __KERNEL__
#         define PDEBUG(fmt, args) printk(KERN_WARNING fmt, ## args)
#      else
#         define PDEBUG(fmt, args) fprintf(stderr, fmt, ## args)
#      endif
#   else
#      define PDEBUG(fmt, args)
#   endif
#endif
#ifndef PDEBUGG
#  define PDEBUGG(fmt, args)
#endif
*/


/* AMCC S5933 PCI Controller Chip Operation Register Offsets */
#define AMCC_OP_REG_OMB1	0x00
#define AMCC_OP_REG_OMB2	0x04
#define AMCC_OP_REG_OMB3	0x08
#define AMCC_OP_REG_OMB4	0x0c
#define AMCC_OP_REG_IMB1	0x10 /* (0x11 in manual ?) */
#define AMCC_OP_REG_IMB2	0x14
#define AMCC_OP_REG_IMB3	0x18
#define AMCC_OP_REG_IMB4	0x1c
#define AMCC_OP_REG_FIFO	0x20
#define AMCC_OP_REG_MWAR	0x24
#define AMCC_OP_REG_MWTC	0x28
#define AMCC_OP_REG_MRAR	0x2c
#define AMCC_OP_REG_MRTC	0x30
#define AMCC_OP_REG_MBEF	0x34
#define AMCC_OP_REG_INTCSR	0x38
#define AMCC_OP_REG_MCSR	0x3c
#define AMCC_OP_REG_MCSR_NVDATA	(AMCC_OP_REG_MCSR + 2) /* Data in byte 2 */
#define AMCC_OP_REG_MCSR_NVCMD	(AMCC_OP_REG_MCSR + 3) /* Command in byte 3 */

/* AMCC S5933 PCI Controller Chip Operation Register Bit definitions */
/* 0-1 Outgoing Mailbox Byte Interrupt Select */
/* 2-3 Outgoing Mailbox Interrupt Select */
#define AMCC_INTCSR_OUTGOING_MAILBOX_INTERRUPT_ENABLE		(1 << 4)	
/* 5-7 Reserved, Always zero */
/* 8-9 Incoming Mailbox Byte Interrupt Select */
/* 10-11 Incoming Mailbox Interrupt Select */
#define AMCC_INTCSR_INCOMING_MAILBOX_INTERRUPT_ENABLE		(1 << 12)	
/* 13 Reserved, Always zero */
#define AMCC_INTCSR_INTERRUPT_ON_WRITE_TRANSFER_COMPLETE	(1 << 14)	
#define AMCC_INTCSR_INTERRUPT_ON_READ_TRANSFER_COMPLETE		(1 << 15)	
#define AMCC_INTCSR_OUTGOING_MAILBOX_INTERRUPT			(1 << 16)	
#define AMCC_INTCSR_INCOMING_MAILBOX_INTERRUPT			(1 << 17)	
#define AMCC_INTCSR_WRITE_TRANSFER_COMPLETE			(1 << 18)	
#define AMCC_INTCSR_READ_TRANSFER_COMPLETE			(1 << 19)	
#define AMCC_INTCSR_MASTER_ABORT				(1 << 20)	
#define AMCC_INTCSR_TARGET_ABORT				(1 << 21)	
/* 22 Reserved, Always zero */
#define AMCC_INTCSR_INTERRUPT_ASSERTED				(1 << 23)	
/* 24-31 FIFO and Endian Control */
#define AMCC_INTCSR_ENDIAN_CONVERSION_0				(1 << 24)	
#define AMCC_INTCSR_ENDIAN_CONVERSION_1				(1 << 25)	
#define AMCC_INTCSR_FIFO_ADVANCE_PCI_0				(1 << 26)	
#define AMCC_INTCSR_FIFO_ADVANCE_PCI_1				(1 << 27)	
#define AMCC_INTCSR_FIFO_ADVANCE_ADDON_0			(1 << 28)	
#define AMCC_INTCSR_FIFO_ADVANCE_ADDON_1			(1 << 29)	
#define AMCC_INTSCR_OUTBOUND_FIFO_DWORD_TOGGLE			(1 << 30)	
#define AMCC_INTSCR_INBOUND_FIFO_DWORD_TOGGLE			(1 << 31)	

#define AMCC_MCSR_OUTBOUND_FIFO_FULL				(1 << 0)	
#define AMCC_MCSR_OUTBOUND_FIFO_4PLUS_WORDS			(1 << 1)	
#define AMCC_MCSR_OUTBOUND_FIFO_EMPTY				(1 << 2)	
#define AMCC_MCSR_INBOUND_FIFO_FULL				(1 << 3)	
#define AMCC_MCSR_INBOUND_FIFO_4PLUS_WORDS			(1 << 4)	
#define AMCC_MCSR_INBOUND_FIFO_EMPTY				(1 << 5)	
#define AMCC_MCSR_OUTBOUND_COUNT_ZERO				(1 << 6)	
#define AMCC_MCSR_INBOUND_COUNT_ZERO				(1 << 7)	
#define AMCC_MCSR_WRITE_VS_READ_PRIORITY			(1 << 8)	
#define AMCC_MCSR_WRITE_FIFO_MANAGEMENT_SCHEME			(1 << 9)	
#define AMCC_MCSR_WRITE_TRANSFER_ENABLE				(1 << 10)	
/* 11 Reserved, Always zero */
#define AMCC_MCSR_READ_VS_WRITE_PRIORITY			(1 << 12)	
#define AMCC_MCSR_READ_FIFO_MANAGEMENT_SCHEME			(1 << 13)	
#define AMCC_MCSR_READ_TRANSFER_ENABLE				(1 << 14)	
/* 15 Reserved, Always zero */
/* 16-23 Non-volatile memory address/data port */
#define AMCC_MCSR_ADDON_RESET					(1 << 24)	
#define AMCC_MCSR_OUTBOUND_FIFO_RESET				(1 << 25)	
#define AMCC_MCSR_INBOUND_FIFO_RESET				(1 << 26)	
#define AMCC_MCSR_MAILBOX_RESET					(1 << 27)	
/* 29-31 NVRAM Access Control */


/* PCI bus control registers */
#define SI500_REGISTER_COMMAND	0x000


/* Driver specific IOCTL commands */
#define SI500_IOCTL_NULL_COMMAND			0
#define SI500_IOCTL_RESET			1
#define SI500_IOCTL_INITIALIZE_DETECTOR		2
#define SI500_IOCTL_DOWNLOAD_HV			3
#define SI500_IOCTL_READ_TEST_IMAGE		4
#define SI500_IOCTL_OPEN_SHUTTER			5
#define SI500_IOCTL_CLOSE_SHUTTER		6
#define SI500_IOCTL_EXPOSE_AND_READ		7
#define SI500_IOCTL_READ_CCD			8
#define SI500_IOCTL_EXPOSE_CCD			9
#define SI500_IOCTL_CLEAR_CCD			10
#define SI500_IOCTL_DOWNLOAD_READOUT_FORMAT	11
#define SI500_IOCTL_DOWNLOAD_SYSTEM_PARAMETER	12
#define SI500_IOCTL_UPLOAD_STATUS		13
#define SI500_IOCTL_DOWNLOAD_EXPOSURE_TIME	14
#define SI500_IOCTL_DOWNLOAD_TDI_DELAY_TIME	15
#define SI500_IOCTL_DOWNLOAD_ANALOG_OFFSET	16
#define SI500_IOCTL_START_TDI_READOUT		17
#define SI500_IOCTL_STOP_TDI_READOUT		18
#define SI500_IOCTL_CALIBRATE_ADC		19

#define SI500_IOCTL_INIT_DMA_BUFFER		101
#define SI500_IOCTL_FREE_DMA_BUFFER		102
#define SI500_IOCTL_INITIALIZE_INTERFACE		103
#define SI500_IOCTL_START_DATA_TRANSFER_INBOUND	104
#define SI500_IOCTL_STOP_DATA_TRANSFER_INBOUND	105
#define SI500_IOCTL_BLOCK_UNTIL_READ_COMPLETE	106
#define SI500_IOCTL_SET_READ_SCHEME		107

/* ASCII Commands to the Spectral Controller */
#define SI500_COMMAND_NULL				'\0'
#define SI500_COMMAND_RESET				'\0'
#define SI500_COMMAND_INITIALIZE			'\0'
#define SI500_COMMAND_DOWNLOAD_HV			'A'
#define SI500_COMMAND_CALIBRATE_ADC			'\0'
#define SI500_COMMAND_READ_TEST_IMAGE			'B'
#define SI500_COMMAND_OPEN_SHUTTER			'C'
#define SI500_COMMAND_CLOSE_SHUTTER			'D'
#define SI500_COMMAND_EXPOSE_AND_READ			'E'
#define SI500_COMMAND_READ_CCD				'F'
#define SI500_COMMAND_EXPOSE_CCD			'\0'
#define SI500_COMMAND_CLEAR_CCD				'G'
#define SI500_COMMAND_DOWNLOAD_READOUT_FORMAT		'H'
#define SI500_COMMAND_DOWNLOAD_SYSTEM_PARAMETER		'I'
#define SI500_COMMAND_UPLOAD_STATUS			'J'
#define SI500_COMMAND_DOWNLOAD_EXPOSURE_TIME		'K'
#define SI500_COMMAND_DOWNLOAD_TDI_DELAY_TIME		'L'
#define SI500_COMMAND_DOWNLOAD_ANALOG_OFFSET		'M'
#define SI500_COMMAND_START_TDI_READOUT			'N'
#define SI500_COMMAND_STOP_TDI_READOUT			'O'

#define SI500_RESPONSE_GOOD				'Y'
#define SI500_RESPONSE_BAD				'N'



/* These structures will be part of the driver code !!! */
struct _si500_format_parameters {
   int    pixel_depth; 
   int    serial_origin, serial_length, serial_binning, serial_postscan; 
   int    parallel_origin, parallel_length, parallel_binning, parallel_postscan; 
   int    nreadouts, readouts_in_use; 
   };

typedef struct _SI500IOCTLParameters {
   int    structure_type;
   int    detector_type;
   int    detector_version;
   int    detector_status;
   int    interface_type;
   int    interface_version;
   int    interface_status;
   struct _si500_format_parameters readout;
   struct _si500_format_parameters image;
   double voltage1, voltage2;
   int    parallel_shift_delay;
   int    ccd_temp_offset, backplate_temp_offset, pressure_offset, temp_setpoint;
   int    ccd_temperature, backplate_temperature, chamber_pressure;
   int    exposure_time;
   int    TDI_delay_time;
   int    analog_offset;
   int    dma_buffer_size;
   int    read_active;
   int    bytes_remaining;
   unsigned long    dma_buffer_address;
   unsigned long    next_dma_address;
   char    auxillary_device_name[64];
   int     auxillary_device_type;
   int     auxillary_device_fd;
   void    *dsp_binary;
   char    *dsp_binary_name;
   int     dsp_binary_size;
   char    dsp_binary_revision[8];
} SI500IOCTLValues;

/* A Function for each type of detector */
extern detector_functions *get_detector_si500(void);


#endif /* si500_h */
