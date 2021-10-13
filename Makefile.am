
JANSSON_CPPFLAGS= -I$(top_builddir)/compat/jansson-2.13.1/src -I$(top_srcdir)/compat/jansson-2.13.1/src
USBUTILS_CPPFLAGS = -I$(top_builddir)/compat/libusb-1.0/libusb -I$(top_srcdir)/compat/libusb-1.0/libusb

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST	= mm.mcs hexdump.c

SUBDIRS = compat

bin_PROGRAMS = mm-tools

MM_TOOLS_CPPFLAGS = $(JANSSON_CPPFLAGS) $(USBUTILS_CPPFLAGS)
MM_TOOLS_LDADD	= @JANSSON_LIBS@ @LIBUSB_LIBS@ @PTHREAD_FLAGS@ @MATH_LIBS@

MM_TOOLS_SOURCES = main.c
MM_TOOLS_SOURCES += api.h auc.h crc.h iic.h auc.c mboot_api.c mm_api.c iic_rpi.c iic_auc.c
if USE_SOFT_CRC
MM_TOOLS_SOURCES += crc16_soft.c
else
MM_TOOLS_SOURCES += crc16.c
endif

if USE_FLASH_LAYOUT_2M
MM_TOOLS_CPPFLAGS += -DUSE_FLASH_LAYOUT_2M
endif

