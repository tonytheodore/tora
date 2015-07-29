#! /bin/bash

g++ --version

tora=/home/travis/build/tora-tool/tora

if [ "$QTTYPE" = "4" ]; then
	mkdir /tmp/qt4
        cd /tmp/qt4
	cmake $tora -DORACLE_PATH_INCLUDES=/usr/include/oracle/12.1/client64/ -DORACLE_PATH_LIB=/usr/lib/oracle/12.1/client64/lib/ -DTEST_APP4=true -DTEST_APP1=true
	make || exit 1
fi

if [ "$QTTYPE" = "5" ]; then
        mkdir /tmp/qt5
	cd /tmp/qt5
	cmake $tora -DWANT_INTERNAL_QSCINTILLA=true -DORACLE_PATH_INCLUDES=/usr/include/oracle/12.1/client64/ -DORACLE_PATH_LIB=/usr/lib/oracle/12.1/client64/lib/ -DQT5_BUILD=true
	make || exit 1
fi
