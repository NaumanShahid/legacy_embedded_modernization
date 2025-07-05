#!/bin/bash

echo "🕒 Fixing file timestamps to prevent clock skew warnings..."
find . -type f -exec touch {} +

echo "✅ File timestamps updated. You can now run your build normally."
