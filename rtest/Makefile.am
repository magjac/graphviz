SUBDIRS = graphs linux.x86

check test rtest: $(top_builddir)/cmd/dot/dot_builtins $(top_builddir)/contrib/diffimg/diffimg
	./rtest.sh

EXTRA_DIST = graphs nshare rtest.sh strps.awk tests.txt tests_subset.txt test_regression.py
