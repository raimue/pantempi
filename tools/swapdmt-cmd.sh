#!/usr/bin/env bash

PANSTAMPDIR=${0%/*}/panstamp/python
export PYTHONPATH=$PANSTAMPDIR/pyswap/${PYTHONPATH:+:$PYTHONPATH}

exec ${PYTHON:-python} $PANSTAMPDIR/swapdmt-cmd/swapdmt.py "$@"
