# Developer's Guide

## Table of contents

[[_TOC_]]

## How to make a release

### A note about the examples below

The examples below are for the 2.44 release. Modify the version
number for the actual release. The example commits were cherry-picked
from different releases since mistakes were made during the 2.44
release (and all other previous releases as well).

### Using a fork or a clone of the original repo

The instructions below assume that the actions are performed from a
fork and that the orignal repository has been added as a remote with:

`git remote add graphviz https://gitlab.com/graphviz/graphviz.git`

If the actions instead are performed from a clone of the orignal repo,
`git push graphviz` should be replaced with `git push origin`.

### Deciding the release version number

This project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).
Before making the release, it must be decided if it is a *major*, *minor* or
*patch* release.

#### Stable release versions and development versions numbering convention

Stable release versions always have an *even* minor version and
development versions always have an *odd* minor version that is the
latest stable release minor version *plus* 1. Development releases
have the patch version automatically set to the
[committer date](https://git-scm.com/docs/pretty-formats#Documentation/pretty-formats.txt-emciem)
(not the [author date](https://git-scm.com/docs/pretty-formats#Documentation/pretty-formats.txt-emadem)
which is what `git log` shows by default) of the latest commit using the format `%Y%m%d.%H%M`.

Release version examples:

- 2.42.3
- 2.42.4
- 2.44.0

Development version examples:

- 2.43.20200403.0503
- 2.45.20200601.1555

### Instructions

1. Check that the
[master pipeline](https://gitlab.com/graphviz/graphviz/-/pipelines?ref=master)
is green

1. Edit `autogen.sh`, `appveyor.yml` and `CMakeLists.txt`:

   Incement patch version with 1 *or* minor version to the next *even* number.

   Example: 466402bb70105dd74282cd9da6bbde9da02a9b3c
   and 2cc6ed876212ec65fccd4a90028335b338d3ccc0 (for release 2.42.4).

1. Edit `CHANGELOG.md` (provided that !1394 is merged)

   Add the new version between `[Unreleased]` and the previous
   version.

   At the bottom of the file, add an entry for the new version. These
   entries are not visible in the rendered page, but are essential for
   the version links to the GitLab commit comparisons to work.

   Updating the `CHANGELOG.md` has never yet been done for the
   Graphviz project, but [this
   example](https://github.com/magjac/d3-graphviz/commit/59f515686a3fdb4da2a04d02665abfb2e583d898#diff-4ac32a78649ca5bdd8e0ba38b7006a1e)
   shows how it's done for another project.

1. Commit:

   `git add -p`

   `git commit -m "Stable Release 2.44.0"`

1. Push:

   `git push graphviz master`

1. Wait for the
[master pipeline](https://gitlab.com/graphviz/graphviz/-/pipelines?ref=master)
to run for the new commit and check that it succeeds

1. Tag release:

   `git tag -a -m "Stable Release 2.44.0" stable_release_2.44.0`

1. Push tag:

   `git push graphviz stable_release_2.44.0`

1. Create a release at [GitHub releases](https://gitlab.com/graphviz/graphviz/-/releases)

   Create a new tag *without* the `stable_release_` prefix: `2.44.0`

1. Edit `autogen.sh`, `appveyor.yml` and `CMakeLists.txt`.

   Update the release again for the next devevelopment series. If
   minor release, increment minor version to the next odd number and
   zero the patch version, *otherwise* increment the patch
   version. See e.g.  28e09c876c4c01e979b5801c89f6f59855c8b4ca and
   fa40209b378c8435fd1c8d6c74ff0ff95c9f45b2

1. Commit:

    `git add -p`

    If patch version was incremented:

    `git commit -m "Move back to 2.43 development series"`

    else (if major or minor version was incremented):

    `git commit -m "Start 2.45 development series"`

1. Push:

    `git push graphviz master`

1. Update the links to the release on the **Downloads** web page through
[Edit this page](https://gitlab.com/graphviz/graphviz.gitlab.io/-/edit/master/_pages/10_download.md):
   - Visit the
   [Appveyor history](https://ci.appveyor.com/project/ellson/graphviz-pl238/history)
   and find the URL to the Windows release build.
   - In the **Windows** section, for the **Stable 2.44 Windows install packages** link:
     - Update the text with the new version number.
     - Update the link with the new URL.
     Example: [23bf8be297b9b4d11d345020acbe823f76bee267](https://gitlab.com/graphviz/graphviz.gitlab.io/-/commit/23bf8be297b9b4d11d345020acbe823f76bee267).

1. Update the links to the released source code package files on the **Sources** web
page through
[Edit this page](https://gitlab.com/graphviz/graphviz.gitlab.io/-/edit/master/download/source/index.md):
   - Visit the
   [portable_source](https://www2.graphviz.org/Packages/stable/portable_source/)
   directory
   and find the URL's to the `tar.gz` and the `tar.gz.md5` files.
   - In the **current stable release** column in the **graphviz** table:
     - Update the text with the new version number.
     - Update the links with the new URL's.

### TODO (with these release instructions)

- Update the example commits above after next release (provided that
  we manage to get it right the first time) and remove the note about
  it at the top and the reference to "another project".

- Add an example commit for the **Sources** page after the next release.

- Investigate if the tagging can be simplifed when making the next
  release. The current approach using dual tags is based on that we
  wanted to tag before push and then make a GitLab release. It didn't
  seem possible to create a GitLab release for an existing tag, hence
  to need to create another tag without the `stable_release_` prefix
  (This seemed to be a good idea at the time but might have been the
  wrong conclusion).

## How to update this guide

### Markdown flavor used

This guide uses
[GitLab Flavored Markdown (GFM)](https://docs.gitlab.com/ce/user/markdown.html#gitlab-flavored-markdown-gfm]).

### Rendering this guide locally

This guide can be rendered locally with e.g. [Pandoc](https://pandoc.org/):

`pandoc DEVELOPERS.md --from=gfm -t html -o DEVELOPERS.html`

### Linting this guide locally

[markdownlint-cli](https://github.com/igorshubovych/markdownlint-cli)
can be used to lint it.
