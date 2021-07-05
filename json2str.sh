#!/bin/bash
rm io_json.c
echo "const char jsonmsg[]=" > io_json.c
cat io.json | sed 's/"/\\"/g' | sed '1c\\"{' | sed '$c}"' | sed -z 's/\n//g' | sed 's/\t//g'|sed 's///g'|sed 's/ //g' >> io_json.c
echo ";" >> io_json.c
