AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libufx.la
libufx_la_CPPFLAGS = -I$(top_srcdir)/include $(BOOST_CPPFLAGS) $(T2SDK_CPPFLAGS) $(SOIL_CPPFLAGS)
libufx_la_SOURCES = UFXUtil.cc TraderServiceImpl.cc
libufx_la_LIBADD = \
		$(BOOST_LIBADD) \
		$(T2SDK_LIBADD) \
		$(SOIL_LIBADD)

libufx_la_LDFLAGS = \
	-no-undefined -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	-release $(LT_RELEASE) 

# header files
noinst_HEADERS = UFXDef.hh UFXLog.hh \
		 UFXUtil.hh TraderServiceImpl.hh


