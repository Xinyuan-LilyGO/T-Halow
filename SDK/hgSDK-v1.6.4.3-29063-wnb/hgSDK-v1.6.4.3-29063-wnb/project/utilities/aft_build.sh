#!/bin/bash

cp -f ./Obj/txw4002a_wnb.ihex project.hex
cp -f ../../../../../tools/makecode/BinScript.exe BinScript.exe
cp -f ../../../../../tools/makecode/crc.exe crc.exe
cp -f ../../../../../tools/makecode/makecode.exe makecode.exe

BinScript.exe BinScript.BinScript
makecode.exe
