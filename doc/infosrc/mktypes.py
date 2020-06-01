#!/usr/bin/env python3
from dataclasses import dataclass
import jinja2
import markupsafe
import sys
from typing import List


@dataclass
class Type:
    name: str
    html_description: str


types: List[Type] = []

for line in sys.stdin:
    # Skip comment lines.
    if line.startswith('#'):
        continue
    if line.startswith(':'):
        # This is a header line. Grab out the values.
        types.append(Type(
            name=line[1:].rstrip(),
            html_description=''
        ))
    else:
        # This is an HTML line, possibly a continuation of a previous HTML line.
        t = types[-1]
        # This is purely so the diffs look the same porting from ksh, could
        # delete this later.
        if t.html_description != '':
            t.html_description += '  '
        t.html_description += line

types.sort(key=lambda t: t.name)

for t in types:
    t.html_description = markupsafe.Markup(t.html_description)

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
template = env.get_template('types.html.j2')
print(template.render(
    types=types,
))
