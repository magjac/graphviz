dot -V 2>&1 | grep "dot - graphviz version ${GV_VERSION}" || (dot -V && false)
