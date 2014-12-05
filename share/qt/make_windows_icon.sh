#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/paycoin.png
ICON_DST=../../src/qt/res/icons/paycoin.ico
convert ${ICON_SRC} -resize 16x16 paycoin-16.png
convert ${ICON_SRC} -resize 32x32 paycoin-32.png
convert ${ICON_SRC} -resize 48x48 paycoin-48.png
convert paycoin-48.png paycoin-32.png paycoin-16.png ${ICON_DST}

