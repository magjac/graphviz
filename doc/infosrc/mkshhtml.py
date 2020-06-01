#!/usr/bin/env python3

from dataclasses import dataclass
import jinja2
import markupsafe
import re
import sys
from typing import List, Dict

N_PER_ROW=4

shapes = []
for line in sys.stdin:
  shape = line.strip()
  shapes.append(shape)

# From https://stackoverflow.com/a/312464/171898
def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]

# Use the shapes name in shape list to create the
# contents of an HTML array.

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
template = env.get_template('shapes.html.j2')
print(template.render(rows=chunks(shapes, N_PER_ROW)))
