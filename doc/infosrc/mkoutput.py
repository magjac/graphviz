#!/usr/bin/env python3
# Takes `outputs` as stdin and generates output.html
# Uses `templates/output.html.j2`
# See `outputs` file for format documentation.

import jinja2
import markupsafe
import re
import sys
from typing import Dict, Tuple

HEADER_RE = re.compile(r'^:(?P<params>[^:]+):(?P<format>.*)')

# Tuple of command-line-params for an output format, e.g. ('jpg', 'jpeg', 'jpe')
params : Tuple[str, ...] = ()

# Map from tuple of command-line-params to full name of the output format
formats : Dict[Tuple[str, ...], str] = {}

# Map from tuple of command-line-params to an HTML description string
html_descriptions : Dict[Tuple[str, ...], str]  = {}

for line in sys.stdin:
    # Skip comment lines.
    if line.startswith('#'):
        continue

    m = HEADER_RE.match(line)
    if m:
        # This is a header line. Grab out the values.

        # Command-line formats are slash-separated.
        params = tuple(m.group('params').split('/'))

        # Full format name is plain text
        formats[params] = m.group('format')

        # Set an empty string html description, ready to append to.
        html_descriptions[params] = ''
    else:
        # This is an HTML line, possibly a continuation of a previous HTML line.
        html_descriptions[params] += line


env = jinja2.Environment(
    # Load template files from ./templates/
    loader=jinja2.FileSystemLoader('templates'),
    # Auto-HTML-escape any html or xml files.
    autoescape=jinja2.select_autoescape(['html', 'xml', 'html.j2', 'xml.j2']),
    # Whitespace control
    trim_blocks=True,
    lstrip_blocks=True,
    # Raise exception on any attempt to access undefined variables.
    undefined=jinja2.StrictUndefined,
)
template = env.get_template('output.html.j2')
print(template.render(
    formats=formats,
    # Vouch for the HTML descriptions as being safe and not needing auto-HTML-escaping.
    # This is reasonable because the HTML descriptions are not attacker-controlled.
    descriptions={
        params: markupsafe.Markup(desc)
        for params, desc in html_descriptions.items()
    }
))
