#!/usr/bin/env bash
MOD_GROUPQUESTS_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_GROUPQUESTS_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_GROUPQUESTS_ROOT"/conf/conf.sh" ]; then
    source $MOD_GROUPQUESTS_ROOT"/conf/conf.sh"
fi
