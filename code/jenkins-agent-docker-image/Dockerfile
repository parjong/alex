FROM ubuntu:14.04
MAINTAINER Jonghyun Park

RUN apt-get update
RUN apt-get install -y wget openjdk-7-jre

RUN mkdir -p /var/jenkins
WORKDIR /var/jenkins
COPY start /var/jenkins
CMD /bin/bash /var/jenkins/start
