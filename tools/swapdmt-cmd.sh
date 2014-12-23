#!/usr/bin/env bash

PANSTAMPDIR=${0%/*}/panstamp/python
export PYTHONPATH=$PANSTAMPDIR/pyswap/${PYTHONPATH:+:$PYTHONPATH}

RLWRAP="$(type -fp rlwrap 2>/dev/null)"

exec $RLWRAP ${PYTHON:-python} $PANSTAMPDIR/swapdmt-cmd/swapdmt.py "$@"
