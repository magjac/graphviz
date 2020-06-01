#!/usr/bin/env python3
# Filter taking a list of attribute descriptions as stdin
# and producing a summary table, followed by a list of
# attribute descriptions.
# Uses `templates/attrs.html.j2`
# See `attrs` file for format documentation.

from dataclasses import dataclass
import jinja2
import markupsafe
import re
import sys
from typing import List, Dict

@dataclass
class Term:
  """ One <dt> item. """
  name: str
  # Anchor (<a name="#">) for definition
  d_anchor: str = ""
  # Anchor (<a name="#">) for table at the top
  a_anchor: str = ""

@dataclass
class Attribute:
    terms: List[Term]
    # use string : this is a string formed of G,N,C,E
    uses: str
    kinds: List[str]
    flags: List[str]
    html_description: str
    defaults: List[str]
    minimums: List[str]

attrs : List[Attribute] = []

for line in sys.stdin:
    # Skip comment lines.
    if line.startswith('#'):
        continue

    if line.startswith(':'):
        # This is a header line. Grab out the values.
        #    :name:uses:kind[:dflt[:minv]];  [notes]
        headers, _, flags = line.rpartition(';')
        parts = headers.split(':')

        attr = Attribute(
            terms=[Term(name=name) for name in parts[1].split('/')],
            uses=parts[2],
            kinds=parts[3].split('/'),
            flags=[flag for flag in flags.strip().split(',') if flag],
            # Set an empty string html description, ready to append to.
            html_description='',
            # Remaining fields are optional.
            # First, check for default value: this has format :dflt1[/dflt2]*
            defaults=parts[4].split('/') if len(parts) >= 5 else [],
            # Check for minimum value: this has format /min1[/min2]*
            minimums=parts[5].split('/') if len(parts) >= 6 else [],
        )
        attrs.append(attr)

    else:
        # This is an HTML line, possibly a continuation of a previous HTML line.
        attr.html_description += '  ' + line


attrs.sort(key=lambda attr: ''.join(term.name for term in attr.terms))

for attr in attrs:
  attr.html_description = markupsafe.Markup(attr.html_description)

# The specification allows items with the same attribute name.
# This creates unique anchor keys, which are n copies of 'a' and 'd'.
a_anchors_used = set()
d_anchors_used = set()
for attr in attrs:
  for term in attr.terms:
    a_key = 'a'
    d_key = 'd'
    a_anchor = a_key + ':' + term.name
    d_anchor = d_key + ':' + term.name
    while a_anchor in a_anchors_used:
      a_key += 'a'
      a_anchor = a_key + ':' + term.name
    while d_anchor in d_anchors_used:
      d_key += 'd'
      d_anchor = d_key + ':' + term.name
    a_anchors_used.add(a_anchor)
    d_anchors_used.add(d_anchor)
    term.a_anchor = a_anchor
    term.d_anchor = d_anchor


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
template = env.get_template('attrs.html.j2')
print(template.render(attrs=attrs))
