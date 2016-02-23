AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libsmack.la
libsmack_la_SOURCES = \
		SocketMulticast.cc \
		MDOptions.cc \
		MDServiceImpl.cc

libsmack_la_CPPFLAGS = -I$(top_srcdir) \
			$(BOOST_CPPFLAGS) \
			$(SOIL_CPPFLAGS)

libsmack_la_LIBADD = $(REM_LIBADD) \
		$(BOOST_LIBADD) \
		$(SOIL_LIBADD)

libsmack_la_LDFLAGS = \
	-no-undefined -version-info \
	$(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	-release $(LT_RELEASE)

# header files
noinst_HEADERS = \
	SocketMulticast.hh \
	MDOptions.hh \
	MDServiceImpl.hh \
	SmackLog.hh


