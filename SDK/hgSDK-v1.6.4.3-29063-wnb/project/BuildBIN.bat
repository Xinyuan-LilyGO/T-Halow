cd /d %~dp0

copy .\Obj\txw4002a.ihex project.hex
copy ..\..\..\..\tools\makecode\BinScript.exe BinScript.exe
copy ..\..\..\..\tools\makecode\crc.exe crc.exe
copy ..\..\..\..\tools\makecode\makecode.exe makecode.exe
copy ..\..\..\..\tools\makecode\makecode_post.bat makecode_post.bat
copy ..\..\..\..\tools\makecode\makedis.bat makedis.bat

BinScript.exe BinScript.BinScript
makecode.exe
::crc.exe crc.ini
::BinScript.exe BinScript_Bin2Hex.BinScript

::pause
