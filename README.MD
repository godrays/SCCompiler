# Project Build Instructions

Follow these steps to build the project and make it deployment-ready.

Currently, it has been built and tested on Sonoma, macOS.

---

### Step 1: Install Third-Party Dependencies.

This step will install dependencies. Assuming XCode and MacPorts is already installed.

```bash
sudo port install ossp-uuid pkgconfig graphviz
```

Install JAVA SE SDK.

```bash
http://www.oracle.com/technetwork/java/javase/downloads/index.html
```

### Step 2: Build Externals

This step will build external libraries.

```bash
cd Externals
./build_antlr.sh
./build_catch2.sh
./build_llvm.sh
```

### Step 3: Build Targets

This step will build all binaries and deploy into a specific folder.

```bash
./build.sh release build-release $(pwd)/product-rel 8
```

After a successful build, all target binaries will be deployed into the product-rel folder.

Note: Run the build.sh file without parameters to see all options.
