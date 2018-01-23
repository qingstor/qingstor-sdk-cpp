	#!/bin/sh 

    # generate code
    echo "[------- generating code... -------]"

    snips=`which snips`
    echo "$snips"

    if [ ! -f $snips ]; then \
		echo "ERROR: Command \"snips\" not found."; \
	fi
	sudo $snips -f="./specs/2016-01-06/swagger/api_v2.0.json" -t="./template/header/" -o="./include/"
    sudo $snips -f="./specs/2016-01-06/swagger/api_v2.0.json" -t="./template/source/" -o="./src/service"
    sudo $snips -f="./specs/2016-01-06/swagger/api_v2.0.json" -t="./template/header_with_c_style/" -o="./include/service_with_c_style/"
    sudo $snips -f="./specs/2016-01-06/swagger/api_v2.0.json" -t="./template/source_with_c_style/" -o="./src/service/service_with_c_style/"
    
    # format code 
    echo "[------- formating code... -------]"
    sudo mv ./include/service_with_c_style/QsList.h ./include/service_with_c_style/QsList_bak
    sudo find ./include/ -name "*.h"| xargs sudo indent  -npro -kr -i4 -ts4 -sob -l80 -ss -bl -bli 0
    sudo find ./src/service -name "*.cpp" | xargs sudo indent  -npro -kr -i4 -ts4 -sob -l80 -ss -bl -bli 0
    sudo find . -name "*~" | xargs sudo rm 
    sudo astyle -R ./*.cpp ./*.h --delete-empty-lines -n --style=ansi $file
    sudo mv ./include/service_with_c_style/QsList_bak ./include/service_with_c_style/QsList.h
    # orgnize files 
    echo "[------- orgnizing files... -------]"
    sudo rm -rf ./src/service/Object.cpp
    echo "delete file ./src/service/Object.cpp"
    sudo rm -rf ./include/Object.h
    echo "delete file ./include/Object.h"
    sudo mv ./src/service/service_with_c_style/QingStor.cpp ./src/service/service_with_c_style/QingStorCStyle.cpp
    echo "rename file QingStorCStyle.cpp "
    sudo mv ./include/service_with_c_style/QingStor.h ./include/service_with_c_style/QingStorCStyle.h
    echo "rename file QingStorCStyle.h "

	echo "Done"