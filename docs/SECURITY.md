# Security Notes
- Native app needs no root privileges.
- Container uses a non-root user, read-only root filesystem, dropped capabilities, and no-new-privileges.
- Treat config and CSV input as untrusted.
- The systemd unit is an example; review paths and provision its service account before use.
- Before production use, add resource limits, structured audit logging, fuzzing, image scanning, and deployment review.
