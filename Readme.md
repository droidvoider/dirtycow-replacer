**PLEASE NOTICE I AM NOT TESTING THIS CODE ANYWHERE EVER! IT IS BEING DESIGNED AS AN EDUCATIONAL TOOL**
**PLEASE NOTICE I AM NOT TESTING THIS CODE ANYWHERE EVER! IT IS BEING DESIGNED AS AN EDUCATIONAL TOOL**
**PLEASE NOTICE I AM NOT TESTING THIS CODE ANYWHERE EVER! IT IS BEING DESIGNED AS AN EDUCATIONAL TOOL**

**What's it do?**
android-dirtycow-replacer uses the CVE-2016-5195 dirtycow exploit to patch a list of over 1000 files.
You can edit it to be 10000 but 1000 should do.
It checks first to make sure the files differ, if not it attempts to replace and if error it halts.
It is your job to provide the files by editing them, or patching your selinux, or whatever.
dirtycow only replaces what it can read, and that's why this tool isn't the final tool.

**Sorry if I said some things twice I have coder head**
This is code was tested on a Note 5 and does appear to function correctly. However...
This code is mostly untested and is not the final project. I am designing a toolbox.c dirtycow exploit
which will over-write files normally unreadable, such as init.
Why toolbox? Because I can grab root + context I need by exploiting toolbox then read all files I want. 

**Requires**
Linux, such as the latest version of Ubuntu (free), and the Android SDK & Android NDK (also free).

**Directions**
Create a file named files.txt with paths left/right of what you wish to replace.
/system/build.prop /data/local/tmp/replace/build.prop
Make sure your files exist on both sides of the equation, pretty simple stuff I hope!
I suggest trying to cat the file before even adding it to the list. example: adb shell cat /init
**path on the left is file being replaced (notice the space) path on the right is file to replace it with**

**Example included**
An example files.txt exists with this example. It points to test files (edit it to see)
There are also two directories containing test files. replace/ and replacewith/
Inside the replace/ directory are 4 files beingpatched1, beingpatched2,..3,..4
beingpatched# text == unpatched001 --- unpatched004
The files in replacedwith/ contain text patchingdon1 through patchingdon4
When you type 'make push' it will compile and these directories, files.txt and replacer will be pushed to
/data/local/tmp/
..still with me?, imagine writing it
**Actual Directions for Example**
Unzip to a folder, right click and open two terminals in this folder
......tip: if you click one terminal window and then the other both terminal windows remain visible
In one terminal window type: make log
In the next terminal window type:
make push  <===No errors right? don't proceed on errors
adb shell
cd data/local/tmp
./replacer

**Overview of main project -- Not this project**
**The compare function is being designed as the trigger for toolbox.c**
The compare function compares files byte by byte to determine if they differ. This will be the trigger
for toolbox.c to attempt to reload /init. Next toolbox.c will write a log file (the next trigger key also)
toolbox.c will log post attempt to another log file (the final trigger) letting us know all functions
attempted. This will enable us to try multiple contexts for each phase upon failure before giving up, likely needed.

**android-dirtycow-replacer**
My goal is to design an automated dirtycow.c replacement tool to use as an exploit inside toolbox.c or dumpstat.c
android-dirtycow-replacer reads files to patch from a text file, it then tests to see if the files differ and if 
then only if they do differ android-dirtycow-replacer will patch the files using dirtycow.c.
Again this code is being designed to merge into toolbox.c / dumpstate.c as a means to patch unpatchable files!
My final code will likely be entwined with UID and context handling code. This is the fork in my own code.

**This app may have other uses**
But I am not designing it for other uses at this time. 
The most viable usage that comes to mind is replacing a constant list of files post boot, such as font's or removing
permissions for apps to have access to the internet while your screen is off. Or many many other settings under /etc
which will be repaired after each boot.

**REQUIRED**
1. You must be able to read the file on your Android Device to be able to patch it. cat /init for example, did it spit out garble?
2. Make sure your replacement files are the same sizes or you will seg fault out and this app will hang
3. There can be no errors in the process or the app is designed to bail
4. Add more error handling, I didn't add much at all.
5. Make sure USB Debugging is enabled and that you can adb shell into your device.
6. Always plug in your device before typing 'make'

**Software not being updated at this time. Software being listed as example code**
I personally believe this tool could achieve root on any device within scope as it stands. I also believe it is a powerful
organizational tool for achieving exactly that goal. The problem for me is I have no interest in gaining root on my personal
cell phone at this time. I crashed out just enough stuff that my Note 5 is so amazing and it's a hard task to setup again.
**PLEASE NOTICE I AM NOT TESTING THIS CODE ANYWHERE EVER! IT IS BEING DESIGNED AS AN EDUCATIONAL TOOL**

**If you have an issue**
Please list the issue and I will correct it when I can as long as I can safely do so on my test device.

