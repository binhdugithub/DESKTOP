#!/bin/bash
PROCESS="ITS_CCTV_NVR"

MAX=2
COUNT=1

until [ $COUNT -gt $MAX ] ; do
        PROCESS_NUM=$(ps -ef | grep "$PROCESS" | grep -v "grep")
        if [ ${#PROCESS_NUM} -gt 0 ]; then
	    sleep 5
           
        else
            echo "$PROCESS is stopped"
	    sleep 30
	    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/nvr/recorder/libs		
	    nohup /opt/nvr/recorder/ITS_CCTV_NVR &
        fi

        sleep 5
done

