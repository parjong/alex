#!/bin/bash

set -eo pipefail

JS_DIR="../JS.mine"
rm -rf "$JS_DIR"
mkdir -p "$JS_DIR"
git -C "$JS_DIR" init
./bplate-inject -o "$JS_DIR" -- "js-plugin" --github-version 'enterprise-server@3.2' --action-name 'my awesome action'
#./bplate-inject -o "$JS_DIR" -- "js-plugin" --github-version 'enterprise-server@3.2'

exit 0

rm -rf X.mine
mkdir -p X.mine
./bplate-inject -o X.mine -- "plugin" 1 2 3
ls -alR X.mine


