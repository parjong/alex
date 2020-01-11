# pepper-build

# How to enable logging

pepper-build provides a logging based on log4cxx. To see the log, create `log4cxx.ini` and fill it with the following:
```
log4j.rootLogger=all, stdout

log4j.appender.stdout=org.apache.log4j.ConsoleAppender
log4j.appender.stdout.layout=org.apache.log4j.PatternLayout

# Pattern to output the caller's file name and line number.
log4j.appender.stdout.layout.ConversionPattern=%5p [%t] (%F:%L) - %m%n
```
