#!/usr/bin/env bash

PANSTAMPDIR=${0%/*}/panstamp/python
export PYTHONPATH=$PANSTAMPDIR/pyswap/src/${PYTHONPATH:+:$PYTHONPATH}

exec ${PYTHON:-python} $PANSTAMPDIR/pyswapdmt/src/pyswapdmt.py "$@"
