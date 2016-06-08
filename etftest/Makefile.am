AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = etftest

etftest_SOURCES = ETFClientOptions.cc ZMQClient.cc main.cc


etftest_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include \
	 $(BOOST_CPPFLAGS) $(T2SDK_CPPFLAGS) \
	 $(SOIL_CPPFLAGS) $(ZMQ_CPPFLAGS)

etftest_LDADD = 	$(BOOST_LIBADD) \
		$(SOIL_LIBADD) \
		$(ZMQ_LIBADD) 


etftest_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed  -pthread 

# header files
noinst_HEADERS = ETFClientOptions.hh ZMQClient.hh

EXTRA_DIST = etfclient.cfg 

extradir = $(bindir)
extra_DATA = etfclient.cfg 

# dist-hook:
# 	ln -s ../service/ufx.cfg ufx.cfg
# 	ln -s ../service/t2sdk.ini t2sdk.ini
# 	ln -s ../service/log.cfg log.cfg

