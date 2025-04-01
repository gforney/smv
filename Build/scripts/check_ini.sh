#!/bin/bash
FILE=$1

SHOWFRAME=`grep -w -A 1 SHOWFRAME $FILE | tail -1 | awk '{print $1}'` 
if [ "$SHOWFRAME" == "" ]; then
  SHOWFRAME=0
fi
OUTLINE=`grep -w -A 1 OUTLINEMODE $FILE | tail -1 | awk '{print $1}'` 
if [ "$OUTLINE" == "" ]; then
  OUTLINE=0
fi
if [[ "$SHOWFRAME" == "0" ]] && [[ "$OUTLINE" != "0" ]]; then
  echo ***warning: $FILE SHOWFRAME=$SHOWFRAME OUTLINE=$OUTLINE
fi
if [[ "$SHOWFRAME" != "0" ]] && [[ "$OUTLINE" == "0" ]]; then
  echo ***warning: $FILE SHOWFRAME=$SHOWFRAME OUTLINE=$OUTLINE
fi
