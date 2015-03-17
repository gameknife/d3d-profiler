 @echo off
 	rem this file made by yikaiming 2012/12/13

    rem batch gammar reference
    
    rem echo %%~dpnA disk + dir + name
    rem echo %%~sA name+ext
    rem echo %%~nA name
    rem echo %%~fA abspathname
    rem echo %%~xA ext
    rem echo %%~pA dik
	
del immediate\* /Q /S /F
rmdir immediate /Q /S
del *.pdb /Q /S /F
del *.ilk /Q /S /F
del *.user /Q /S /F
del *.ipch /Q /S /F
del *.sdf /Q /S /F
del *.aps /Q /S /F
del bin\* /Q /S /F
rmdir bin /Q /S
del ipch\* /Q /S /F
rmdir ipch /Q /S
pause