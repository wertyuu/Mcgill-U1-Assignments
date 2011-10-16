#!/usr/bin/env bash

if [ $1 != '-o' ];then
    echo -e "\nerror: expected first argument -o\n"
    echo -e "USAGE: compile -o filename [-clean] [-backup] [-archive] [-help] cfilenames\n"
    echo -e "DESCRIPTION:\n"
    echo -e "\t-o filename, \tnon-optional argument. Place output in file filename.\n"
    echo -e "\t-clean, \toptional argument. Deletes .o files before compile\n"
    echo -e "\t-backup, \toptional argument. copies all .c and .h files into backup dir.\n"
    echo -e "\t-archive, \toptional argument. TARS source dir and moves archive to backup dir.\n"
    echo -e "\t-help, \t\toptional argument. shows USAGE and DESCRIPTION.\n"
    echo -e "\tcfilenames, \toptional argument. Source files to be compiled.\n"
    echo -e "EXAMPLE:\n"
    echo -e "\tcompile -o myFile -clean -backup -archive -help f1.c f2.c f3.c\n"
else
    for var in $*
    do
        case $var in
        '-clean')
            rm *.o;;
        '-backup')
            cp *.c ../backup
            cp *.h ../backup;;
        '-archive')
            tar -cvzf ../backup/`date +"%m-%d-%y"`.tar.gz *;;
        '-help')
            echo -e "\nUSAGE: compile -o filename [-clean] [-backup] [-archive] [-help] cfilenames\n"
            echo -e "DESCRIPTION:\n"
            echo -e "\t-o filename, \tnon-optional argument. Place output in file filename.\n"
            echo -e "\t-clean, \toptional argument. Deletes .o files before compile\n"
            echo -e "\t-backup, \toptional argument. copies all .c and .h files into backup dir.\n"
            echo -e "\t-archive, \toptional argument. TARS source dir and moves archive to backup dir.\n"
            echo -e "\t-help, \t\toptional argument. shows USAGE and DESCRIPTION.\n"
            echo -e "\tcfilenames, \toptional argument. Source files to be compiled.\n"
            echo -e "EXAMPLE:\n"
            echo -e "\tcompile -o myFile -clean -backup -archive -help f1.c f2.c f3.c\n";;
        esac
    done

        #if [ $var = '-clean' ];then
        #    rm *.o
        #fi
        #if [ $var = '-backup' ];then
        #    cp *.c ../backup
        #    cp *.h ../backup
        #fi
        #if [ $var = '-archive' ];then
        #fi

fi
