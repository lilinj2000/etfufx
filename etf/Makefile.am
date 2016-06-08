AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = etfufx

etfufx_SOURCES = ETFConfig.cc ZMQService.cc main.cc


etfufx_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include \
	 $(BOOST_CPPFLAGS) $(T2SDK_CPPFLAGS) \
	 $(SOIL_CPPFLAGS) $(ZMQ_CPPFLAGS)

etfufx_LDADD = 	$(BOOST_LIBADD) \
		$(SOIL_LIBADD) \
		$(T2SDK_LIBADD) \
		$(ZMQ_LIBADD) \
		../ufx/libufx.la

etfufx_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed  -pthread 

# header files
noinst_HEADERS = ETFConfig.hh ETFLog.hh ZMQService.hh

EXTRA_DIST = env.sh etf.cfg t2sdk.ini log.cfg license.dat

extradir = $(bindir)
extra_DATA = env.sh etf.cfg t2sdk.ini log.cfg license.dat

# dist-hook:
# 	ln -s ../service/ufx.cfg ufx.cfg
# 	ln -s ../service/t2sdk.ini t2sdk.ini
# 	ln -s ../service/log.cfg log.cfg

