#!/bin/sh

# 1) Format disk.
# 2) Create /beach.jpg
# 3) Read beach.jpg and check MD5.
# 4) Mkdir /home
# 5) Mkdir /home/user
# 6) Create /home/sun.jpg
# 7) Create /home/user/earth.jpg
# 8) Create /home/user/galaxy.jpg
# 9) Create /home/manhattan.jpg
# 10) ls /
# 11) ls /home
# 12) ls/home/user
# 13) Read /home/sun.jpg and check MD5
# 14) Read /home/user/galaxy.jpg and check galaxy.jpg MD5
# 15) Delete /home/user/galaxy.jpg
# 16) Delete /home/user/earth.jpg
# 17) Rmdir /home/user/
# 18) ls /

echo "########### Test 1 #############"
./simulfs -format
echo "Formating passed!"

echo ""
echo "########### Test 2 #############"
./simulfs -create images/beach.jpg /beach.jpg
echo "Create /beach.jpg passed!"

echo ""
echo "########### Test 3 #############"
OMD5=$(md5sum images/beach.jpg | awk '{print $1}')

mkdir -p images/recovered

./simulfs -read images/recovered/beach.jpg /beach.jpg

CMD5=$(md5sum images/recovered/beach.jpg | awk '{print $1}')

if [ "$OMD5" != "$CMD5" ]; then
	echo "beach.jpg MD5 error!"
	exit 1
fi;

echo "Read /beach.jpg passed!"

echo ""
echo "########### Test 4 #############"
echo "Creating directory /home"
./simulfs -mkdir /home

echo ""
echo "########### Test 5 #############"
echo "Creating directory /home/user"
./simulfs -mkdir /home/user

echo ""
echo "########### Test 6 #############"
./simulfs -create images/sun.jpg /home/sun.jpg
echo "Create /home/sun.jpg passed!"

echo ""
echo "########### Test 7 #############"
./simulfs -create images/earth.jpg /home/user/earth.jpg
echo "Create /home/user/earth.jpg passed!"

echo ""
echo "########### Test 8 #############"
./simulfs -create images/galaxy.jpg /home/user/galaxy.jpg
echo "Create /home/user/galaxy.jpg passed!"

echo ""
echo "########### Test 9 #############"
./simulfs -create images/manhattan.jpg /home/manhattan.jpg
echo "Create /home/manhattan.jpg passed!"

echo ""
echo "########### Test 10, 11 e 12 #############"
./simulfs -ls /
./simulfs -ls /home
./simulfs -ls /home/user

echo ""
echo "########### Test 13 #############"
OMD5=$(md5sum images/sun.jpg | awk '{print $1}')

./simulfs -read images/recovered/sun.jpg /home/sun.jpg

CMD5=$(md5sum images/recovered/sun.jpg | awk '{print $1}')

if [ "$OMD5" != "$CMD5" ]; then
	echo "sun.jpg MD5 error!"
	exit 1
fi;

echo "read /home/sun.jpg passed!"

echo ""
echo "########### Test 14 #############"
OMD5=$(md5sum images/galaxy.jpg | awk '{print $1}')

./simulfs -read images/recovered/galaxy.jpg /home/user/galaxy.jpg

CMD5=$(md5sum images/recovered/galaxy.jpg | awk '{print $1}')

if [ "$OMD5" != "$CMD5" ]; then
	echo "galaxy.jpg MD5 error!"
	exit 1
fi;

echo "read /home/recovered/galaxy.jpg passed!"

echo ""
echo "########### Test 15 #############"
./simulfs -del /home/user/galaxy.jpg
echo "Delete galaxy.jpg passed!"

echo ""
echo "########### Test 16 #############"
./simulfs -del /home/user/earth.jpg
echo "Delete galaxy.jpg passed!"

echo ""
echo "########### Test 17 #############"
./simulfs -rmdir /home/user/
echo "Delete user directory passed!"

echo ""
echo "########### Test 18 #############"
./simulfs -ls /


