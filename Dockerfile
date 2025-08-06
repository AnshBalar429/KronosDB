FROM gcc:11

RUN apt-get update && apt-get install -y \
    cmake \
    libboost-dev \
    libboost-system-dev \
    libboost-thread-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -B build && cmake --build build

EXPOSE 12345

CMD ["./build/Multithreaded_DB"]