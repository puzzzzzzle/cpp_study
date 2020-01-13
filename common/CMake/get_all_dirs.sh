#!/bin/bash

function listFiles()
{
        for file in `ls $1`;
        do
                if [ -d "$1/$file" ]; then
                    echo -n "$1/$file;"
                    listFiles "$1/$file"
                fi
        done
}
listFiles $1