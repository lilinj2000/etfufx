AUTOMAKE_OPTIONS = foreign

noinst_PROGRAMS = unittest

unittest_SOURCES = ETFConfigTest.cc TraderServiceImplTest.cc \
		   ZMQTest.cc


unittest_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include \
	 $(GTEST_CPPFLAGS) $(BOOST_CPPFLAGS) $(T2SDK_CPPFLAGS) \
	 $(SOIL_CPPFLAGS) $(ZMQ_CPPFLAGS)

unittest_LDADD = $(GTEST_LIBADD) \
		$(BOOST_LIBADD) \
		$(SOIL_LIBADD) \
		$(T2SDK_LIBADD) \
		$(ZMQ_LIBADD) \
		../ufx/libufx.la \
		../etf/etfufx-ETFConfig.o

unittest_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed  -pthread 

# header files
noinst_HEADERS = ZMQPubService.hh

EXTRA_DIST = env.sh etf.cfg t2sdk.ini log.cfg license.dat

# dist-hook:
# 	ln -s ../service/ufx.cfg ufx.cfg
# 	ln -s ../service/t2sdk.ini t2sdk.ini
# 	ln -s ../service/log.cfg log.cfg

