# C++ devcontainer (Ubuntu 24.04 base)
ARG VARIANT=ubuntu-24.04
FROM mcr.microsoft.com/devcontainers/base:${VARIANT}

ENV DEBIAN_FRONTEND=noninteractive
ENV CC=clang CXX=clang++ \
    CCACHE_DIR=/home/vscode/.cache/ccache \
    CCACHE_MAXSIZE=5G

# TODO remove nlohmann in the future.
RUN apt-get update && apt-get install -y --no-install-recommends \
    bash build-essential git curl ca-certificates pkg-config cmake ninja-build \
    clang clangd clang-format lld lldb gdb ccache \
    python3 python3-pip python3-venv python-is-python3 \
    libgtest-dev libglew-dev \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
    libegl1-mesa-dev libgl1-mesa-dev \
    nlohmann-json3-dev rapidjson-dev \
    && rm -rf /var/lib/apt/lists/*

RUN install -d -m 700 -o vscode -g vscode /home/vscode/.cache \
    && install -d -m 700 -o vscode -g vscode /home/vscode/.cache/ccache

# Build & install GoogleTest once
RUN cmake -S /usr/src/googletest -B /tmp/gtest-build \
    && cmake --build /tmp/gtest-build --target install -j"$(nproc)" \
    && rm -rf /tmp/gtest-build \
    && ldconfig

# Route clang through ccache
RUN ln -sf /usr/bin/ccache /usr/local/bin/clang \
    && ln -sf /usr/bin/ccache /usr/local/bin/clang++

# Build & install GLFW (X11)
ARG GLFW_REF=3.4
RUN git clone --branch ${GLFW_REF} --depth 1 https://github.com/glfw/glfw.git /opt/glfw \
    && cmake -S /opt/glfw -B /opt/glfw/build -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF \
        -DGLFW_INSTALL=ON \
        -DGLFW_BUILD_X11=ON -DGLFW_BUILD_WAYLAND=OFF \
    && cmake --build /opt/glfw/build --target install -j"$(nproc)" \
    && rm -rf /opt/glfw && ldconfig

# Fetch Dear ImGui sources
ARG IMGUI_REF=v1.91.0
RUN git clone --branch ${IMGUI_REF} --depth 1 https://github.com/ocornut/imgui.git /opt/imgui \
    && rm -rf /opt/imgui/.git

# Show tool versions at build
RUN clang --version && cmake --version && ninja --version

# Default to non-root user from base image
USER vscode
WORKDIR /workspaces
