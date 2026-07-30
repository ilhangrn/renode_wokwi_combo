FROM ubuntu:24.04

# Prevent interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build dependencies, Python, and system tools
RUN apt-get update && apt-get install -y \
    curl \
    git \
    python3 \
    python3-pip \
    python3-venv \
    libusb-1.0-0 \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Install PlatformIO Core globally inside the container
RUN pip3 install -U platformio --break-system-packages

# Install the Espressif Rust toolchain installer (espup)
RUN curl -L https://github.com -o /usr/local/bin/espup \
    && chmod +x /usr/local/bin/espup

# Create a non-root user for development
ARG USERNAME=developer
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update && apt-get install -y sudo \
    && echo $USERNAME ALL=\(ALL\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME
WORKDIR /home/developer

# Pre-install the ESP32 Rust target (This runs as the developer user)
RUN espup install --targets esp32
