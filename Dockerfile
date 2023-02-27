FROM ubuntu:20.04
WORKDIR /containers
COPY . /containers
RUN apt-get update && \
    apt-get install -y g++ cmake python3 valgrind cppcheck libgtest-dev && \
    rm -rf /var/lib/apt/lists/*
CMD ["make", "test"]
