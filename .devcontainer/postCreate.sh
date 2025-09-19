#!/usr/bin/env bash
set -euo pipefail

chmod +x .vscode/scripts/*.sh || true

# Mark workspace as safe (useful when mounting from host)
git config --global --add safe.directory /workspaces/* || true
ccache --max-size=5G || true

bash ".vscode/scripts/fullclean.sh" || true