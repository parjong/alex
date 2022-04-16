#!/bin/bash

wget -O slave.jar "${JENKINS_MASTER_URL}/jnlpJars/slave.jar"
java ${JAVA_OPTS} -jar slave.jar -jnlpUrl "${JENKINS_MASTER_URL}/computer/${JENKINS_SLAVE_NAME}/slave-agent.jnlp" -secret "${JENKINS_SLAVE_PASS}"
