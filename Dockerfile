# docker build -t lebedevri/chrysaor .

FROM debian:testing
MAINTAINER Roman Lebedev <lebedev.ri@gmail.com>

# Paper over occasional network flakiness of some mirrors.
RUN echo 'APT::Acquire::Retries "5";' > /etc/apt/apt.conf.d/80retry

# Install dev stuff
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      gcc-6 g++-6 clang-3.8 make cmake libgtest-dev && \
    apt-get clean -y && rm -rf /var/lib/apt/lists/*
