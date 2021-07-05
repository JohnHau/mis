#!/bin/bash
cat now-json.txt|sed 's/\\//g' | sed 's/^.//g' | sed 's/.$//g'> now.json
