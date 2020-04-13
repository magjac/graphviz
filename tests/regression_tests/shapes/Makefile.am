SUBDIRS = reference

check test rtest:
	if command -v python3; then \
		python3 shapes.py; \
	else \
		python2 shapes.py; \
	fi

EXTRA_DIST = shapes.py
