# Botris-cpp-stackoverflow
A botris bot to overflow your stack

# dependencies
    - OpenSSL (libssl-dev on debian!)
 
# Downloading and Building
### Cloning
```git clone <url> --recurse-submodules```

If you forgot to install the submodule (IXWebSocket), do this in the git repo root dir:
```git submodule update --init --recursive```

### Building

```
mkdir build
cd build
cmake ..
make -j4
```
And you're done!


# Prerequisites for running
    - Set the environment variable BOTRIS_API_TOKEN to your bot token
