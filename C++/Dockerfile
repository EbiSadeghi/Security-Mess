#### Build stage:
# We want to keep build tools and source in an intermediate stage, 
# then produce a smaller final image by copying only the necessary outputs (binaries, assets) 
# from the named build stage into the runtime stage. This reduces final image size and attack surface.
FROM docker.io/library/ubuntu:24.04 AS build
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ca-certificates pkg-config git ca-certificates \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /src

# Copy only files needed for the build to keep context small.
# Adjust if you need other files (CMakeLists, scripts, resources).
COPY CMakeLists.txt .
COPY include/ include/
COPY src/ src/

# Configure and build
RUN mkdir -p /app \
 && mkdir build \
 && cd build \
 && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=20 \
 && cmake --build . --parallel $(nproc) \
 && cp ./SecureCpp /app/SecureCpp

#### SBOM stage:
# Do this outside of the docker image

#### Runtime stage: 
# use minimal base (distroless)
#FROM gcr.io/distroless/cc
FROM docker.io/library/ubuntu:24.04 
COPY --from=build /app/SecureCpp /usr/local/bin/SecureCpp
ENTRYPOINT ["/usr/local/bin/SecureCpp"]
