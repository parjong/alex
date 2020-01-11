#CAFFE_ROOT=..
#CAFFE_INSTALL_ROOT=$(CAFFE_ROOT)/build/install
#
#all:
#	g++ -std=c++11 -o design -I $(CAFFE_INSTALL_ROOT)/include -L $(CAFFE_INSTALL_ROOT)/lib design.cpp -lcaffe -lboost_system -lglog
#
#run:
#	LD_LIBRARY_PATH=$(CAFFE_INSTALL_ROOT)/lib ./design $(CAFFE_ROOT)/examples/mnist/lenet.prototxt $(CAFFE_ROOT)/examples/mnist/lenet_iter_5000.caffemodel
