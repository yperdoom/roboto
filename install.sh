#!/usr/bin/env bash
set -e

REPO="yperdoom/roboto"
INSTALL_DIR="$HOME/.local/share/roboto"
BIN_DIR="$HOME/.local/bin"
DESKTOP_DIR="$HOME/.local/share/applications"

# Find latest release tarball
echo "Fetching latest release..."
LATEST_URL=$(curl -s "https://api.github.com/repos/$REPO/releases/latest" \
  | grep "browser_download_url.*linux.*tar.gz" \
  | cut -d '"' -f 4)

if [ -z "$LATEST_URL" ]; then
  echo "Error: could not find a Linux release at github.com/$REPO/releases"
  exit 1
fi

FILENAME=$(basename "$LATEST_URL")
TMP_DIR=$(mktemp -d)
trap "rm -rf $TMP_DIR" EXIT

echo "Downloading $FILENAME..."
curl -L --progress-bar "$LATEST_URL" -o "$TMP_DIR/$FILENAME"

echo "Installing to $INSTALL_DIR..."
rm -rf "$INSTALL_DIR"
mkdir -p "$INSTALL_DIR"
tar -xzf "$TMP_DIR/$FILENAME" -C "$INSTALL_DIR" --strip-components=1

# Symlink binary
mkdir -p "$BIN_DIR"
ln -sf "$INSTALL_DIR/bin/robo3t" "$BIN_DIR/roboto"

# Desktop entry
mkdir -p "$DESKTOP_DIR"
cat > "$DESKTOP_DIR/roboto.desktop" << EOF
[Desktop Entry]
Name=RoboTo
Comment=Shell-centric MongoDB management tool
Exec=$INSTALL_DIR/bin/robo3t
Icon=$INSTALL_DIR/share/icons/roboto.png
Terminal=false
Type=Application
Categories=Development;Database;
StartupWMClass=robo3t
EOF

update-desktop-database "$DESKTOP_DIR" 2>/dev/null || true

# Warn if ~/.local/bin is not in PATH
if [[ ":$PATH:" != *":$BIN_DIR:"* ]]; then
  echo ""
  echo "Note: add this line to your ~/.bashrc or ~/.zshrc to use 'roboto' from the terminal:"
  echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
fi

echo ""
echo "Done! RoboTo installed."
echo "  Terminal:     roboto"
echo "  App launcher: search for 'RoboTo'"
