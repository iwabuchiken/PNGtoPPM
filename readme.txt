------------------------
06/05/2014 13:42:46

	To run the program
------------------------
# Win
pushd C:\WORKS\WS\WS_Android_20130929_122122\IP
.\dist\Debug\MinGW-Windows\ip.exe
.\dist\Debug\MinGW-Windows\ip.exe lena512.pgm -rgb 10,20,50
.\dist\Debug\MinGW-Windows\ip.exe ..\image_processing_Nagao_2\D-4\images\lena512.pgm -rgb 10,10,100 -dst .\images\lena512.ppm -ff -f
.\dist\Debug\MinGW-Windows\ip.exe -rgb 100,100,100 -dst .\images\lena512.ppm -ff -f -src ..\image_processing_Nagao_2\D-4\images\lena512.pgm

# Ubuntu
pushd /home/buchi/WORKS/WS/NetBeans/PNGtoPPM
./dist/Debug/GNU-Linux-x86/pngtoppm

#REF https://help.ubuntu.com/community/CommandlineHowto#Multiple_Commands
pushd /home/buchi/WORKS/WS/NetBeans/PNGtoPPM && gitk &
pushd /home/buchi/WORKS/WS/NetBeans/PNGtoPPM
gitk &

pushd /home/buchi/WORKS/WS/NetBeans/PNGtoPPM/images
pushd /home/buchi/WORKS/WS/NetBeans/PNGtoPPM/dist/Debug/GNU-Linux-x86/

/home/buchi/WORKS/WS/NetBeans/PNGtoPPM/dist/Debug/GNU-Linux-x86/pngtoppm

#merge_png.c
/home/buchi/WORKS/WS/NetBeans/PNGtoPPM/dist/Debug/GNU-Linux-x86/pngtoppm images/download-jpg.copy.png images/download-jpg.copy-6.png images/download-jpg.merged-6.png
./dist/Debug/GNU-Linux-x86/pngtoppm images/download-jpg.copy.png images/download-jpg.copy-6.png images/download-jpg.merged-6.png

#merge_png.c => threshold 24/05/2014 17:01:53
#merge_png.c => -proc
./dist/Debug/GNU-Linux-x86/pngtoppm images/download-jpg.copy.png images/latin_jazz.png images/merge-process-1.png -proc -rgb 0,100,0 -src images/download-jpg.copy.png -dst images/download-jpg.copy.processed-6.png

#merge_png.c => -histo
./dist/Debug/GNU-Linux-x86/pngtoppm -histo -src images/download-jpg.copy.png -dst images/histo-1.png

./dist/Debug/GNU-Linux-x86/pngtoppm images/download-jpg.png images/download-jpg.copy.png
------------------------

    Ignored by file system
	
------------------------
^(CVS|SCCS|vssver.?\.scc|#.*#|%.*%|_svn)$|~$|^\.(?!htaccess$).*$


------------------------

	Log
------------------------
gedit /home/buchi/WORKS/WS/NetBeans/PNGtoPPM/log/exec_log.txt &

------------------------


	Git
------------------------
//REF http://tobysoft.net/wiki/index.php?git%2F%A5%B3%A5%DE%A5%F3%A5%C9%A4%CE%BE%CA%CE%AC(alias)%C0%DF%C4%EA%A4%F2%A4%B9%A4%EB%CA%FD%CB%A1#t6684adb
git config --global alias.co checkout
git config --global alias.c commit
git config --global alias.s status
git config --global alias.l log
git config --global user.email "iwabuchi.k.2010@gmail.com"
git config --global user.name "iwabuchiken"

------------------------


	Structure: include
------------------------
main.c  -> pnglib.h -> lib.h
                    -> img_lib.h

pgmlib.h    -> img_lib.h

================ EOF ================