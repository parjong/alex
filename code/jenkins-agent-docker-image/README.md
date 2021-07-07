# How to use
```
$ docker build -t [Image Name] .
$ docker run -d \
	--env JENKINS_MASTER_URL=http://[MASTER ADDRESS]:[MASTER PORT]/ \
	--env JENKINS_SLAVE_NAME=[SLAVE NAME] \
	--env JENKINS_SLAVE_PASS=[SLAVE PASS] \
	[Image Name]
```
