# Developer environment and build system for Embedded Linux homework
FROM debian:bookworm-slim

# Install build tools and debugging/network utilities
RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    netcat-traditional \
    iputils-ping \
    curl \
    vim \
    nano \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# Copy project files into container
COPY . .

# By default, open a bash shell for manual work
CMD ["/bin/bash"]
