AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libsmack.la
libsmack_la_SOURCES = \
		socket_multicast.cc \
		md_options.cc \
		md_service_impl.cc

libsmack_la_CPPFLAGS = \
	-I$(top_srcdir) \
	$(BOOST_CPPFLAGS) \
	$(SOIL_CPPFLAGS) \
	$(RAPIDJSON_CPPFLAGS) \
	$(FMT_CPPFLAGS) \
	$(SPDLOG_CPPFLAGS)

libsmack_la_LIBADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(FMT_LIBADD)

libsmack_la_LDFLAGS = \
	-no-undefined -version-info \
	$(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	-release $(LT_RELEASE)

# header files
noinst_HEADERS = \
	socket_multicast.h \
	md_options.h \
	md_service_impl.h



