FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies for PlatformIO, Rust, and Renode
RUN apt-get update && apt-get install -y \
    ca-certificates curl git python3 python3-pip python3-venv build-essential \
    libglib2.0-0 libpixman-1-0 libgtk-3-0 libnss3 libx11-6 libxrender1 libxext6 \
    xz-utils \
    && rm -rf /var/lib/apt/lists/*

# Install Renode portable package
RUN curl -fsSL -o renode.tar.gz https://builds.renode.io/renode-latest.linux-portable.tar.gz \
    && mkdir -p /opt/renode \
    && tar -xzf renode.tar.gz -C /opt/renode --strip-components=1 \
    && ln -s /opt/renode/renode /usr/local/bin/renode \
    && rm renode.tar.gz

# Install PlatformIO Core
RUN python3 -m venv /opt/pio-venv \
    && /opt/pio-venv/bin/pip install --no-cache-dir -U pip platformio
ENV PATH="/opt/pio-venv/bin:$PATH"

# Install Rust toolchain for ESP32-C3 (RISC-V target)
RUN curl --proto '=https' --tlsv1.2 -sSf https://rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:$PATH"
RUN rustup target add riscv32imac-unknown-none-elf
