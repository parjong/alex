#!/bin/bash

###
### https://wiki.jenkins-ci.org/display/JENKINS/Distributed+builds
###

URL=$1; shift

AGENT_NAME=$1; shift
AGENT_PASS=$1; shift

# TODO
if [[ -z "${URL}" || -z "${AGENT_NAME}" || -z "${AGENT_PASS}" ]]; then
  echo "USAGE: ${SELF_HEAD} [URL] [AGENT NAME] [AGENT PASS]"
  exit 255
fi

AGENT_JAR="${ALEX_APPLET_DATA_DIR}/agent.jar"

if [[ ! -f "${AGENT_JAR}" ]]; then
  # Download from http://yourserver:port/jnlpJars/slave.jar 
  wget -O "${AGENT_JAR}" "http://${URL}/jnlpJars/agent.jar"
fi

if [[ ! -f "${AGENT_JAR}" ]]; then
  echo "ERROR: FAIL TO DOWNLOAD slave.jar"
  exit 255
fi

# java -jar slave.jar -jnlpUrl http://yourserver:port/computer/slave-name/slave-agent.jnlp
java \
  -jar "${AGENT_JAR}" \
  -jnlpUrl http://${URL}/computer/${AGENT_NAME}/slave-agent.jnlp \
  -secret "${AGENT_PASS}"
