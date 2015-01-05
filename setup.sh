#!/bin/bash
function help()
{
  echo -e "Usage: $0 <argument>"
  echo -e "This script help you to easy install or compile simple editor\n"
  echo -e "     install     to compile and install simple editor ."
  echo -e "     compile     to compile simple editor ."
  echo -e "     help        to show this help screen ."
}

function install()
{
  make 
  make install
  make clean
}

function compile()
{
  make 
  make clean
}


USER=`id -u`

if [ $USER != 0 ] 
  then
    echo -e "Permission denied: \n\t this operation need root privileges please use sudo $0"
    exit 1
fi

if [ $# != 1 ] 
  then
    help
    exit 1
fi

if [ $1 == "install" ] 
  then
    install
fi

if [ $1 == "compile" ] 
  then
    compile
fi

if [ $1 == "help" ] 
  then
    help
fi