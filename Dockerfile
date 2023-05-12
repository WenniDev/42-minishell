# Build and run:
#   docker build -t clion/ubuntu/cpp-env:1.0 -f Dockerfile.cpp-env-ubuntu .

FROM ubuntu

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y gcc g++ gdb clang
RUN apt-get install -y ninja-build cmake autoconf automake
RUN apt-get install -y libtool valgrind locales-all dos2unix
RUN apt-get install -y rsync tar python3 python3-dev
RUN apt-get install -y libreadline-dev=8.1.2-1
RUN apt-get clean