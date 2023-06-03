FROM debian:stable-slim as builder


RUN \
  apt-get update && \
  apt-get install -y build-essential llvm cmake clang libatomic1 portaudio19-dev


COPY . /link
RUN mkdir -p /link/mayhem/build
WORKDIR /link/mayhem/build

RUN cmake -DCMAKE_CXX_STANDARD=20 -DBUILD_FUZZER=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
RUN cmake --build .


FROM debian:stable-slim as packaged
RUN \
  apt-get update && \
  apt-get install -y libatomic1
COPY --from=builder /link/mayhem/testsuite/ /mayhem/testsuite
COPY --from=builder /link/mayhem/build/Link_fuzz /Link_fuzz