# Basic release compile script
# This script clones this repository in a subdirectory, copies all of the protocols and compiles the library.

# Make sure to start from blank
rm -rf JWayland-release
git clone https://github.com/Fabillotic/JWayland JWayland-release

# Clone the wayland-protocols repository if necessary
if [ ! -d "wayland-protocols" ]; then
	git clone https://gitlab.freedesktop.org/wayland/wayland-protocols
fi

# Clone the wayland core repository if necessary
if [ ! -d "wayland" ]; then
	git clone https://gitlab.freedesktop.org/wayland/wayland
fi

# Checkout the most recent tag
git -C wayland-protocols checkout $(git -C wayland-protocols describe --abbrev=0 --tags)
git -C wayland checkout $(git -C wayland describe --abbrev=0 --tags)

cp wayland-protocols/stable/**/*.xml JWayland-release/protocols
cp wayland-protocols/staging/**/*.xml JWayland-release/protocols
cp wayland-protocols/unstable/**/*.xml JWayland-release/protocols
cp wayland/protocol/wayland.xml JWayland-release/protocols

# Remove the unstable versions of xdg-shell because they are incompatible with stable/xdg-shell in scanning
rm JWayland-release/protocols/xdg-shell-unstable*.xml

make -C JWayland-release scan
make -C JWayland-release

mkdir -p release
cp -f JWayland-release/jwayland.jar release/jwayland.jar
cp -f JWayland-release/jwayland_native.jar release/jwayland_native.jar
cp -f JWayland-release/jwayland_source.jar release/jwayland_source.jar

# Remove unnecessary directory
rm -rf JWayland-release
