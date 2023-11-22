#!/bin/bash 

DAY=$1
CONFIG=$2
shift 2

./${DAY}/target/macosx-ARM64/${CONFIG}/${DAY}/${DAY} "$@"

