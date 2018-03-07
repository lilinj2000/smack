AUTOMAKE_OPTIONS = foreign

SUBDIRS = 

check_PROGRAMS = unittest

unittest_SOURCES = \
	md_service_test.cc


unittest_CPPFLAGS = \
	-I$(top_srcdir) \
	$(BOOST_CPPFLAGS) \
	$(GTEST_CPPFLAGS) \
	$(SOIL_CPPFLAGS) \
	$(RAPIDJSON_CPPFLAGS) \
	$(FMT_CPPFLAGS) \
	$(SPDLOG_CPPFLAGS)


unittest_LDADD = \
	$(GTEST_LIBADD) \
	../service/libsmack.la \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(FMT_LIBADD)

unittest_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = 

EXTRA_DIST = smack.json env.sh

