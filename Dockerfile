FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    ninja-build \
    libgl1-mesa-dev \
    libglew-dev \
    libglfw3-dev \
    libglm-dev

WORKDIR /app
COPY . .

RUN cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build


FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    libgl1 \
    libgl1-mesa-dri \
    libopengl0 \
    libglew2.2 \
    libglfw3 \
    xvfb \
    xauth

WORKDIR /app

COPY --from=build /app/Minimum_bounding_box .
COPY shaders ./shaders
COPY *.obj ./

ENV LIBGL_ALWAYS_SOFTWARE=1

ENTRYPOINT ["xvfb-run", "-a", "./Minimum_bounding_box"]
CMD ["teapot.obj"]
