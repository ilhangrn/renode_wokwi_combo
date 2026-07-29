FROM ubuntu:24.04

# Install base tools, Python, and Renode dependencies
RUN apt-get update && apt-get install -y \
    curl python3 python3-pip git mono-complete

# Install PlatformIO Core globally inside the container
RUN pip3 install -U platformio --break-system-packages

# Example: Install a specific version of Renode inside this container
RUN curl -L -o renode.deb https://github.com \
    && apt-get install -y ./renode.deb && rm renode.deb
