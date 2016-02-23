AUTOMAKE_OPTIONS = foreign

SUBDIRS = 

noinst_PROGRAMS = unittest

unittest_SOURCES = \
	MDServiceImplTest.cc


unittest_CPPFLAGS = -I$(top_srcdir) -I.. -I..\
		$(BOOST_CPPFLAGS) \
		$(GTEST_CPPFLAGS) \
		$(SOIL_CPPFLAGS)


unittest_LDADD = \
	$(GTEST_LIBADD) \
	../service/libsmack.la \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD)



unittest_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = 

EXTRA_DIST = log.cfg smack.cfg env.sh

