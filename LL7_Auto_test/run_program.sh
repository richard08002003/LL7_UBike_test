#!/bin/bash

echo "執行LL7_UBike程式 . . . "
cd /usr/local/UBike/LL7_UBike/bin
pwd
#背景執行
./LL7_UBike &

# 檢查是否成功執行程式
##pid=$(ps auxw | grep "LL7_UBike" | grep -v grep)
pid=$(ps | grep "LL7_UBike" | grep -v grep)
echo $pid 
if [ "$pid" != "" ]; then 
  echo $pid
  echo "成功開起LL7_UBike程式"
  cd /home/root/LL7_Test
  filepath="/home/root/LL7_Test/Log"
  if [ -e $filepath ]; then
	echo $filepath exists
  else
	echo $filepath does not exist
	echo "Create the floder . . ."
	mkdir Log
  fi

else
  echo "找不到此行程!"
  exit 1 
fi
